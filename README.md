# posttest3-praktikum-iot-unmul-2026

## **Nama Kelompok:**

Kelompok 7

## **Anggota:**

1. Muhammad Aidil Saputra (2309106042)
2. Vashih Al Farizi (23091006076)
3. Muhammad Rafif Hanif (2309106044)
4. Muhamad Ihsan (2209106099)

---

## **Judul studi kasus**

bendungan pintar memerlukan sistem pemantauan ketinggian air dan pengendalian pintu air secara otomatis maupun darurat dari jarak jauh. Sistem ini menggunakan Water Level Sensor untuk mendeteksi ketinggian air, Motor Servo sebagai aktuator penggerak pintu air, dan Buzzer sebagai alarm peringatan.

---

## **Deskripsi**

1. Atur logika otomatisasi ketinggian air dengan ketentuan sebagai berikut:
- Level Aman (Sensor <= 800): Pintu air tertutup (Servo 0°), Buzzer mati.
- Level Waspada (801 - 1500): Pintu air terbuka setengah (Servo 90°), Buzzer mati.
- Level Bahaya (> 1500): Pintu air terbuka penuh (Servo 180°), Buzzer menyala berkedip
2. Pada Kodular menampilkan nilai level air, status level (aman/waspada/bahaya), status buzzer, dan nilai servo.
3. Pada Kodular terdapat 2 button mode otomatis dan manual, dengan ketentuan:
- Otomatis: aktuator (servo dan buzzer) bekerja sesuai dengan syarat pada ketentuan nomor 1
- Manual: aktuator (servo dan buzzer) dapat dikontrol secara manual pada kodular
4. Buat tampilan semenarik mungkin.

---

## **Pembagian Tugas**

- Muhammad Aidil Saputra: Pembukan dan menjelaskan alat alat yang digunakan
- Vashih Al Farizi: Membuat Blocks Kodular, membuat Config penghubung Kodular ke ESP32 dan menjelasaka penggunaan
- Muhammad Rafif Hanif: Membuat config sistem dan Menjelaskan cara penggunaan sensor
- Muhamad Ihsan:  Membuat Board Schematic dan penjelasan pin alat

---

## **Komponen yang Digunakan** ##
- ESP32
- Sensor Air
- Servo
- Buzzer
- Breadboard
- Kabel jumper
- Sumber daya kabel type c

---

## **Board Schematic** ##
<img width="888" height="576" alt="image" src="https://github.com/user-attachments/assets/0cad881a-8f7c-436f-9151-bbfff657e7c1" />



---

## **Link Video Demo** ##

LINK: https://youtu.be/1UBeoprrq2o

---
