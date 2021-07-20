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