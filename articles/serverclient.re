= WebAPIを使おう
この章ではWebAPIを利用して天気情報をディスプレイに表示することを目的としてます。

=== WebAPIとは？
APIとはApplication Programming Interfaceの略でコンテキストによって様々な意味合いがありますが、
主にアプリケーションが何らかの情報を得たり、渡したりする際に用いる窓口を指す際に用いられています。
そのためWebAPIはWebを通してやり取りを行うAPIを意味しています。
ゲームなどで「Twitterに共有」というリンクが設置されていることがありますが、これはゲームのアプリケーションがTwitterAPIを通してゲームの内容をTwitterに共有できる機能です。

== Weather APIを使う
先ほどWebAPIの説明を行いますが、なかでも今回は天気を知れるAPIを使います。
天気を知れるAPIは複数ありますが、ここでは「Weather API」というものを利用します。
以下のリンクにアクセスしてWeather APIのトップページに移動してください（@<img>{1}）。

//embed[latex]{
\begin{center}
Weather API: https://www.weatherapi.com/
\end{center}
//}

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

選択した後、@<img>{5}のような画面に遷移します。

//image[5][APIの試行ページ]{
//}

この画面では以下の5つのパラメータを設定することができます。

 * Your API Key
 ** 先ほどメモしたAPI key
 * Protocol
 ** HTTP
 * Format
 ** JSON
 * Parameter q
 ** London
 * Parameter api
 ** no

ProtocolはAPIとの通信に用いるプロトコルを指定して
Formatはやり取りをする情報の形式を表しています。
HTTPとJSONの詳細については後に説明します。
パラメータを選択したのち@<strong>{Show Response}を選択すると
以下のレスポンスが帰ってきます。
@<list>{Call}はAPIを呼び出すときに用いるURLです。
keyの部分にはWeather APIで得られたAPI Keyを入れてください。
@<list>{ResponseCode}と@<list>{ResponesHeader}と@<list>{ResponseBody}は
APIとの通信でHTTPというプロトコルを使用した際に帰ってくるもの（レスポンス）です。
これについては後に説明します。
また、@<list>{ResponesHeader}と@<list>{ResponseBody}はAPIで呼び出した
指定した地域の天気情報です。これは先ほど指定したJSONという形式で送られています。
これもまた後に説明します。

=== レスポンス

//list[Call][Call]{
http://api.weatherapi.com/v1/current.json?key=********&q=Saitama&aqi=no
//}

//list[ResponseCode][ResponeseCode]{
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

=== JSON（JavaScript Object Node）
JSONはデータを記述する際に用いられる言語の一つで、
JavaScriptでオブジェクトを記述する際の記法をもとにしています。
//list[json][JSONデータの例]{
{
  "THEToilet" : unko,
  "DNE3" : "芝浦"
}
//}
JSONで使えるデータ型は文字列、数値、配列、ブーリアン等が挙げられます。

=== HTTP（Hypertext Transfer Protocol）
HTTPとはTCP/IPと呼ばれるをインターネットなどのネットワーク上で使われている通信プロトコル上で
Web情報をやり取りする際に用いられるプロトコルです。
例えば電子計算機研究会（通称: DEN3）のホームページにアクセスした際も
@<img>{2021-01-25-173558}のようにHTTP通信が行われています。
//image[2021-01-25-173558][DEN3のホームページにアクセスした際の通信]{
//}
HTTPはリクエスト/レスポンス型の通信プロトコルであり、
クライアント側は通信相手にリクエスト（要求）を出すと、
通信相手からのレスポンス（応答）が返ってくるまで待機します。
ちなみにHTTPSはHTTPの通信を暗号化しているプロトコルです。
またHTTPの通信のやり取りにはHTTPメッセージというものが使われており
Weather APIとのやり取りでもでてきた

 * ステータスコード
 * ヘッダ
 * ボディ

の3つと

 * HTTPメソッド

が主に重要になるので、これらの紹介を行います。

==== ステータスコード
ステータスコードとはHTTP通信にてリクエストを送った後、
そのリクエストが成功したかどうかを表している数字です。
主に3桁の数字で表され、それぞれの数字の意味としては

 * 2xx 200番台
 ** リクエストが成功成功したことを表す。
 ** EX: 200 OK（リクエスト成功）
 * 3xx 300番台
 ** リダイレクト（別のアクセスへの転送）を行うときに返ってくる。
 ** EX: 301 Moved Permanently（アクセス先のURLが変更したため転送する）
 * 4xx 400番台
 ** クライアント側のエラーを表す。
 ** クライアントが送った処理が間違っている時に返ってくる。
 ** EX: 404 not found（指定したコンテンツが見つかりませんでした）
 * 5xx 500番台
 ** サーバ側のエラーを表す。
 ** サーバ内でエラーが発生している。
 ** EX: 500 Internal Server Error（サーバ内部エラー）

を表しています。

==== ヘッダ
ヘッダにはHTTPメッセージについてのメタデータ(データについての付加情報)
が書かれています。例としてはボディに記述されているコンテンツの種類（htmlやJSONなど）や
コンテンツのサイズ、後述するHTTPメソッド等です。

==== ボディ
やり取りをしたいコンテンツが入っています、
主にJSON化したデータやHTMLなどです。

==== HTTPメソッド
HTTP通信にはメソッドと呼ばれているHTTPリクエストの種類を表すものがあります。
ここではCURD(Create, Update, Read, Delete)と呼ばれる性質を満たす代表的なメソッド

 * GET
 * POST
 * PUT
 * DELETE

の四つを紹介したいと思います。

===== GET
コンテンツの取得の際に使われます。
@<img>{2021-02-01-004533}はブログの記事を取得した例で、
リクエストメソッドとしてGETが使われています。

//image[2021-02-01-004533][HTTP通信でGET]{
//}

===== POST

コンテンツの追加、作成時に使われます。

DEN3ブログにコメントを投稿（@<img>{2021-02-01-004715}）した際は、
リクエストメソッドとしてPOSTが使われ（@<img>{2021-02-01-004705}）、
HTTPリクエストのボディにはコメントの内容が書かれており（@<img>{2021-02-01-004631}）、コメントの内容とともに
サーバにリクエストを送信しています。
//image[2021-02-01-004715][ブログに送信したコメント]{
//}
//image[2021-02-01-004705][HTTP通信でPOST]{
//}
//image[2021-02-01-004631][コメントを送信した際のボディ部]{
//}

===== PUT
コンテンツの作成、更新時に使われ、
ブログで例えるとブログを更新したいときに使われています。

===== DELETE
コンテンツの削除時に使われ、ブログで例えると、
ブログの投稿などを削除した時に使われます。
#@#山本 陽平. Webを支える技術 ―― HTTP，URI，HTML，そしてREST WEB+DB PRESS plus  株式会社技術評論社.

=== ESP32でJSONを利用する
JSON形式のデータがWeatherAPIから返ってくるため、これをESP32側で解釈してデータとして
扱えるようにする必要があります。
そこで、公開されているライブラリであるArduinoJSONを利用します。
ArduinoJSONを使用する場合にはJSONデータをESP32で扱えるデータに変換する際に
キャパシティの計算をする必要があります。そのため以下のリンクにアクセスして
設定を行ってください。ただし、今回使うWeather API用のキャパシティの計算結果は
用意してあるので参考として紹介します。

//embed[latex]{
\begin{center}
ArduinoJson Assistant: https://arduinojson.org/v6/assistant/
\end{center}
//}

リンクにアクセスすると@<img>{6}に遷移します。
//image[6][ArudinoAssistantのトップページ]{
//}
ここで設定には

 * Processor
 ** ESP32
 * Mode
 ** Deserialize（データ構造を復元する処理）
 * Input Type
 ** String

を設定してください。
その後、@<strong>{Next: JSON}を選択してください。

遷移後は@<img>{7}のような画面になるのでInputに
使用するJSONデータを入力してください。
次に@<strong>{Next: Size}を選択してください。
//image[7][JSONの大きさ設定]{
//}
遷移後の@<img>{8}でデシリアライズに必要なサイズが分かります。
//image[8][JSONのサイズ確認画面]{
//}

@<list>{world}がWeather APIをESP32で使用するためのコードです。
inputにはWeather APIから送られてきたデータを代入してください。

//list[world][デシリアライズコード]{
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

//image[15-1][ライブラリの管理の選択]{ 
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
 * Location（地名）
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
const String api_key = "ffe91ee9ec094d333681d74332211106";
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
  String target_url = "https://api.weatherapi.com/v1/current.json?key=";
  target_url += (api_key + "&q=" + location + "&aqi=no");
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
    Serial.print(F("deserializeJson() failed: "));
    // F()マクロは、指定した文字列分がSRAMからFlashメモリに移動する。
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
{"location":{"name":"Saitama","region":"Saitama","country": ・・・・省略
parse.......
------weather--------
Saitama
30.00
59
2021-08-11 17:00
status code : 200
{"location":{"name":"Saitama","region":"Saitama","country": ・・・・省略
parse.......
------weather--------
Saitama
30.00
59
2021-08-11 17:00
status code : 200
{"location":{"name":"Saitama","region":"Saitama","country": ・・・・省略
parse.......
------weather--------
Saitama
30.00
59
2021-08-11 18:15
//}

== ディスプレイを使う
ここで、取得した情報を手軽に確認するためにディスプレイを使ってみます。
今回使うディスプレイ（@<img>{P_20210811_184332}）はESP32との通信にI2Cという通信方式を利用しているので、ますそちらを紹介します。

//image[P_20210811_184332][ディスプレイ]{
//}

=== I2C（Inter-Integrated Circuit）とは
I2Cはフィリップ社が開発したシリアル通信方式です。
I2Cに必要な通信戦は4本で使用目的は電源（Vdd）、GND、SDA（シリアルデータ）、SCL（シリアルクロック）です。
SDAはデータの書き込みと読み込みを行い、SCLは通信先との同期をとる際に使用されます。
I2Cでは通信するデバイスはマスタとスレーブに分類され、マスタがスレーブとの通信を管理します。
ここではESP32がマスタに相当し、ディスプレイがスレーブに相当します。
また、マスタがスレーブを認識するためにスレーブにはそれぞれ認識アドレスが割り当てられます。
#@#プルアップ抵抗

=== ライブラリのインストール
ディスプレイをESP32上で使うためにライブラリをArduino IDEにインストールします。

@<img>{15-1}のように（スケッチ＞ライブラリのインクルード＞ライブラリを管理）を選択してください。

選択するとライブラリマネージャーが開かれるので、検索窓に「ssd1306 esp32」を入力してください（@<img>{9}）。
その後、「ESP8266 ans ESP32 OLED driver for SSD1306 displays」をインストールしてください

//image[10][SSD1306用ライブラリのインストール]{
//}

=== ディスプレイの表示
ここで実際にディスプレイを表示させてみましょう。
今回はHello,Worldを表示させてみたいと思います。
回路図（@<img>{oled}）を参考に電子回路を組み、プログラム（@<list>{oled}）を書き込んでください。

==== 回路図
 
 * 必要材料
 ** ESP32 × 1
 ** ブレッドボード × 2
 ** 10kΩ × 2
 ** SSD1306 display × 1
 ** ジャンプワイヤ

//image[oled][ディスプレイ表示回路図][scale=1.3]{
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
  display.drawString(0, 0, "Hello,World");  // 左上を原点とした座標で
                                            // （0,0）に"Hello,World"表示
  display.display();  // 指定した文字列を表示させる
}

void loop(){}
//}

// TODO: 画像差し替え＆キャプション差し替え

//image[P_20210807_121205][P_20210807_121205]{
//}
//image[P_20210807_121228][Hello! ディスプレイ]{
//}

== Weather APIから得たデータを表示

//list[weaher][Iのデータをディスプレイに表示するプログラム]{
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include <Wire.h>  // I2Cを利用するためのライブラリ
#include "SSD1306.h" // ディスプレイのライブラリ

SSD1306 display(0x3c, 21, 22);  // ディスプレイのインスタンスを作成する。
// アドレス、SDA、SCLを指定

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
  const char *last_updated;
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

  display.init(); // ディスプレイの初期化
}

void loop()
{
  display.clear(); // ディスプレイの文字をすべて消す

  HTTPClient http;
  String target_url = "https://api.weatherapi.com/v1/current.json?key=";
  target_url += (api_key + "&q=" + location + "&aqi=no");
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
      Serial.println(weather.last_updated);
      // char [100]
      display.setFont(ArialMT_Plain_10);  // フォントサイズを10pxに設定
      display.drawString(0, 0, "region:");  // （x座標, y座標, 表示したい文字列）
      display.drawString(0, 12, "temperature:");
      display.drawString(0, 24, "humididity:");
      display.drawString(0, 36, "last_updated:");
      display.drawString(65, 0, weather.region);
      display.drawString(65, 12, String(weather.temperature) + "°C");
      display.drawString(65, 24, String(weather.humidity) + "%");
      display.drawString(30, 48, weather.last_updated);

      display.display();  // 設定した文字列をディスプレイに表示させる
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
    Serial.print(F("deserializeJson() failed: "));
    // F()マクロは、指定した文字列分がSRAMからFlashメモリに移動する。
    Serial.println(error.f_str());
    Weather weather = {"", 0, 0};
    return weather;
  }

  JsonObject location = doc["location"];
  const char *location_region = location["region"];  // "Saitama"

  JsonObject current = doc["current"];
  const char *current_last_updated = current["last_updated"]; //  "2021-07-17 23:45"
  float current_temp = current["temp_c"];  // 23.3℃
  int current_humidity = current["humidity"];  // 88％

  Weather weather =
  {location_region, current_temp, current_humidity, current_last_updated};

  return weather;
}
//}

//image[P_20210811_231214][Weather APIのデータをディスプレイに表示]{
//}

Weather APIは15分に一回更新されますが
ここでは一分間に一回Weather APIへのリクエストを送っています。

== 応用問題1: センサのデータを表示する

//image[displaydht11][温湿度データをディスプレイに表示する回路図][scale=1.8]{
//}

//list[dht_ssd][DHT11のデータをディスプレイに表示すえうプログラム]{
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

//image[P_20210809_140907][温湿度をディスプレイに表示]{
//}

== 応用問題2: 時計を表示してみる

応用問題として時計を作成します。
正確な時刻情報を取得するためは、NTPサーバにアクセスする必要があります。
そのためまずはNTPサーバについての紹介を行います。

=== NTP（Network Time Protocol）
NTPは時刻の同期に用いられるプロトコルです。
クライアントは主に原子時計やGPSを用いて時刻を管理している、
NTPサーバに問い合わせを送ることで時刻を取得することができます。

===
//list[clock][時刻表示プログラム]{
#include <WiFi.h>

#include <Wire.h>  // I2Cを利用するためのライブラリ
#include "SSD1306.h" // ディスプレイのライブラリ

SSD1306 display(0x3c, 21, 22);  // ディスプレイのインスタンスを作成する。
// アドレス、SDA、SCLを指定

// WiFi接続用変数
const char *ssid = "elecom-b2809f-g";
const char *password = "fapd4rpfac3u";

int JST = 3600 * 9;  // 標準時間

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);  // Wi-Fi接続開始

  while (WiFi.status() != WL_CONNECTED) // Wi-Fiアクセスポイントへ接続するまで待機
  {
    Serial.println("Waiting for Wi-Fi connection....");
    delay(500);
  }
  Serial.println("Connected to Wi-Fi");

  configTime(JST, 0, "ntp.nict.jp", "0.jp.pool.ntp.org", "time1.google.com");
  // 標準時間, サマータイム, ntpサーバ
  display.init(); // ディスプレイの初期化
}

struct tm timeInfo;//時刻を格納するオブジェクト

void loop() {
  delay(1000);

  display.clear(); // ディスプレイの文字をすべて消す

  getLocalTime(&timeInfo);  // tmオブジェクトのtimeInfoに現在時刻を入れ込む

  char date[12], now_time[7];
  sprintf(date, "%04d/%02d/%02d",
  timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday);
  sprintf(now_time, "%02d:%02d", timeInfo.tm_hour, timeInfo.tm_min);
  Serial.println(date);

  display.setFont(ArialMT_Plain_16);  // フォントサイズを10pxに設定
  display.drawString(2, 2, String(date));
  display.setFont(ArialMT_Plain_24);  // フォントサイズを24pxに設定
  display.drawString(35, 25, String(now_time));

  display.display();  // 設定した文字列をディスプレイに表示させる
}
//}

//image[P_20210811_224508][時刻を表示したディスプレイ][scale=0.8]{
//}