#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// ESP32アクセスポイントのSSIDとパスワード（名称自由）
const char *ssid = "esp32-ap";
const char *password = "pass";

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
