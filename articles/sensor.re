= 取得データをWebに公開しよう！

//image[6][今回の目標画面]{
//}

== センサーを使おう

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
==== LCD

//image[oled][oled]{
//}
//image[10][SSD1306用ライブラリのインストール]{
//}
//list[oled][oled]{
#include <Wire.h>
#include <string>
#include "SSD1306.h" //ディスプレイ用ライブラリを読み込み
using namespace std;

SSD1306 display(0x3c, 21, 22); //SSD1306インスタンスの作成（I2Cアドレス,SDA,SCL）

int i = 0;
void setup()
{

  display.init();                          //ディスプレイを初期化
  display.setFont(ArialMT_Plain_16);       //フォントを設定
  display.drawString(0, 0, "Hello World"); //(0,0)の位置にHello Worldを表示
  display.display();                       //指定された情報を描画
}

void loop()
{
  i++;
  display.setPixel(i, i + 10);
  if (i == 100)
  {
    i = 0;
  }
  display.displ
//}


//list[dht11][dht11]{
// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
  // REQUIRES the following Arduino libraries:
  // - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
  // - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
  
  #include "DHT.h"
  
  #define DHTPIN 4     // Digital pin connected to the DHT sensor
  // Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
  // Pin 15 can work but DHT must be disconnected during program upload.
  
  // Uncomment whatever type you're using!
  #define DHTTYPE DHT11   // DHT 11
  //#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
  //#define DHTTYPE DHT21   // DHT 21 (AM2301)
  
  // Connect pin 1 (on the left) of the sensor to +5V
  // NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
  // to 3.3V instead of 5V!
  // Connect pin 2 of the sensor to whatever your DHTPIN is
  // Connect pin 4 (on the right) of the sensor to GROUND
  // Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
  
  // Initialize DHT sensor.
  // Note that older versions of this library took an optional third parameter to
  // tweak the timings for faster processors.  This parameter is no longer needed
  // as the current DHT reading algorithm adjusts itself to work on faster procs.
  DHT dht(DHTPIN, DHTTYPE);
  
  void setup() {
    Serial.begin(9600);
    Serial.println(F("DHTxx test!"));
  
    dht.begin();
  }
  
  void loop() {
    // Wait a few seconds between measurements.
    delay(2000);
  
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
  
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.print(F("°F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.print(hif);
    Serial.println(F("°F"));
  }
//}

//list[tmp][tmp]{
 	Humidity: 56.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.47°C 76.04°F
  Humidity: 56.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.47°C 76.04°F
  Humidity: 56.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.47°C 76.04°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°F
  Humidity: 57.00%  Temperature: 24.50°C 76.10°F  Heat index: 24.49°C 76.09°	 
//}

== Webに公開しよう

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

unsigned long delayTime;
float temp;
float pressure;
float humid;

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

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  ambient.set(1, h);
  ambient.set(2, t);
  ambient.set(3, f);

  ambient.send(); //  Ambientにデーターを送信

  delay(PERIOD * 1000);
}
//}
