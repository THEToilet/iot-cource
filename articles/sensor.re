= センサのデータをWeb上に公開しよう

今回は温湿度センサで得たデータをWeb上に公開することが目標です。

//image[6][今回の目標画面]{
//}

== センサを使おう

==== 温湿度センサ
//table[DHT11][DHT11データシート]{
温度範囲	-20~℃
湿度範囲	-20~℃
サンプリング間隔	2秒に一回
//}

//image[dht11_1][dhtの概要]{
//}
//table[DHT11_pin][DHT11のピンについて]{
ピンの番号	ピンの内容
1	VDD power supply 3.3 ~ 5.5V DC
2	DATA serial DATA, single bus
3	NC empty feet
4	GND grounding, power supply negative
//}
==== DHT11用ライブラリのインストール
次にESP32用のライブラリをArduino IDEにインストールします。

@<img>{15-1}のように スケッチ＞ライブラリのインクルード＞ライブラリを管理 を選択してください。
//image[15-1][ライブラリの管理の選択][scale=0.8]{
//}
//image[9][DHT11用ライブラリのインストール]{
//}
//image[8][依存ライブラリのインストール]{
//}

==== DHT11を使って温湿度を測る

//image[dht11][dht11回路図]{
//}

//list[dht11][dht11]{
#include "DHT.h"
#define DHTPIN 4  // センサのデータを読み取るGPIOの番号を指定する

// DHTライブラリはDHT22/DHT11に対応しているので
// 使用するセンサを指定する　
#define DHTTYPE DHT11

DHT dht11(DHTPIN, DHTTYPE);  // DHT11のインスタンスを作成する

void setup() {
  Serial.begin(115200);
  dht11.begin();  // DHT11を始動させる
}

void loop() {
  // DHT11のサンプリング間隔が2秒なので
  // センサが値を読むまで2秒待機
  delay(2000);

  float humidity = dht11.readHumidity();  // 湿度取得
  float temperature = dht11.readTemperature();  // 温度取得（デフォルトでは摂氏=℃）

  // NaN（Not a Number）つまり数字を読み取れなかった場合再取得する
  // returnした場合loop()の最初に戻る
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("値が読み取れませんでした");
    return;
  }

  // 体感温度（湿度を含めた体感の温度指数）を計算する
  float apparent_temperature = dht11.computeHeatIndex(temperature, humidity);

  Serial.print("温度: "); Serial.print(temperature); Serial.print("℃ ");
  Serial.print("湿度: "); Serial.print(humidity); Serial.print("% ");
  Serial.print("体感温度: "); Serial.print(apparent_temperature); Serial.println("℃");
}
//}

//list[tmp][tmp]{
温度: 24.00℃ 湿度: 59.00% 体感温度: 18.87℃
温度: 23.80℃ 湿度: 58.00% 体感温度: 18.61℃
温度: 23.80℃ 湿度: 59.00% 体感温度: 18.65℃
温度: 23.80℃ 湿度: 59.00% 体感温度: 18.65℃
温度: 23.80℃ 湿度: 59.00% 体感温度: 18.65℃
温度: 23.80℃ 湿度: 59.00% 体感温度: 18.65℃
温度: 23.80℃ 湿度: 61.00% 体感温度: 18.75℃
値が読み取れませんでした
値が読み取れませんでした
値が読み取れませんでした
温度: 24.50℃ 湿度: 83.00% 体感温度: 20.55℃
温度: 24.60℃ 湿度: 75.00% 体感温度: 20.28℃
温度: 24.70℃ 湿度: 71.00% 体感温度: 20.21℃
温度: 24.80℃ 湿度: 67.00% 体感温度: 20.13℃
温度: 24.80℃ 湿度: 64.00% 体感温度: 19.99℃
温度: 24.80℃ 湿度: 62.00% 体感温度: 19.89℃
温度: 24.80℃ 湿度: 61.00% 体感温度: 19.85℃
温度: 24.90℃ 湿度: 59.00% 体感温度: 19.86℃
温度: 24.80℃ 湿度: 58.00% 体感温度: 19.71℃

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
#include <WiFi.h>
#include "DHT.h"
#include "Ambient.h"
#define DHTPIN 4  // センサのデータを読み取るGPIOの番号を指定する

// DHTライブラリはDHT22/DHT11に対応しているので
// 使用するセンサを指定する　
#define DHTTYPE DHT11

// Ambient用変数
unsigned int channel_id = 40076;
const char *write_key = "b94c1123733aec95";

// WiFi接続用変数
const char *ssid = "elecom-b2809f-g";
const char *password = "fapd4rpfac3u";

DHT dht11(DHTPIN, DHTTYPE);  // DHT11のインスタンスを作成する
Ambient ambient;  // Ambientのインスタンスを作成する
WiFiClient wifi_client;  // Ambientに接続するためのクライアントを用意

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);  // Wi-Fi接続開始

  while (WiFi.status() != WL_CONNECTED) // Wi-Fiアクセスポイントへ接続するまで待機
  {
    Serial.println("Waiting for Wi-Fi connection....");
    delay(500);
  }
  Serial.println("Connected to Wi-Fi");
  dht11.begin();  // DHT11を始動させる
  ambient.begin(channel_id, write_key, &wifi_client);
}

void loop() {
  // DHT11のサンプリング間隔は2秒ですが
  // Amibentのデータ送信間隔は最低でも5秒間隔を開ける
  // 必要があるので5秒待機
  delay(30000);

  float humidity = dht11.readHumidity();  // 湿度取得
  float temperature = dht11.readTemperature();  // 温度取得（デフォルトでは摂氏=℃）

  // NaN（Not a Number）つまり数字を読み取れなかった場合再取得する
  // returnした場合loop()の最初に戻る
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("値が読み取れませんでした");
    return;
  }

  // 体感温度（湿度を含めた体感の温度指数）を計算する
  float apparent_temperature = dht11.computeHeatIndex(temperature, humidity);

  Serial.print("温度: "); Serial.print(temperature); Serial.print("℃ ");
  Serial.print("湿度: "); Serial.print(humidity); Serial.print("% ");
  Serial.print("体感温度: "); Serial.print(apparent_temperature); Serial.println("℃");

  ambient.set(1, temperature);  // チャート1に温度データ登録
  ambient.set(2, humidity);  // チャート2に湿度データ登録
  ambient.set(3, apparent_temperature);  // チャート3に体感温度データ登録

  ambient.send();  // 登録データ送信
  Serial.println("Ambientにデータを送信しました");
}
//}

//emlist{
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Waiting for Wi-Fi connection....
Connected to Wi-Fi
温度: 24.70℃ 湿度: 63.00% 体感温度: 19.83℃
Ambientにデータを送信しました
温度: 24.70℃ 湿度: 61.00% 体感温度: 19.74℃
Ambientにデータを送信しました
温度: 24.70℃ 湿度: 61.00% 体感温度: 19.74℃
Ambientにデータを送信しました
温度: 24.60℃ 湿度: 61.00% 体感温度: 19.63℃
Ambientにデータを送信しました
温度: 24.50℃ 湿度: 61.00% 体感温度: 19.52℃
Ambientにデータを送信しました
温度: 24.40℃ 湿度: 61.00% 体感温度: 19.41℃
Ambientにデータを送信しました
温度: 24.40℃ 湿度: 61.00% 体感温度: 19.41℃
Ambientにデータを送信しました
//}