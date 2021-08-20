= 応用編

== WebサーバからのLチカ

//list[d][d]{
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// WiFi接続用変数
const char *ssid = "elecom-b2809f-g";
const char *password = "fapd4rpfac3u";

WebServer server(80);

void handleNotFound() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleRoot() {
  String message = "\
<html lang=\"ja\">\n\
<meta charset=\"utf-8\">\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
<head>\n\
  <title>Unko</title>\n\
</head>\n\
<body style=\"font-family: sans-serif; background-color: #ffeeaa;\" >\n\
  <h1>UnkoServer</h1>\n\
</body>\n\
</html>\n";
  server.send(200, "text/plain", message);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); // Wi-Fi接続開始
  while (WiFi.status() != WL_CONNECTED) // Wi-Fiアクセスポイントへ接続するまで待機
  {
    Serial.println("Waiting for Wi-Fi connection....");
    delay(500);
  }
  Serial.println("Connected to Wi-Fi");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("GW address: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS address: ");
  Serial.println(WiFi.dnsIP());
  Serial.println("");

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
}

void loop() {
  server.handleClient();
  delay(5);
}
//}

https://en.wikipedia.org/wiki/.local

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

//list[a][a]{
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// WiFi接続用変数
const char *ssid = "ssid";
const char *password = "password";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
//}
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
  "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package→
_esp32_index.json"
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