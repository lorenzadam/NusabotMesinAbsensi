# [Sistem Absensi - Nusabot](https://nusabot.id)

**Nusabot Absensi** adalah sistem absensi gratis yang dapat diterapkan untuk berbagai kepentingan absensi seperti pabrik, toko, kantor, dan sebagainya. Sistem ini termasuk manajemen absensi dan mesin absensi yang dapat dipelajari oleh siapapun.
Sistem ini dibuat tanpa framework dan menggunakan bahasa struktural sehingga mudah dipelajari oleh pemula.

Proyek ini adalah bagian dari proyek **Nusabot FOSS** sebagai wujud kepedulian Nusabot terhadap pendidikan teknologi di Indonesia yang bertujuan untuk membuat dan mengembangkan proyek-proyek *open source*  yang memiliki kualitas baik sehingga dapat diterapkan secara real di industri sekaligus dapat dipelajari oleh seluruh masyarakat Indonesia. 

**Demo di [http://absensi.nusabot.id](https://absensi.nusabot.id/)**
Nomor Induk: *123*
Password: *123*

Untuk *source code* aplikasi dapat mengunjungi repo berikut:
https://github.com/lorenzadam/NusabotAbsensi

## Fitur Mesin Nusabot Absensi

Nusabot Absensi memiliki fitur yang tidak dimiliki mesin absensi pada umumnya dan sistem ini adalah sistem **IoT Based** data yang direkam oleh mesin dikirimkan melalui jaringan internet secara realtime sehingga memungkinkan integrasi data dan pengolahan data secara terpusat dan dapat diakses darimana saja.

!["Skematik"](https://nusabot.id/wp-content/uploads/2021/08/NusabotMesinAbsensi_bb.png "Skematik")

!["Start"](https://nusabot.id/wp-content/uploads/2021/08/WhatsApp-Image-2021-07-25-at-00.45.46.jpeg "Start")

!["Develop"](https://nusabot.id/wp-content/uploads/2021/08/photo_2021-08-06_15-38-35.jpg "Develop")

- Menggunakan ESP8266 agar menunjang komunikasi data melalui WiFi
- Absen masuk, mulai istirahat, selesai istirahat, dan pulang
- Absensi merekam MAC Address dari alat absen sehingga dapat dibuat fitur agar pengguna tidak dapat melakukan absen menggunakan alat yang belum didaftarkan ke sistem.
- Pembagian zona waktu Indonesia (WIB, WITA, WIT).
- Mengatur SSID, Password, dan zona waktu dapat dilakukan melalui hp, laptop, pc, dan perangkat lainnya melalui web browser tanpa harus merubah kode program.
- Absensi melalui RFID (bisa dikembangkan menggunakan media lain).
- Dapat digunakan secara gratis tanpa perlu izin.
- Pengembangan alat menggunakan framework Arduino IDE agar dapat dengan mudah dipelajari oleh pemula.
- Tidak memerlukan RTC karena menggunakan waktu dari server NTP.

## Instalasi dan Kebutuhan

Untuk proses pengembangan dan uji coba alat ini membutuhkan:
1. ESP8266 Development Board (bisa menggunakan Wemos ataupun NodeMCU), untuk dijual ataupun untuk diterapkan di lapangan direkomendasikan menggunakan modul ESP12.
2. OLED
3. RFID-RC522
4. Breadboard dan Kabel
5. Tactile Switch 

## Request Fitur Baru dan Pelaporan Bug
Anda dapat meminta fitur baru maupun melaporkan bug melalui menu **issues** yang sudah disediakan oleh GitHub (lihat menu di atas), posting issues baru dan kita akan berdiskusi disana.

## Berkontribusi

Siapapun dapat berkontribusi pada proyek ini mulai dari pemrograman, pembuakan buku manual, sampai dengan mengenalkan produk ini kepada masyarakat Indonesia agar mengurangi kesenjangan pendidikan teknologi.

## Terimakasih Kepada Para Kontributor
- Nusabot
- Wiku

# Lisensi

Nusabot Mesin Absensi dilisensikan diatas **[GPLV3](https://github.com/lorenzadam/NusabotMesinAbsensi/blob/main/LICENSE "GPLV3")** dan termasuk 100% Free and Open Source Software and Hardware bahkan Anda dapat membuat mesin absensi sendiri dan menjualnya menggunakan rangkaian dan kode program Nusabot Mesin Absensi.
