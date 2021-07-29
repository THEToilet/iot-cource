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