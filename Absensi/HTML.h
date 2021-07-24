//halaman html
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<style>
input[type=text], select {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}

input[type=submit] {
  width: 100%;
  background-color: #4CAF50;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

input[type=submit]:hover {
  background-color: #45a049;
}

div {
  border-radius: 5px;
  background-color: #f2f2f2;
  padding: 20px;
}
</style>
<body>

<h3>Pengaturan Alat | Nusabot</h3>

<div>
  <form action="/action_page">
    <label for="ssid">SSID</label>
    <input type="text" id="fname" name="ssidNew" placeholder="SSID WiFi Anda">

    <label for="pass">Password</label>
    <input type="text" id="pass" name="passNew" placeholder="Kosongkan jika tidak menggunakan password">

    <label for="zona">Zona Waktu</label>
    <select id="zona" name="zona">
      <option value="25200">WIB</option>
      <option value="28800">WITA</option>
      <option value="32400">WIT</option>
    </select>

    <input type="submit" value="Simpan">
  </form>
</div>

</body>
</html>

)rawliteral";


const char sukses_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <style>
        div {
            position: fixed;
            top: 50%;
            left: 50%;
            margin-top: -100px;
            margin-left: -200px;
        }
    </style>
    <title>Selamat Datang | Nusabot</title>
  </head>
  <body>
    <div>
        <h1>Pengaturan Tersimpan</h1>
    <div>
  </body>
</html>

)rawliteral";
