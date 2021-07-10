/*
   Gunakan Core ESP8266 versi 2.7.4, hal ini berpengaruh terhadap epoch time dari
   NTP Server.

   Kami belum mengetahui kenapa terjadi seperti itu. Perlu gunakan metode lain
   untuk mendapatkan tanggal jika ingin menggunakan Core ESP8266 diatas versi 2.7.4

   Credits:
   - Lorenz Adam D.
   - Wiku
   - Nusabot Team

   Proyek ini dilisensikan dibawah GPL3 (General Public License V.3)
   Nusabot berhak mengganti lisensi di rilis-rilis yang akan datang.
*/

#include <NTPClient.h>
#include "ESP8266WiFi.h"
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include "SSD1306.h" //https://github.com/ThingPulse/esp8266-oled-ssd1306
#include <WiFiUdp.h>

#define tombol 15

//Konfigurasi WiFi
const char *ssid = "Aa_plus";
const char *password = "adamdamara";

//IP Address ataupun Domain Web Server
const char *host = "192.168.100.55";

constexpr uint8_t RST_PIN =  0; // Pin D3 Pada Wemos D1 R1 Mini
constexpr uint8_t SS_PIN =  2; // Pin D4 Pada Wemos D1 R1 Mini

unsigned long previousMillis = 0, interval = 1000, epochTime;

/*
   Address diatur ke 0x3C, dari coba-coba karena dari scanner tidak
   muncul. D2 (SDA/Serial Data), dan D5 (SCK/Serial Clock).
   Pakai OLED buatan Tiongkok, jadi tidak menggunakan library dari
   Adafruit
*/
SSD1306  display(0x3C, D1, D2);

/*
  Ambil waktu dari NTP Server
*/
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200);

/*
  Buat identitas mesin untuk mencatat di mesin mana pengguna yang
  bersangkutan yang melakukan absensi, nilai variabel ini akan
  disimpan di basis data.

  Identitas mesin ini berupa MAC Address. Untuk perangkat yang tidak
  memiliki network adapter mungkin dapat membuat identitas mesin
  sendiri namun hal tersebut akan sulit jika ingin dilakukan
  update melalui OTA. Well secara praktik OTA tidak dapat dilakukan
  jika tidak mesin tidak disertai network adaptor.
*/
String uid, url, textKategori = "Masuk", idmesin = String(WiFi.macAddress());
String hari[7] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
String bulan[12] = {"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Ags", "Sep", "Okt", "Nov", "Des"};

int kategori = 1; //default kategori absen

MFRC522 mfrc522(SS_PIN, RST_PIN); //Buat instance RC522

void setup() {
  pinMode(tombol, INPUT_PULLUP);
  Serial.begin(9600); //Inisialisasi komunikasi serial untuk debuging
  delay(1000);
  Serial.println("Setup");
  display.init();
  display.flipScreenVertically();

  //menghubungkan ke wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Menghubungkan");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawStringMaxWidth(128 / 2, 64 / 2, 128, "Menghubungkan ke WiFi");
    display.display();
  }

  Serial.println("");
  Serial.print("Terhubung ke ");
  Serial.println(ssid);
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(128 / 2, 64 / 2, "Terhubung Ke Jaringan");
  display.display();
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();

  /*
     Uncomment jika menggunakan Arduino based ATMEGA32U4
     Agar uC Jangan lakukan apapun jika tidak ada
     komunikasi serial
  */
  // while (!Serial);
  SPI.begin();      // Inisialisasi SPI bus
  mfrc522.PCD_Init();   // Inisialisasi MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Untuk menampilkan detail detail PCD - MFRC522 Card Reader
  Serial.println(F("Scan PICC untuk melihat UID..."));
  Serial.println("Setup done");
  delay(1000); //agar pesan terhubung ke jaringan bisa tampil
}

void loop() {
  timeClient.update();

  epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime); //NTP time structure
  int tanggalIni = ptm->tm_mday;
  int bulanIni = ptm->tm_mon + 1;
  int tahunIni = ptm->tm_year + 1900; //NTP mengambil detik sejak tahun 1900
  String namaBulan = bulan[bulanIni - 1];
  String tanggal = String(tanggalIni) + " " + String(bulan[bulanIni - 1]) + "  " + String(tahunIni) ;

  unsigned long currentMillis = millis();
  WiFiClient client;
  timeClient.update();
  if (!client.connect(host, 80)) {
    Serial.println("koneksi gagal");
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawStringMaxWidth(128 / 2, 64 / 2, 128 , "Tidak Dapat Terhubung Ke Server");
    display.display();
    return;
  }

  /*
    Kembali ke awal loop jika tidak ada tag yang terbaca pada reader.
    Hal ini meringankan beban kerja atau mempersingkat proses saat
    posisi idle
  */
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    //cek tombol
    if (digitalRead(tombol) == 1) {
      kategori += 1;
      if (kategori > 4) {
        kategori = 1;
      }
      switch (kategori) {
        case 1:
          textKategori = "Masuk";
          break;
        case 2:
          textKategori = "Mulai Istirahat";
          break;
        case 3:
          textKategori = "Selesai Istirahat";
          break;
        case 4:
          textKategori = "Pulang";
          break;
      }
      Serial.println(textKategori);
      delay(500); //agar penambahannya tidak terlalu cepat
    }

    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;

      display.clear();
      display.setFont(ArialMT_Plain_24);
      display.setTextAlignment(TEXT_ALIGN_CENTER);
      display.drawString(128 / 2, 10, String(timeClient.getFormattedTime()));
      display.setFont(ArialMT_Plain_10);
      display.drawString(128 / 2, 0, String(hari[timeClient.getDay()]) + ", " + tanggal);
      display.setTextAlignment(TEXT_ALIGN_RIGHT);
      display.drawString(128, 50, String(WiFi.RSSI()) + " dBm");
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.drawString(0, 50, textKategori);
      display.display();

      //delay(50);
      return;
    }
  }

  // pilih satu tag
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    //delay(50);
    return;
  }

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  //kirim data
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(128 / 2, 10, textKategori);
  display.setFont(ArialMT_Plain_10);
  display.drawString(128 / 2, 30, "Data Absen Direkam :)");
  display.display();

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

  delay(1000); // ambil aman, biarkan uC posisi idle
}

/*
  Helper routine untuk melakukan dump a byte array
  sebagai nilai hex ke variabel
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    uid = uid + String(buffer[i], HEX);
  }
  Serial.println(uid);
  Serial.println(idmesin);

  url = "/absensi/machine.php?tag=";
  url = url + uid + "&idmesin=" + idmesin + "&kategori=" + kategori;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.println();
  uid = ""; //kosongkan variabel UID setelah selesai digunakan
}
