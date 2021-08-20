#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// WiFi接続用変数
const char *ssid = "ssid";
const char *password = "password";


WebServer server(80);

void handleNotFound() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleRoot() {
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n\
                   <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", message);
}

void handleLedBlink() {
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
                   <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", message);
}
void handleDHT11() {
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
                   <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", message);
}

void handleWeatherAPI() {
  String message = "\
  <!DOCTYPE html>\n\
<html>\n\
<head>\n\
    <meta charset=\"utf-8\" />\n\
    <title>Toilet Paper</title>\n\
    <link rel=\"stylesheet\" href=\"stylesheet.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick.css\" />\n\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"slick/slick-theme.css\" />\n
                   <link rel=\"shortcut icon\" href=\"img/toilet_paper2_sankaku.png\">\n\
</head>\n\
<body>\n\
    <!-----------------------header------------------------------->\n\
    <header>\n\
        <div class=\"container\">\n\
            <div class=\"header-title\">\n\
                <div id=\"top-btn\" class=\"header-logo\">Toilet Paper</div>\n\
            </div>\n\
            <div class=\"header-menu\">\n\
                <ul class=\"header-menu-right\">\n\
                    <li><a href=\"/blink\">About Me</a></li>\n\
                    <li><a href=\"/sensor\">Skill Set</a></li>\n\
                    <li><a href=\"/weather\">Works</a></li>\n\
                </ul>\n\
            </div>\n\
        </div>\n\
    </header>\n\
    <!----------------------------header-end--------------------------->\n\
    <div class=\"top-wrapper\">\n\
        <h1>Portfolio</h1>\n\
        <img src=\"img/toilet_kirei.png\" />\n\
    </div>\n\
</body>\n\
</html>\n\
\n";
  server.send(200, "text/plain", "weaher");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  delay(100);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/blink", handleLedBlink);
  server.on("/sensor", handleDHT11);
  server.on("/weather", handleWeatherAPI);

  /*
    server.on("/inline", []() {
      server.send(200, "text/plain", "this works as well");
    });
  */

  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(5);
}
