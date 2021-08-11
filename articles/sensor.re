= センサのデータをWeb上に公開しよう

この章ではIoTの定番であるセンサを使ってデータを取得します。
目標として、温湿度センサで得たデータをWeb上に公開します。

== センサを使おう
センサとは温度や湿度、匂いなどの様々な情報を信号化して機械が使いやすいようにするものです。
この章では、手軽で身近である温湿度を計測できる温湿度センサを使用します。

==== 温湿度センサ
温湿度センサはその字の通り温度と湿度を計測してくれます。
使用するセンサはDHT11（@<img>{dht11_1}）というもので、取得した温湿度データをデジタル出力をしてくれます。
//image[dht11_1][DHT11][scale=0.9]{
//}
DHT11の主な仕様は以下の通りです（@<table>{DHT11}）。

//table[DHT11][DHT11の主な仕様]{
温度範囲	-20 ~ - ℃
湿度範囲	5 ~ 95 ％
サンプリング間隔	2秒に一回
//}

4本あるピン（@<img>{dht11_1}）はそれぞれ@<table>{DHT11_pin}のような用途で使われます。

//table[DHT11_pin][DHT11のピンについて]{
ピンの番号	ピンの用途
1	Vdd 3.3 ~ 5.5V の直流を流す
2	データ出力用ピン
3	なにも接続しない
4	GND
//}

==== DHT11用ライブラリのインストール
DHT11をESP32上で使うためにDHT11ライブラリをArduino IDEにインストールします。

@<img>{15-1}のように（スケッチ＞ライブラリのインクルード＞ライブラリを管理）を選択してください。

//image[15-1][ライブラリの管理の選択][scale=0.8]{
//}

選択するとライブラリマネージャーが開かれるので、検索窓に「DHT11」を入力してください（@<img>{9}）。
その後、DHT sensor library をインストールしてください。

//image[9][DHT11用ライブラリのインストール][scale=0.8]{
//}

インストールを選択すると依存ライブラリの追加インストールについて聞かれるので@<strong>{Install all}を
選択してください（@<img>{8}）。

//image[8][依存ライブラリのインストール][scale=0.8]{
//}

==== DHT11を使って温湿度を測る
ここで実際にDHT11を使ってみましょう。
@<img>{dht11}と@<img>{P_20210805_184541}また@<img>{P_20210805_184615}を参考に回路を組んでください。抵抗は10kΩを使用しています。

//image[dht11][DHT11回路図][scale=1.5]{
//}

//image[P_20210805_184541][DHT11回路配置図][scale=0.7]{
//}
//image[P_20210805_184615][DHT11アップ図][scale=0.7]{
//}

//list[dht11][DHT11実行プログラム]{
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

  Serial.printf("温度: %.3lf ℃\n", temperature);
  Serial.printf("湿度: %.3lf ％\n", humidity);
  Serial.printf("体感温度: %.3lf ℃\n", apparent_temperature)
}
//}

プログラムの書き込みと、回路の配置に成功するとシリアルモニタにデータが送られてきます。
「値が読み取れませんでした」が表示されている部分は試しにセンサを抜いたためです。

//list[tmp][シリアルモニタ]{
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
外出時に自分の部屋の温湿度を知りたいことはありませんか？
外部のサーバにデータを送信することで、外出時も自宅のデータをWebで見ることができます。

=== Wi-FIと接続する
外部のサーバに接続するために、まずWi-Fiに接続します。
Wi-Fiに接続するために必要な情報は以下の二つです。
プログラムを書き込む際に必要になるので準備をしておいてください。

 * SSID（Service Set Identifier）
 ** SSIDとはWi-Fi、無線LANの通信規格（IEEE802.11）で定められているアクセスポイントのを識別するための名称。芝浦で言うところの「SRAS-WPA」など。
 * パスワード
 ** 指定したSSIDのアクセスポイントに接続する際に必要なパスワード1

=== Ambient
外出時に自宅のセンサのデータをWeb上で見るために、
センサから取得したデータを外部のサーバに送信しますが、
その外部のサーバとしてAmbientを使用します。

AmbientはIoTデータの可視化サービスです。
データをグラフとして表示してくれるだけでなく、データを利用した
様々なカスタマイズができます。

以下のリンクにアクセスしてAmbientのトップページに移動してください（@<img>{1}）。

@<href>{https://ambidata.io/}

//image[1][Ambientのトップページ]{
//}

Ambientを利用するために、まずユーザ登録をします。
@<strong>{ユーザ登録（無料）}を選択してユーザ登録画面に移動してください（@<img>{2}）。
その後、メールアドレスとパスワードを入力してユーザ登録をしてください。

//image[2][ユーザ登録]{
//}

ユーザ登録をすると登録したメールアドレスに登録完了メールが届きます（@<img>{3}）。
このメールに添付してあるリンクにアクセスすることユーザ登録完了です。

//image[3][登録完了メール]{
//}

ユーザ登録完了後、ログイン画面にアクセスしログインしてください（@<img>{4}）。

//image[4][ログイン画面]{
//}

ログイン後、@<strong>{チャネルを作る}を選択し、チャネルを作成することでAmbientの設定は完了です。

//image[5][チャネル作成完了画面]{
//}

プログラムを書き込む際に必要な情報として以下の二つがあるので、メモをしておいてください。

 * チャネルID
 * ライトキー

==== ライブラリのインストール
AmbientをESP32上で使うためにAmbientライブラリをArduino IDEにインストールします。

@<img>{15-1}のように（スケッチ＞ライブラリのインクルード＞ライブラリを管理）を選択してください

ライブラリマネージャーの検索窓に「Ambient」と入力し、候補に出てくる「Ambient ESP32 ESP8266 lib」をインストールしてください。

//image[7][ambient用ライブラリのインストール][scale=0.8]{
//}

=== Ambientにデータを送る
ここで実際にAmbientにデータを送ります。
DHT11を使用するので回路図は@<img>{P_20210805_184541}を利用してください。
プログラムは@<list>{amibient}を書き込んでください。
各々の環境に合わせて変数を書き換える必要があります。
以下の変数を書き換えてください。

 * SSID
 ** 変数名: ssid
 * パスワード
 ** 変数名: password
 * チャネルID
 ** 変数名: channel_id
 * ライトキー
 ** 変数名: write_key

//list[amibient][Ambient利用プログラム]{
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

  Serial.printf("温度: %.3lf ℃\n", temperature);
  Serial.printf("湿度: %.3lf ％\n", humidity);
  Serial.printf("体感温度: %.3lf ℃\n", apparent_temperature)

  ambient.set(1, temperature);  // チャート1に温度データ登録
  ambient.set(2, humidity);  // チャート2に湿度データ登録
  ambient.set(3, apparent_temperature);  // チャート3に体感温度データ登録

  ambient.send();  // 登録データ送信
  Serial.println("Ambientにデータを送信しました");
}
//}

プログラムの実行に成功するとシリアルモニタに以下のように表示されます（@<list>{ambient_console}）。
Wi-Fiのコネクションが完了した後、5秒ごとにDHT11より取得したデータをAmbientに送信します。

//list[ambient_console][シリアルモニタ画面]{
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

Ambientとの通信に成功していると@<img>{graph}のように表示されます。
ただし@<img>{graph}はプログラムを開始してから数分経過後のグラフです。

//image[graph][Ambientに表示されるグラフ]{
//}