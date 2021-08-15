= 応用編

== WebサーバからのLチカ
== 2台のESP32を使ってピンポンする 

 サーバクライアント
  Interface 2018 9より
  Wi-FIネットワークはアクセス・ポイント（AP）を中心としたネットワーク
  	アクセスポイントは多くの場合、インターネットなどの他のネットワークに接続しており、その場合はルータとも呼ばれる
  	アクセス・ポイントに接続する端末をステーション（STA）という
  ESP32をAPモードするには
  > WiFi.softAP(ssid, password);
  STAモードでアクセスポイントに接続するには
  > WiFi.begin(ssid, password);

 WiFiのアクセスポイントがなくてもESP32が2府あれば、片方をアクセスポイントにして通信できる

== VScodeからESP32にスケッチを書き込む

まず、拡張機能の検索窓に「Arduino」と入力してArduinoの拡張機能をインストールしてください（@<img>{1}）。
//image[1][拡張機能でArduinoをInstall]{
//}

つぎにCtrl Shift P
を押してコマンドパレットを開いてください。

//image[2][2]{
//}

 arduino serial
//image[3][3]{
//}
/mnt/c/Users/Document/Arduino

//image[4][4]{
//}
serial port 選択
//image[5][5]{
//}
ボード選択

//image[6][6]{
//}
//image[7][7]{
//}
//image[8][8]{
//}
//list[json][json]{
"arduino.additionalUrls": [
  "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json"
],
//}
//image[9][9]{
//}

//image[10][10]{
//}
arduino bord maneger
//image[11][11]{
//}
//image[12][12]{
//}
//image[13][13]{
//}
 Arduino IDEのほうを動かしているとうまくいかない

 インクルードパスの設定
 c_cpp_properties.json
  ctrl shift P
 select sketch
 でビルドしたいファイルを選択
 https://garretlab.web.fc2.com/arduino/introduction/vscode/

//image[14][14]{
//}