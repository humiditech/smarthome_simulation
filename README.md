# Simulasi Smart Home

## Screenshoot Home-Page
![Screenshot HomePage](https://raw.githubusercontent.com/humiditech/smarthome_simulation/master/SC-Homepage.png)

## Konsep Kerja
Pada projek ini terdiri dari dua bagian utama :
#### 1. Web Server (terinstall di Raspberry Pi)

Web server berfungsi untuk menjalankan simulasi Smart Home. 
Web server menggunakan Node.js sebagai bahasa pemrogaman utama, Express.js sebagai server utama, dan ws.js sebagai server websocket yang akan berkomunikasi dengan ESP-01. Pada saat ada perubahan event dari homepage simulasi smarthome, webserver akan melakukan broadcast message websocket
ke semua ESP-01.

* Dokumentasi Node.js : https://nodejs.org/en/
* Dokumentasi Express.js : https://expressjs.com/
* Dokumentasi Websocket : https://www.codepolitan.com/menegtahui-apa-itu-websocket

#### 2. ESP-01 Side 

Pada ESP-01, berfungsi untuk menerima data dari Webserver dan menjalankan nya ke aktuator. Komunikasi data menggunakan websocket sehingga
dapat terjadi komunikasi lebih cepat dan realtime. Data yang diterima dari webserver dalam format json sehingga perlu di parsing menggunakan
library ArduinoJson. Ketika mendapatkan broadcast message websocket, ESP-01 akan melakukan parsing dan menentukan apa yang harus dilakukan 
oleh aktuator.