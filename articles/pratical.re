= 応用編

== Webサーバからの操作
ESP32上でWebサーバを起動させて、LEDの操作とセンサの値読み取りを行います。

 * 必要材料
 ** ESP32 × 1
 ** ブレッドボード × 2
 ** 10kΩ × 1
 ** 100Ω × 1
 ** LED × 1
 ** DHT11 × 1
 ** ジャンプワイヤ

各々の環境に合わせて変数を書き換える必要があります。
以下の変数を書き換えてください。

 * SSID
 ** 変数名: ssid
 * パスワード
 ** 変数名: password

//image[dht11_led][回路図][scale=1.6]{
//}

//image[171017][回路配置図]{
//}
//image[P_20210805_184615][DHT11アップ図]{
//}
//list[d][d]{
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "DHT.h"
#define DHTPIN 4 // センサのデータを読み取るGPIOの番号を指定する
// DHTライブラリはDHT22/DHT11に対応しているので
// 使用するセンサを指定する　
#define DHTTYPE DHT11
DHT dht11(DHTPIN, DHTTYPE); // DHT11のインスタンスを作成する

// WiFi接続用変数
const char *ssid = "ele2o3-b2309f-g";
const char *password = "fedd4123as3u";

String common_html = "\
<!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>ESP32 DashBoard</title>\n\
    <link rel=\"stylesheet\" href=\"/stylesheet.css\" />\n\
</head>\n\
<body>\n\
  <header>\n\
    <div class=\"container\">\n\
      <div class=\"header-title\">\n\
       <div>\n\
       <a id=\"top-btn\" class=\"header-logo\" href=\"/\">ESP32 DashBoard</a>\n\
       </div>\n\
      </div>\n\
    <div class=\"header-menu\">\n\
     <ul class=\"header-menu-right\">\n\
      <li><a href=\"/blink\">Blink</a></li>\n\
      <li><a href=\"/sensor\">Sensor</a></li>\n\
     </ul>\n\
    </div>\n\
    </div>\n\
  </header>\n\
\n";

WebServer server(80);

void handleNotFound() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleRoot() {
  String message = "\
     <div class=\"top-wrapper\">\n\
        <h1>Here is the ESP32 DashBoard</h1>\n\
    </div>\n\
    </body>\n\
    </html>\n\
    \n";
  server.send(200, "text/html", common_html + message);
}

void handleLedBlink() {
  String message = "\
      <div class=\"top-wrapper\">\n\
        <h1>LED Blink</h1>\n\
        <button onclick=\"location.href='/blink/on'\">ON</button>\n\
        <button onclick=\"location.href='/blink/off'\">OFF</button>\n\
    </div>\n\
    </body>\n\
    </html>\n\
  \n";
  server.send(200, "text/html", common_html + message);
}
void handleDHT11() {
  // DHT11のサンプリング間隔が2秒なので
  // センサが値を読むまで2秒待機
  delay(2000);
  float humidity = dht11.readHumidity(); // 湿度取得
  float temperature = dht11.readTemperature(); // 温度取得（デフォルトでは摂氏=℃）
  // NaN（Not a Number）つまり数字を読み取れなかった場合再取得する
  // returnした場合loop()の最初に戻る
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("値が読み取れませんでした");
    return;
  }
  // 体感温度（湿度を含めた体感の温度指数）を計算する
  float apparent_temperature = dht11.computeHeatIndex(temperature, humidity);
  String message = "\
      <div class=\"top-wrapper\">\n\
        <h1>DHT11 Sensor</h1>\n\
        <h2>Temperature: " + String(temperature) + "°C</h2>\n\
        <h2>Humidity: " + String(humidity) + "%</h2>\n\
        <h2>ApparentTemperature: " + String(apparent_temperature) + "%</h2>\n\
        <button onclick=\"location.href='/sensor'\">UPDATE</button>\n\
    </div>\n\
    </body>\n\
    </html>\n\
  \n";
  server.send(200, "text/html", common_html + message);
}

void handleCSS() {
  String message = "\
  @charset \"UTF-8\";* {min-height: 0;min-width: 0;}\n\
  body { margin: 0; font-weight: 400; -webkit-font-smoothing: antialiased;\n\
  font-size: 14px; color: #888; }\n\
  a { text-decoration: none; color: #323a45; \n\
  -webkit-transition: all 0.3s; transition: all 0.3s; }\n\
  a a:hover { color: #5983ff; text-decoration: none; }\n\
  ul { margin: 0; padding: 0; list-style: none; }\n\
  li { margin: 0; padding: 0; list-style: none; }\n\
  .container { width: 1170px; padding-right: 15px; \n\
  padding-left: 15px; margin-right: auto; margin-left: auto; }\n\
  h2,h3,h4,h5,h6 { margin-top: 10px;\n\
  margin-bottom: 10px; font-weight: 400; }\n\
  /*-------  ここからheader  --------*/\n\
  header { height: 50px; position: fixed; top: 0;\n\
  left: 0; right: 0; background-color: #2489c4; line-height: 50px;\n\
  -webkit-box-shadow: -1px 1px 1px rgba(0, 0, 0, 0.1);\n\
  box-shadow: -1px 1px 1px rgba(0, 0, 0, 0.1);\n\
  z-index: 10; }\n\
  .header-title { float: left; }\n\
  .header-logo { color: white; font-weight: 700;\n\
  font-size: 22px; font-family: \"Dosis\", sans-serif; cursor: pointer;}\n\
  .header-menu-right { float: right; }\n\
  .header-menu-right li { float: left; }\n\
  .header-menu-right a { color: #ffffff; font-weight: 700;\n\
  padding: 10px; text-decoration: none; }\n\
  .header-menu-right a:hover { color: #104600;\n\
  -webkit-transition: color 0.3s; transition: color 0.3s;}\n\
  .heading { padding-top: 60px; padding-bottom: 30px; color: #5f5d60;\n\
  text-align: center;}\n\
  .heading h2 {font-weight: normal; }\n\
  /*-------  ここまでheader  --------*/\n\
  .top-wrapper { padding-top: 120px; padding-bottom: 100px;\n\
  color: #5f5d60; text-align: center; }\n\
  \n";

  server.send(200, "text/css", message);
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

  // ESP32のIP
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
  // ネットワークゲートウェイのIP
  Serial.print("Network Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  // DNSServerのIP
  Serial.print("Network DNS Server IP: ");
  Serial.println(WiFi.dnsIP());

  while (!MDNS.begin("ESP32"))
  { // mDNSでESP32という名前を登録する
    Serial.println("Waiting for mDBS to be configured....");
    delay(100);
  }
  Serial.println("Complete mDNS configuration.");


  pinMode(13, OUTPUT); // GPIO13を出力端子として用いる
  dht11.begin(); // DHT11を始動させる

  server.on("/", handleRoot);
  server.on("/blink", handleLedBlink);
  server.on("/blink/on", []() {
    digitalWrite(13, HIGH); // GPIO13に電流を流しLEDを光らせる
    handleLedBlink();
  });
  server.on("/blink/off", []() {
    digitalWrite(13, LOW); // GPIO13に電流を流しLEDを光らせる
    handleLedBlink();
  });
  server.on("/sensor", handleDHT11);
  server.on("/stylesheet.css", handleCSS);

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("WebServer 起動");
}

void loop() {
  server.handleClient();
  delay(5);
}
//}

https://en.wikipedia.org/wiki/.local

//list[ss][WebServer起動時のシリアルモニタ]{
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Connected to Wi-Fi
ESP32 IP: 192.168.2.159
Network Gateway IP: 192.168.2.1
Network DNS Server IP: 192.168.2.1
Complete mDNS configuration.
WebServer 起動
ESP32アクセスポイントのIPアドレスは192.168.4.1
//}

http://esp32.local

//image[202754][Webサーバのトップページ]{
//}
//image[202816][LED操作画面]{
//}
//image[202832][センサ読み取り画面]{
//}

== ESP32でアクセスポイントを設定

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

 * 必要材料
 ** ESP32 × 1
 ** ブレッドボード × 2

各々の環境に合わせて変数を書き換える必要があります。
以下の変数を書き換えてください。

 * SSID
 ** 変数名: ssid
 * パスワード
 ** 変数名: password

//list[a][アクセスポイントプログラム]{
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// ESP32アクセスポイントのSSIDとパスワード（名称自由）
const char *ssid = "ssid";
const char *password = "password";

// ポート80番につなぐWebServerを設定
WebServer server(80);

// エラー時に呼ばれる関数
void handleNotFound()
{
  server.send(400, "text/plain", "not found");
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);          // ESP32をアクセスポイントに設定
  WiFi.softAP(ssid, password); // アクセスポイントモード設定
  delay(100);

  Serial.print("ESP32アクセスポイントのIPアドレスは");
  Serial.print(WiFi.softAPIP());
  Serial.println("です。");

  while (!MDNS.begin("esp32"))
  { // mDNSでESP32という名前を登録する
    Serial.println("Waiting for mDBS to be configured....");
    delay(100);
  }
  Serial.println("Complete mDNS configuration.");

  // WebServerの設定（"/"にアクセスした際の挙動を設定）
  server.on("/", []()
  {
    server.send(200, "text/plain", "ok");
  });
  // WebServerの設定（エラー時の挙動を設定）
  server.onNotFound(handleNotFound);

  server.begin(); // サーバを起動する
  Serial.println("WebServerを起動します");
}

void loop()
{
  // サーバへのアクセスを受け付ける
  server.handleClient();
  delay(5);
}
//}

//list[ds][アクセスポイント起動時のシリアルモニタ]{
ESP32アクセスポイントのIPアドレスは192.168.4.1です。
Complete mDNS configuration.
WebServerを起動します
dhcps: send_nak>>udp_sendto result 0
//}

//image[ssid][アクセスポイント表示画面]{
//}
//image[212841][アクセスポイント接続時画面]{
//}
//image[212909][ESP32のアクセスポイント経由で接続]{
//}
//image[213003][ESP32のアクセスポイント経由でのエラー画面]{
//}