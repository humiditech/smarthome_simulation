# Simulasi Smart Home

## Screenshoot Home-Page
![Screenshot HomePage](https://raw.githubusercontent.com/humiditech/smarthome_simulation/master/SC-Homepage.png)

## Konsep Kerja
Pada projek ini terdiri dari dua bagian utama :
- Web Server (terinstall di Raspberry Pi)
Web server berfungsi untuk menjalankan simulasi Smart Home. 
Web server menggunakan Node.js sebagai bahasa pemrogaman utama, Express.js sebagai server utama, dan ws.js sebagai server websocket yang akan berkomunikasi dengan ESP-01.

* Dokumentasi Node.js : https://nodejs.org/en/
* Dokumentasi Express.js : https://expressjs.com/
* Dokumentasi Websocket : https://www.codepolitan.com/menegtahui-apa-itu-websocket

- ESP-01 Side 