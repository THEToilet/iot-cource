#include <Arduino.h>

/*
  Webサーバーテスト
*/

// WiFiライブラリをインクルード
#include <WiFi.h>

// アクセスポイント設定
const char *WIFI_SSID = "elecom-b2809f-g";
const char *WIFI_PASS = "fapd4rpfac3u";

// インスタンス生成
WiFiClass wifi;

// WebServerライブラリを使用
#include <WebServer.h>

// インスタンス作成 待ち受け80番ポート
WebServer server(80);

// basic認証用
const char *www_username = "admin";
const char *www_password = "abc";

void setup()
{
  // put your setup code here, to run once:

  // シリアル通信を開始
  Serial.begin(115200);

  // ちょっと待つ
  delay(3000);

  // 既に接続中なら一旦切る
  if (wifi.isConnected())
  {
    wifi.disconnect();
    delay(3000);
  }

  // wifiモードを設定 ステーションモード
  wifi.mode(WIFI_STA);
  wifi.setAutoConnect(false);

  // wifi通信開始
  wifi.begin(WIFI_SSID, WIFI_PASS);
  delay(6000); // 6秒待ち

  // 繋がるまでループ
  while (wifi.status() != WL_CONNECTED)
  {
    // 繋がらなかったら
    if (wifi.status() == WL_CONNECT_FAILED)
    {
      Serial.println("aborting wifi connection to SSID. plz check at config.");
    }
    Serial.println("connecting...");
    delay(6000);
  }

  Serial.println("success!");
  Serial.print("IP address: ");
  Serial.println(wifi.localIP());
  Serial.print("GW address: ");
  Serial.println(wifi.gatewayIP());
  Serial.print("DNS address: ");
  Serial.println(wifi.dnsIP());
  Serial.println("");

  // rootアクセスに応答する定義
  server.on("/", []() {
    // BASIC認証
    if (!server.authenticate(www_username, www_password))
    {
      return server.requestAuthentication();
    }
    // 認証OKの場合にはログインOKを表示
    server.send(200, "text/plain", "Login OK");
  });

  // サーバースタート
  server.begin();

  Serial.print("WebServer Started. http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Webサーバー待ち受け
  server.handleClient();

}
