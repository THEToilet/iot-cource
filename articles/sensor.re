= センサーのデータをWeb上に公開しよう

//image[6][今回の目標画面]{
//}

#@#== ESP32用ライブラリのインストール
#@#次にESP32用のライブラリをArduino IDEにインストールします。

#@#@<img>{15-1}のように スケッチ＞ライブラリのインクルード＞ライブラリを管理 を選択してください。
#@#//image[15-1][ライブラリの管理の選択][scale=0.8]{
#@#//}
#@#次に、検索窓にesp32と入力しでてきたesp32ライブラリをインストールしてください（@<img>{16}）。
#@#//image[16][ESP32用ライブラリのインストール][scale=0.8]{
#@#//}
== センサーを使おう

==== 温湿度センサー

温度範囲 0~50℃
湿度範囲20~90℃
動作電圧 3-5.5v
電流供給0.5~2.5mA
読み取りタイミング
一秒間隔
毎秒センサー取得できる
ArduinoIDEを使用したDHT11 / DHT22温度および湿度センサーを備えたESP32
https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/
//image[dht11][dht11]{
//}
//image[9][DHT11用ライブラリのインストール]{
//}

//image[8][依存ライブラリのインストール]{
//}
//image[dht11_1][依存ライブラリのインストール]{
//}
//image[dht11_2][依存ライブラリのインストール]{
//}
//image[dht11_3][依存ライブラリのインストール]{
//}


//list[dht11][dht11]{
#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11
  
DHT dht(DHTPIN, DHTTYPE);
  
void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  // センサーが値を読むまで待機
  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // 体感温度
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F(" Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
}
//}

//list[tmp][tmp]{
Humidity: 56.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.47°C 76.04°F
Humidity: 56.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.47°C 76.04°F
Humidity: 56.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.47°C 76.04°F
//}

== Webに公開しよう

=== Wi-FIと接続する
==== SSIDとは

アクセスポイントの名前
SSID（Service Set Identifier）とはIEEE802.11（Wi-Fi　無線LANの通信規格）で定められているアクセスポイントの識別子のこと
混線を避けるため名付けられている
長さは最大32文字

=== ambientについて

AmbientはIoTデータの可視化サービスです。
https://ambidata.io/
//image[1][ambientのトップページ]{
//}
//image[2][ユーザ登録]{
//}
//image[3][登録完了メール]{
//}
//image[4][ログイン画面]{
//}
チャネルを作成します。
//image[5][チャネル作成完了画面]{
//}
//image[7][ambient用ライブラリのインストール]{
//}

==== ライブラリのインストール

==== 回路図

==== コーディング

//list[amibient][amibient]{
#include "Ambient.h"
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 4
#define PERIOD 30

WiFiClient client;
Ambient ambient;
#define DHTTYPE DHT11 // DHT 11

unsigned int channelId = 39400;            // AmbientのチャネルID(数字)
const char *writeKey = "624168ad3f97c4b9"; // ライトキー

DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(115200);
  WiFi.begin("elecom-b2809f-g", "fapd4rpfac3u"); //  Wi-Fiの初期化

  while (WiFi.status() != WL_CONNECTED)
  { //  Wi-Fiアクセスポイントへの接続待ち
    delay(500);
  }
  dht.begin();
  ambient.begin(channelId, writeKey, &client); //  チャネルIDとライトキーを指定してAmbientの初期化
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  ambient.set(1, h);
  ambient.set(2, t);
  ambient.set(3, hic);

  ambient.send(); //  Ambientにデーターを送信

  delay(PERIOD * 1000);
}
//}
