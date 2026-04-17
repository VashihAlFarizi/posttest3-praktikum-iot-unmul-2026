#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

// ================= WIFI =================
const char* ssid = "Hey";
const char* password = "makannasik";

// ================= MQTT =================
const char* mqtt_server = "broker.emqx.io";

// ================= PIN =================
#define WATER_SENSOR A0
#define BUZZER D6
#define SERVO_PIN D5

WiFiClient espClient;
PubSubClient client(espClient);
Servo servo;

// ================= VAR =================
bool modeAuto = true;
bool buzzerManual = false;
int servoManual = 0;

// ===== BLINK BUZZER =====
unsigned long previousMillis = 0;
const long interval = 300;
bool buzzerBlinkState = false;

// ================= WIFI =================
void setup_wifi() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

// ================= CALLBACK =================
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  message.trim();
  message.toUpperCase();

  Serial.println("\n=== MQTT MASUK ===");
  Serial.print("Topic: "); Serial.println(topic);
  Serial.print("Msg  : "); Serial.println(message);
  Serial.print("Length: "); Serial.println(message.length());

  if (strcmp(topic, "vashih/posttest3/control") == 0) {

    // ===== MODE =====
    if (message.indexOf("AUTO") >= 0) {
      modeAuto = true;
      Serial.println(">>> PINDAH KE AUTO");

      client.publish("vashih/posttest3/mode", "AUTO");
      return;
    }

    if (message.indexOf("MANUAL") >= 0) {
      modeAuto = false;
      Serial.println(">>> PINDAH KE MANUAL");

      client.publish("vashih/posttest3/mode", "MANUAL");
      return;
    }

    // ===== CONTROL MANUAL =====
    if (!modeAuto) {
      if (message == "SERVO_0") servoManual = 0;
      else if (message == "SERVO_90") servoManual = 90;
      else if (message == "SERVO_180") servoManual = 180;
      else if (message == "BUZZER_ON") buzzerManual = true;
      else if (message == "BUZZER_OFF") buzzerManual = false;
    }
  }
}

// ================= MQTT =================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting MQTT...");

    if (client.connect("ESP8266_Posttest3")) {
      Serial.println("Connected");

      client.subscribe("vashih/posttest3/control");

      // kirim status awal
      client.publish("vashih/posttest3/mode", modeAuto ? "AUTO" : "MANUAL");

    } else {
      Serial.println("Retry...");
      delay(2000);
    }
  }
}

// ================= STATUS =================
String getStatus(int v) {
  if (v <= 800) return "AMAN";
  else if (v <= 1500) return "WASPADA";
  else return "BAHAYA";
}

// ================= SETUP =================
void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(BUZZER, OUTPUT);
  servo.attach(SERVO_PIN);
}

// ================= LOOP =================
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int air = analogRead(WATER_SENSOR);
  String status = getStatus(air);

  int servoPos;
  bool buzzerActive;

  // ===== MODE AUTO =====
  if (modeAuto) {
    if (status == "AMAN") {
      servoPos = 0;
      buzzerActive = false;
    } else if (status == "WASPADA") {
      servoPos = 90;
      buzzerActive = false;
    } else {
      servoPos = 180;
      buzzerActive = true;
    }
  }

  // ===== MODE MANUAL =====
  else {
    servoPos = servoManual;
    buzzerActive = buzzerManual;
  }

  servo.write(servoPos);

  // ===== BUZZER BLINK =====
  if (buzzerActive) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      buzzerBlinkState = !buzzerBlinkState;
      digitalWrite(BUZZER, buzzerBlinkState);
    }
  } else {
    digitalWrite(BUZZER, LOW);
    buzzerBlinkState = false;
  }

  // ===== PUBLISH DATA =====
  client.publish("vashih/posttest3/levelair", String(air).c_str());
  client.publish("vashih/posttest3/statuslevel", status.c_str());
  client.publish("vashih/posttest3/servo", String(servoPos).c_str());
  client.publish("vashih/posttest3/buzzer", buzzerActive ? "ON" : "OFF");
  client.publish("vashih/posttest3/mode", modeAuto ? "AUTO" : "MANUAL");

  Serial.print("Mode: ");
  Serial.print(modeAuto ? "AUTO" : "MANUAL");
  Serial.print(" | Buzzer: ");
  Serial.println(buzzerActive ? "KEDIP" : "OFF");

  delay(200);
}
