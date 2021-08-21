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
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
server.send(200, "text/plain", message);
}

void handleLedBlink(){
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", message);
}
void handleDHT11(){
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", message);
}

void handleWeatherAPI(){
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", "weaher");
}

void setup() {
  Serial.begin(115200);
//  WiFi.mode(WIFI_STA);
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
  server.on("/blink", handleLedBlink);
  server.on("/sensor", handleDHT11);
  server.on("/weather", handleWeatherAPI);

/*
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  */

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
#include <WebServer.h>
#include <ESPmDNS.h>

// WiFi接続用変数
const char *ssid = "ssid";
const char *password = "password";


WebServer server(80);

void handleNotFound() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleRoot() {
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
server.send(200, "text/plain", message);
}

void handleLedBlink(){
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", message);
}
void handleDHT11(){
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", message);
}

void handleWeatherAPI(){
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
    <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", "weaher");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  delay(100);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");

   if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/blink", handleLedBlink);
  server.on("/sensor", handleDHT11);
  server.on("/weather", handleWeatherAPI);

/*
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  */

  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(5);
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