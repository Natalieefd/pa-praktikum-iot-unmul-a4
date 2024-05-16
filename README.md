<a name="top"></a>

<div align="center">  

# PA-PRAKTIKUM-IOT-UNMUL-A4

| NIM | NAMA |
|------------|:----------------------:|
| 2109106040 | Natalie Fuad |
| 2109106045 | Muhammad Irsyadul Asyrof Haryono |
| 2109106050 | Sherina Laraswati |
<br>
</div>

<div align="center">
  
## IMPLEMENTASI SISTEM IOT PADA KETERSEDIAAN PARKIR MOBIL MENGGUNAKAN SENSOR JARAK
<br>
</div>

## DESKRIPSI
Rangkaian ini mendeteksi objek pada sebuah parkir mobil menggunakan sensor jarak. Sensor akan terus mengirim jarak ke NODEMCU, jika tidak terdeteksi objek yang berjarak kurang dari 4 cm dengan sensor, LED akan terus menyala dan jika tombol "cek parkir" pada platform blynk diklik buzzer akan menyala selama 5 detik. Ketika sensor mendeteksi objek dan jika jarak objek dengan sensor sekitar kurang dari 4 cm, maka LED akan mati dan buzzer tidak akan bersuara. Untuk monitoring jarak dapat dilihat pada platform blynk dan mqtt.

## PEMBAGIAN TUGAS

`040_Natalie Fuad`       = Membuat readme pada github, mengatur logika sensor jarak, led dan buzzer, mengatur konfigurasi master node ke mqtt dan menyusun manual book
<br>
`047_Muhammad Irsyadul A F`  = Mengatur konfigurasi bylnk, mengatur konfigurasi edge node dan master node ke bylnk, dan menyusun manual book
<br>
`050_Sherina Laraswati`  = Membuat rangkaian design schematic, membuat rangkaian master node dan edge node, mengatur konfigurasi mqtt, dan menyusun manual book


## KOMPONEN YANG DIGUNAKAN
- Bread Board : sebagai tempat rangkaian komponen
- ESP8266 : untuk menghubugkan komponen ke internet melalui WIFI
- Kabel Jumper : untuk menyambungkan komponen elektronik satu sama lain
- LED : untuk menampilkan cahaya
- Resistor : untuk menghabat arus listrik
- Buzzer : untuk peringatan jarak kolom parkir berupa suara
- Sensor Jarak (HC-SR04) : untuk mendeteksi jarak berupa gelombang ultrasonik


## RANGKAIAN

- DESIGN SCHEMATIC
<div align="center">
  
<img src="https://github.com/Natalieefd/pa-praktikum-iot-unmul-a4/blob/main/Lampiran/design_schematic.png">

</div>

<br>

<!--
  
- OUR SCHEMATIC
<div align="center">

<b>Master Node (Publisher)</b><br>

<img src="https://github.com/Natalieefd/pa-praktikum-iot-unmul-a4/blob/main/Lampiran/rangkaian_master_node.png">

<br><b>Edge Node (Subscriber)</b><br>

<img src="https://github.com/Natalieefd/pa-praktikum-iot-unmul-a4/blob/main/Lampiran/rangkaian_edge_node.png">

</div>

<br>

-->
  
<div align="center">

  [Back To Top](top)

</div>

