= WebAPIを使おう

=== WebAPIとは？
Application Programming Interface
コンテキストによって様々な使い方がされている
Twitter

== Weather APIを使う
天気を知れるAPIが様々ありますが、ここでは「Weather API」というものを利用します。
以下のリンクにアクセスしてWeather APIのトップページに移動してください（@<img>{1}）。

Weather API: @<href>{https://www.weatherapi.com/}

//image[1][WeatherAPIのトップページ]{
//}

Weather APIを利用するためにまず、ユーザ登録をします。
@<strong>{Signup}を選択してユーザ登録画面に移動してください（@<img>{2}）。
登録をするために、メールアドレスとパスワードを入力し@<strong>{Sign up}を選択してください。

//image[2][登録画面]{
//}

ユーザ登録が完了すると登録メールアドレスに認証メールが届くので（@<img>{11}）
リンク先にアクセスをしてユーザ登録を完了してください。

//image[11][認証メール]{
//}

その後、登録情報をもとにログインをしてください（@<img>{3}）。

//image[3][ログイン画面]{
//}

ログイン後はマイページに遷移します（@<img>{4}）。
この際ページ上部の

 * API key

はWeather APIを使用する際の認証に使うのでメモをしておいてください。
次にWeather APIの仕様を確認するために@<strong>{API Explorer}を選択してください。

//image[4][マイページ]{
//}

@<img>{5}

//image[5][APIの試行ページ]{
//}

Call
@<href>{https://api.weatherapi.com/v1/current.json?key=********&q=Saitama&aqi=no}

//list[ResponesCod][ResponesCode]{
200
//}

//list[ResponesHeader][ResponesHeader]{
{
    "Transfer-Encoding": "chunked",
    "Connection": "keep-alive",
    "Vary": "Accept-Encoding",
    "CDN-PullZone": "93447",
    "CDN-Uid": "8fa3a04a-75d9-4707-8056-b7b33c8ac7fe",
    "CDN-RequestCountryCode": "FI",
    "CDN-EdgeStorageId": "615",
    "CDN-CachedAt": "2021-07-12 14:05:36",
    "CDN-RequestPullSuccess": "True",
    "CDN-RequestPullCode": "200",
    "CDN-RequestId": "a45be49d32c7a76559a3f3920d337f53",
    "CDN-Cache": "MISS",
    "Cache-Control": "public, max-age=180",
    "Content-Type": "application/json",
    "Date": "Mon, 12 Jul 2021 12:05:36 GMT",
    "Server": "BunnyCDN-FI1-615"
}
//}

//list[ResponseBody][ResponseBody]{
{
      "location": {
          "name": "Saitama",
          "region": "Saitama",
          "country": "Japan",
          "lat": 35.91,
          "lon": 139.66,
          "tz_id": "Asia/Tokyo",
          "localtime_epoch": 1626091536,
          "localtime": "2021-07-12 21:05"
      },
      "current": {
          "last_updated_epoch": 1626087600,
          "last_updated": "2021-07-12 20:00",
          "temp_c": 29.4,
          "temp_f": 84.9,
          "is_day": 0,
          "condition": {
              "text": "Partly cloudy",
              "icon": "//cdn.weatherapi.com/weather/64x64/night/116.png",
              "code": 1003
          },
          "wind_mph": 7.6,
          "wind_kph": 12.2,
          "wind_degree": 162,
          "wind_dir": "SSE",
          "pressure_mb": 1010.0,
          "pressure_in": 30.3,
          "precip_mm": 0.0,
          "precip_in": 0.0,
          "humidity": 61,
          "cloud": 47,
          "feelslike_c": 32.1,
          "feelslike_f": 89.8,
          "vis_km": 10.0,
          "vis_miles": 6.0,
          "uv": 7.0,
          "gust_mph": 9.2,
          "gust_kph": 14.8
    }
}
//}

この形式をJSON（JavaScript Object Node）と言います。

=== HTTPとは
@<href>{http://den3.net/activity_diary/2021/02/01/2718/}

このブログを見ている時点であなたはHTTPを使用していることになります。
![](http://den3.net/wp-content/uploads/2021/01/スクリーンショット-2021-01-25-173558.png)
電算のホームページにアクセスした際に行われている通信内容。

![](http://den3.net/wp-content/uploads/2021/01/20191025011652-300x300.png)
このサイトがhttpsじゃない点については早急に対応したいと思います。

### HTTPとは
TCP/IPをベースにしたアプリケーション層のプロトコルです。
HTTPはリクエスト/レスポンス型のプロトコルであり、クライアントはリクエストを出した場合レスポンスが返ってくるまで待機します。
あとステートレスなのが特徴です。

### HTTPメッセージ
リクエストメッセージとレスポンスメッセージのことはまとめてHTTPメッセージと呼ばれます。
![](http://den3.net/wp-content/uploads/2021/01/スクリーンショット-2021-01-31-235422.png)

#### スタートライン
　ここではリクエストメッセージとレスポンスメッセージで書かれている内容が異なり総称としてスタートラインと呼ばれています。
　リクエストメッセージではリクエストラインを用います。内容としては、メソッド(後述),リクエストURI,プロトコルバージョン(HTTP/1.1)が書かれており、
  レスポンスメッセージではステータスラインを用いステータスコード(後述)などが書かれています。
#### ヘッダ
　メッセージのメタデータについて書いています(データについての付加情報)
#### ボディ
　メッセージが入ります　よくあるのがJson化したデータやHTMLなどがここに入っています。
### HTTPメソッド
前述したようにHTTPにはメソッドと呼ばれているHTTPリクエストの種類を表すものがあります。
本当は8つのメソッドがあるのですが今回は
CURD(Create, Update, Read, Delete)と呼ばれる性質を満たす代表的なメソッド

 * GET
 * POST
 * PUT
 * DELETE

の四つを紹介したいと思います。

##### GET
リソースの取得

ブログの記事を取得した例
![](http://den3.net/wp-content/uploads/2021/02/スクリーンショット-2021-02-01-004533.png)
##### POST

リソースの追加、作成
ブログなどを投稿するときにはこのメソッドが呼ばれます。

コメントを投稿した際の例
![](http://den3.net/wp-content/uploads/2021/02/スクリーンショット-2021-02-01-004715.png)
![](http://den3.net/wp-content/uploads/2021/02/スクリーンショット-2021-02-01-004705.png)
![](http://den3.net/wp-content/uploads/2021/02/スクリーンショット-2021-02-01-004631.png)

 * PUT
 ** リソースの作成、更新
 ** ブログを更新したいときに使います。
 * DELETE
 ** リソースの削除
 ** 投稿などを削除した時に使われます。



### ステータスコード
前述したとおりHTTPはリクエスト/レスポンス型のプロトコルなので
リクエストを送るとレスポンスが返ってきます代表的なのは下の画像に書いてあるStatus Codeに書いてある200 OKとかです

![](http://den3.net/wp-content/uploads/2021/01/スクリーンショット-2021-01-31-234745.png)
意味としては
 * 2xx
 ** リクエスト成功
 ** ex: 200 OK
 * 3xx
 ** リダイレクトを行うときに返ってくる
 * 4xx
 ** クライアントエラー
 ** クライアントが送った処理が間違っている
 ** ex: 404 not found
 * 5xx
 ** サーバエラー
 ** サーバ内でエラーが発生している
 ** ex: 500 Internal Server Error
などがあります

### 参照
山本 陽平. Webを支える技術 ―― HTTP，URI，HTML，そしてREST WEB+DB PRESS plus  株式会社技術評論社.

=== ESP32でJSONを利用する
これらの形式が、WeatherAPIから帰ってくるため、ESP32側で使えるようにしなければなりません
そこで、公開されているライブラリであるarduinoJSONを利用します。

 JSONドキュメントを作る時にキャパシティを計算する必要がある
 ArduinoJson Assistant
 https://arduinojson.org/v6/assistant/

//image[6][ArudinoAssistantのトップページ]{
//}
//image[7][JSONの大きさ設定]{
//}
//image[8][JSONのサイズ確認画面]{
//}


//list[world][最初のプログラム]{
// String input;

  StaticJsonDocument<1536> doc;

  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  JsonObject location = doc["location"];
  const char* location_name = location["name"]; // "Saitama"
  const char* location_region = location["region"]; // "Saitama"
  const char* location_country = location["country"]; // "Japan"
  float location_lat = location["lat"]; // 35.91
  float location_lon = location["lon"]; // 139.66
  const char* location_tz_id = location["tz_id"]; // "Asia/Tokyo"
  long location_localtime_epoch = location["localtime_epoch"]; // 1626533912
  const char* location_localtime = location["localtime"]; // "2021-07-17 23:58"

  JsonObject current = doc["current"];
  long current_last_updated_epoch = current["last_updated_epoch"]; // 1626533100
  const char* current_last_updated = current["last_updated"]; // "2021-07-17 23:45"
  float current_temp_c = current["temp_c"]; // 23.3
  float current_temp_f = current["temp_f"]; // 73.9
  int current_is_day = current["is_day"]; // 0

  JsonObject current_condition = current["condition"];
  const char* current_condition_text = current_condition["text"]; // "Clear"
  const char* current_condition_icon = current_condition["icon"];
  int current_condition_code = current_condition["code"]; // 1000

  float current_wind_mph = current["wind_mph"]; // 3.8
  float current_wind_kph = current["wind_kph"]; // 6.1
  int current_wind_degree = current["wind_degree"]; // 250
  const char* current_wind_dir = current["wind_dir"]; // "WSW"
  int current_pressure_mb = current["pressure_mb"]; // 1019
  float current_pressure_in = current["pressure_in"]; // 30.6
  int current_precip_mm = current["precip_mm"]; // 0
  int current_precip_in = current["precip_in"]; // 0
  int current_humidity = current["humidity"]; // 88
  int current_cloud = current["cloud"]; // 0
  float current_feelslike_c = current["feelslike_c"]; // 24.9
  float current_feelslike_f = current["feelslike_f"]; // 76.9
  int current_vis_km = current["vis_km"]; // 16
  int current_vis_miles = current["vis_miles"]; // 9
  int current_uv = current["uv"]; // 1
  float current_gust_mph = current["gust_mph"]; // 13.9
  float current_gust_kph = current["gust_kph"]; // 22.3
//}

==== JSONのライブラリをインストールする
JSONをESP32上で使うためにライブラリをArduino IDEにインストールします。

@<img>{15-1}のように（スケッチ＞ライブラリのインクルード＞ライブラリを管理）を選択してください。

//image[15-1][ライブラリの管理の選択][scale=0.8]{
//}

選択するとライブラリマネージャーが開かれるので、検索窓に「ArduinoJSON」を入力してください（@<img>{9}）。
その後、「ArduinoJson」をインストールしてください
//image[9][ArduinoJson用ライブラリのインストール]{
//}

=== Weather APIからデータを取得する
ここで、実際にWeatherAPIからデータを取得してみます。
@<list>{w}のプログラムをESP32に書き込んでください。
各々の環境に合わせて変数を書き換える必要があります。
以下の変数を書き換えてください。

 * SSID
 ** 変数名: ssid
 * パスワード
 ** 変数名: password
 * API Key
 ** Weaher APIに用いるAPI Key
 ** 変数名: api_key
 * 地名
 ** Weather APIで取得したい地名
 ** 変数名: location

//list[w][Weaher APIとの通信]{
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi接続用変数
const char *ssid = "elecom-b2809f-g";
const char *password = "fapd4rpfac3u";

// WeatherAPI用変数
const String api_key = "ffe99ee9ec094d3681d74132211106";
const String location = "Saitama";

struct Weather {
  const char *region;
  float temperature;
  int humidity;
};

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);  // Wi-Fi接続開始

  while (WiFi.status() != WL_CONNECTED) // Wi-Fiアクセスポイントへ接続するまで待機
  {
    Serial.println("Waiting for Wi-Fi connection....");
    delay(500);
  }
  Serial.println("Connected to Wi-Fi");
}

void loop()
{
  HTTPClient http;
  String target_url = "https://api.weatherapi.com/v1/current.json?key=" + api_key + "&q=" + location + "&aqi=no";
  http.begin(target_url);  // HTTP通信を開始する

  int http_code = http.GET();  // HTTP通信でGETする

  Serial.printf("status code : %d\n", http_code);
  if (http_code > 0)  // HTTP通信が失敗すると負値になる
  {
    if (http_code == HTTP_CODE_OK)  // HTTPコードが200の場合成功
    {
      String payload = http.getString();  // HTTPのレスポンスボディを取得
      Serial.println(payload);
      Weather weather = parse(payload);  // WeatherAPIのJSONをパースする
      Serial.println("------weather--------");
      Serial.println(weather.region);
      Serial.println(weather.temperature);
      Serial.println(weather.humidity);
    }
    else if (http_code > 500) {
      Serial.printf("Server Error: %d", http_code);
    }
    else if (http_code > 400) {
      Serial.printf("Client Error: %d", http_code);
    }
  }
  else
  {
    Serial.println(http.errorToString(http_code).c_str());
  }
  http.end();  // HTTP通信の終了
  delay(60000);
}

Weather parse(String input)
{
  Serial.println("parse.......");
  StaticJsonDocument<1536> doc;  // JSONをパースするための領域を作成
  DeserializationError error = deserializeJson(doc, input);  // JSONをパースする

  if (error)  // パースに失敗すると呼ばれる
  {
    Serial.print(F("deserializeJson() failed: "));  // F()マクロは、指定した文字列分がSRAMからFlashメモリに移動する。
    Serial.println(error.f_str());
    Weather weather = {"", 0, 0};
    return weather;
  }

  JsonObject location = doc["location"];
  const char *location_region = location["region"];  // "Saitama"

  JsonObject current = doc["current"];
  float current_temp = current["temp_c"];  // 23.3℃
  int current_humidity = current["humidity"];  // 88％

  Weather weather = {location_region, current_temp, current_humidity};

  return weather;
}
//}

一分ごとにWeather APIにアクセスし情報を取得しています。
取得した情報をパースした後に@<list>{we_se}のように表示しています。

//list[we_se][Weather APIとの通信をシリアルモニタに表示]{
Waiting for Wi-Fi connection....
Connected to Wi-Fi
status code : 200
{"location":{"name":"Saitama","region":"Saitama","country":"Japan","lat":35.91,"lon":139.66,"tz_id":"Asia/Tokyo","localtime_epoch":1628673297,"localtime":"2021-08-11 18:14"},"current":{"last_updated_epoch":1628668800,"last_updated":"2021-08-11 17:00","temp_c":30.0,"temp_f":86.0,"is_day":1,"condition":{"text":"Partly cloudy","icon":"//cdn.weatherapi.com/weather/64x64/day/116.png","code":1003},"wind_mph":9.4,"wind_kph":15.1,"wind_degree":180,"wind_dir":"S","pressure_mb":1011.0,"pressure_in":29.85,"precip_mm":0.0,"precip_in":0.0,"humidity":59,"cloud":25,"feelslike_c":31.0,"feelslike_f":87.9,"vis_km":10.0,"vis_miles":6.0,"uv":8.0,"gust_mph":12.5,"gust_kph":20.2}}
parse.......
------weather--------
Saitama
30.00
59
2021-08-11 17:00
status code : 200
{"location":{"name":"Saitama","region":"Saitama","country":"Japan","lat":35.91,"lon":139.66,"tz_id":"Asia/Tokyo","localtime_epoch":1628673297,"localtime":"2021-08-11 18:14"},"current":{"last_updated_epoch":1628668800,"last_updated":"2021-08-11 17:00","temp_c":30.0,"temp_f":86.0,"is_day":1,"condition":{"text":"Partly cloudy","icon":"//cdn.weatherapi.com/weather/64x64/day/116.png","code":1003},"wind_mph":9.4,"wind_kph":15.1,"wind_degree":180,"wind_dir":"S","pressure_mb":1011.0,"pressure_in":29.85,"precip_mm":0.0,"precip_in":0.0,"humidity":59,"cloud":25,"feelslike_c":31.0,"feelslike_f":87.9,"vis_km":10.0,"vis_miles":6.0,"uv":8.0,"gust_mph":12.5,"gust_kph":20.2}}
parse.......
------weather--------
Saitama
30.00
59
2021-08-11 17:00
status code : 200
{"location":{"name":"Saitama","region":"Saitama","country":"Japan","lat":35.91,"lon":139.66,"tz_id":"Asia/Tokyo","localtime_epoch":1628673514,"localtime":"2021-08-11 18:18"},"current":{"last_updated_epoch":1628673300,"last_updated":"2021-08-11 18:15","temp_c":30.0,"temp_f":86.0,"is_day":1,"condition":{"text":"Partly cloudy","icon":"//cdn.weatherapi.com/weather/64x64/day/116.png","code":1003},"wind_mph":9.4,"wind_kph":15.1,"wind_degree":180,"wind_dir":"S","pressure_mb":1011.0,"pressure_in":29.85,"precip_mm":0.0,"precip_in":0.0,"humidity":59,"cloud":25,"feelslike_c":31.0,"feelslike_f":87.9,"vis_km":10.0,"vis_miles":6.0,"uv":8.0,"gust_mph":12.5,"gust_kph":20.2}}
parse.......
------weather--------
Saitama
30.00
59
2021-08-11 18:15

//}

== ディスプレイを使う
ここで、取得した情報を手軽に確認するためにディスプレイを使ってみます。
今回使うディスプレイはESP32との通信にI2Cという通信方式を利用しているので、ますそちらを紹介します。

=== I2Cとは

4本の線を接続するだけでセンサーや表示デバイスを手軽に利用できる
I2C（Inter Integrated Circuit）
IC間で通信することを目的に、フィリップ社が開発したシリアル通信方式
データのやり取りをするSDA（シリアルデータ）と、
IC間でタイミングを合わせるのに利用するSCL（シリアルクロック）
2本の線をつなげることで、互いにデータのやり取りえをするようになっている
GNDと電源にもつなげるので4本必要
I2Cは各種デバイスを制御するマスターと、マスターからの命令によって制御されるスレーブに分かれる
マスターはマイコンに当たる
デバイスを制御する場合に、対象デバイスを指定する必要がある
各I2CデバイスにはI2Cアドレスが割り当てられている
アドレスは16進数表記で0x03から0x77までの117個のアドレスが利用できる
大体は製品出荷時にアドレスが割り当てられている


==== ライブラリのインストール
ディスプレイをESP32上で使うためにライブラリをArduino IDEにインストールします。

@<img>{15-1}のように（スケッチ＞ライブラリのインクルード＞ライブラリを管理）を選択してください。

選択するとライブラリマネージャーが開かれるので、検索窓に「ssd1306 esp32」を入力してください（@<img>{9}）。
その後、「ESP8266 ans ESP32 OLED driver for SSD1306 displays」をインストールしてください
//image[10][SSD1306用ライブラリのインストール]{
//}

==== 回路図

//image[oled][ディスプレイ表示回路図]{
//}

//list[oled][ディスプレイ表示プログラム]{
#include <Wire.h>  // I2Cを利用するためのライブラリ
#include "SSD1306.h"

SSD1306 display(0x3c, 21, 22);  // ディスプレイのインスタンスを作成する。
                                // アドレス、 SDA、 SCLを指定

void setup()
{
  display.init();  // ディスプレイの初期化
  display.setFont(ArialMT_Plain_24);  // フォントサイズ24pxで表示
  display.drawString(0, 0, "Hello,World");  // 左上を原点とした座標で（0,0）に"Hello,World"表示
  display.display();  // 指定した文字列を表示させる
}

void loop(){}
//}

//image[oled1][SSD1306用ライブラリのインストール]{
//}
//image[P_20210807_121228][P_20210807_121228][scale=0.8]{
//}
//image[P_20210807_121205][P_20210807_121205][scale=0.8]{
//}

//emlist{
#include "DHT.h"

#include <Wire.h>  // I2Cを利用するためのライブラリ
#include "SSD1306.h" // ディスプレイのライブラリ

#define DHTPIN 4  // センサのデータを読み取るGPIOの番号を指定する
// DHTライブラリはDHT22/DHT11に対応しているので
// 使用するセンサを指定する　
#define DHTTYPE DHT11

SSD1306 display(0x3c, 21, 22);  // ディスプレイのインスタンスを作成する。
                                // I2Cアドレス、SDA、SCLを指定
DHT dht11(DHTPIN, DHTTYPE);  // DHT11のインスタンスを作成する

void setup()
{
  Serial.begin(115200);
  dht11.begin();  // DHT11を始動させる
  display.init(); // ディスプレイの初期化
}

void loop() {
  // DHT11のサンプリング間隔が2秒なので
  // センサが値を読むまで2秒待機
  delay(2000);
  display.clear(); // ディスプレイの文字をすべて消す

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
  Serial.printf("体感温度: %.3lf ℃\n", apparent_temperature);

  display.setFont(ArialMT_Plain_10);  // フォントサイズを10pxに設定
  display.drawString(0, 0, "temperature");  // （x座標, y座標, 表示したい文字列）
  display.drawString(0, 25, "humididity");
  display.setFont(ArialMT_Plain_24);  // フォントサイズを24pxに設定
  display.drawString(50, 10, String(temperature));  // String()で文字列に変換
  display.drawString(50, 30, String(humidity));
  display.setFont(ArialMT_Plain_10);  // フォントサイズを10pxに設定
  display.drawString(110, 22, "°C");
  display.drawString(110, 42, "%");

  display.display();  // 設定した文字列をディスプレイに表示させる
}
//}

//image[P_20210809_140907][P_20210809_140907][scale=0.8]{
//}

//list[weather_api][weather_api]{
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

void setup()
{

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for (uint8_t t = 4; t > 0; t--)
    {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("elecom-b2809f-g", "fapd4rpfac3u");
}

void loop()
{
    // wait for WiFi connection
    if ((wifiMulti.run() == WL_CONNECTED))
    {
 
      HTTPClient http;

      USE_SERIAL.print("[HTTP] begin...\n");
      // configure traged server and url
      //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
      http.begin("https://api.weatherapi.com/v1/current.json?key=ffe99ee9ec094d3681d74132211106&q=Saitama&aqi=no"); //HTTP

      USE_SERIAL.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK)
            {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                parse(payload);
            }
        }
        else
        {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(50000);
}

void parse(String input)
{
    USE_SERIAL.println("parse");
    USE_SERIAL.println("=====");
    StaticJsonDocument<1536> doc;

      DeserializationError error = deserializeJson(doc, input);
  
      if (error)
      {
          USE_SERIAL.print(F("deserializeJson() failed: "));
          USE_SERIAL.println(error.f_str());
          return;
      }
  
      JsonObject location = doc["location"];
      const char *location_name = location["name"];                // "Saitama"
      const char *location_region = location["region"];            // "Saitama"
      const char *location_country = location["country"];          // "Japan"
      float location_lat = location["lat"];                        // 35.91
      float location_lon = location["lon"];                        // 139.66
      const char *location_tz_id = location["tz_id"];              // "Asia/Tokyo"
      long location_localtime_epoch = location["localtime_epoch"]; // 1626533912
      const char *location_localtime = location["localtime"];      // "2021-07-17 23:58"
      USE_SERIAL.println(location_country);
  
      JsonObject current = doc["current"];
      long current_last_updated_epoch = current["last_updated_epoch"]; // 1626533100
      const char *current_last_updated = current["last_updated"];      // "2021-07-17 23:45"
      float current_temp_c = current["temp_c"];                        // 23.3
      float current_temp_f = current["temp_f"];                        // 73.9
      int current_is_day = current["is_day"];                          // 0
  
      JsonObject current_condition = current["condition"];
      const char *current_condition_text = current_condition["text"]; // "Clear"
      const char *current_condition_icon = current_condition["icon"];
      int current_condition_code = current_condition["code"]; // 1000
  
      float current_wind_mph = current["wind_mph"];       // 3.8
      float current_wind_kph = current["wind_kph"];       // 6.1
      int current_wind_degree = current["wind_degree"];   // 250
      const char *current_wind_dir = current["wind_dir"]; // "WSW"
      int current_pressure_mb = current["pressure_mb"];   // 1019
      float current_pressure_in = current["pressure_in"]; // 30.6
      int current_precip_mm = current["precip_mm"];       // 0
      int current_precip_in = current["precip_in"];       // 0
      int current_humidity = current["humidity"];         // 88
      int current_cloud = current["cloud"];               // 0
      float current_feelslike_c = current["feelslike_c"]; // 24.9
      float current_feelslike_f = current["feelslike_f"]; // 76.9
      int current_vis_km = current["vis_km"];             // 16
      int current_vis_miles = current["vis_miles"];       // 9
      int current_uv = current["uv"];                     // 1
      float current_gust_mph = current["gust_mph"];       // 13.9
      float current_gust_kph = current["gust_kph"];       // 22.3
      return;
  }
//}

Weather api は15分に一回更新される

==[column] サーバクライアント
サーバ？クライアント？とは何

== 応用問題: WebサーバからのLチカ