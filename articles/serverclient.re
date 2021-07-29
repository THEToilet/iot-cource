= WebAPIを使おう

=== WebAPIとは？

== Weather APIを使う

//image[1][WeatherAPIのトップページ]{
//}
//image[2][登録画面]{
//}
//image[3][ログイン画面]{
//}
//image[4][マイページ]{
//}
//image[5][APIの試行ページ]{
//}

Weather API
@<href>{https://www.weatherapi.com/}

Call
@<href>{https://api.weatherapi.com/v1/current.json?key=********&q=Saitama&aqi=no}

ResponeseCode
200

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
これらの形式が、WeatherAPIから帰ってくるため、ESP32側で使えるようにしなければなりません
そこで、公開されているライブラリであるarduinoJSONを利用します。

==== ライブラリのインストール

 [** arduinoJSON]
 JSONドキュメントを作る時にキャパシティを計算する必要がある
 ArduinoJson Assistant
 https://arduinojson.org/v6/assistant/

//image[6][ArudinoAssistantのトップページ]{
//}
//image[7][JSONの大きさ設定]{
//}
//image[8][JSONのサイズ確認画面]{
//}
//image[9][ArduinoJson用ライブラリのインストール]{
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

== ディスプレイを使う

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

//image[oled][oled]{
//}
//image[10][SSD1306用ライブラリのインストール]{
//}
//list[oled][oled]{
#include <Wire.h>
#include "SSD1306.h"
using namespace std;

SSD1306 display(0x3c, 21, 22);

void setup()
{
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Hello World");
  display.display();
}

void loop(){}
//}

//image[oled1][SSD1306用ライブラリのインストール]{
//}

//list[weather_api][weather_api]{
#include <Arduino.h>
  
//#include <Arduino_JSON.h>
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

==[column] コラム: サーバクライアント
サーバ？クライアント？とは何


== 応用問題: WebサーバからのLチカ