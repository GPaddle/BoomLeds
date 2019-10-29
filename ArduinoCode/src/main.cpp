#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include "config.h"



#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
#include <Fonts/TomThumb.h>

#define PIN D5
#define LED_BRIGHTNESS 32

#define serve(server, uri, filePath, contentType)             \
  {                                                           \
    server.on(uri, [&]() {                                    \
      File file = SPIFFS.open(filePath, "r");                 \
      int sentBytes = server.streamFile(file, contentType);   \
      Serial.println(String("GET ") + uri + " " + sentBytes); \
      file.close();                                           \
    });                                                       \
  }

const uint8_t matrixWidth = 32;
const uint8_t matrixHeight = 8;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                                               NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

const size_t capacity = JSON_ARRAY_SIZE(5);
DynamicJsonDocument doc(capacity);

void waitForWifi()
{
  WiFi.hostname(HOSTNAME);
  WiFi.mode(WIFI_STA);
  do
  {
    Serial.println(String("Connecting to ") + WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(4000);
  } while (WiFi.status() != WL_CONNECTED);
}

void handleWebSocket(uint8_t num, WStype_t type, uint8_t *payload, size_t lenght)
{
  int16_t desc, x, y, r, g, b;
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_TEXT:
    Serial.printf("[%u] get Text: %s\n", num, payload);

    deserializeJson(doc, payload);
    desc = doc[0];

    switch (desc)
    {

      //Display Code
    case 1:

      matrix.show();

      break;

      //Image Code
    case 2:
      x = doc[1];
      y = doc[2];
      r = doc[3];
      g = doc[4];
      b = doc[5];

      Serial.printf("xy (%d,%d) rgb (%d,%d,%d)", x, y, r, g, b);

      matrix.drawPixel(x, y, matrix.Color(r, g, b));

      break;

      //Single pixel Code
    case 3:

      x = doc[1];
      y = doc[2];
      r = doc[3];
      g = doc[4];
      b = doc[5];

      Serial.printf("xy (%d,%d) rgb (%d,%d,%d)", x, y, r, g, b);

      matrix.drawPixel(x, y, matrix.Color(r, g, b));
      matrix.show();

      break;

      //Text Code
    case 4:
      std::string txt = doc[1];

      //TODO function to write text
      
      break;

    default:
      Serial.println("Code non reconnu");
      break;
    }

    Serial.printf("%s\n", payload);

    break;
  case WStype_CONNECTED:
    IPAddress ip = webSocket.remoteIP(num);
    Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    break;
  }
}

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println("Starting...");

  SPIFFS.begin();
  Serial.println("Spiffs started");

  waitForWifi();
  Serial.println("WiFi started");
  Serial.println(WiFi.localIP());

  serve(server, "/", "/index.html.gz", "text/html");
  serve(server, "/index.html", "/index.html.gz", "text/html");
  serve(server, "/style.css", "/style.css.gz", "test/css");
  serve(server, "/app.js", "/app.js.gz", "application/javascript");
  serve(server, "/p5.min.js", "/p5.min.js.gz", "application/javascript");
  serve(server, "/addons/p5.dom.min.js", "/addons/p5.dom.min.js.gz", "application/javascript");
  serve(server, "/addons/p5.sound.min.js", "/addons/p5.sound.min.js.gz", "application/javascript");
  server.begin();
  Serial.println("HTTP Server started");

  webSocket.begin();
  webSocket.onEvent(handleWebSocket);
  Serial.println("Websocket Server started");
  /*
  initLeds();
  LEDS.addLeds<WS2812, DataPin, GRB>(leds, matrixWidth * matrixHeight);
  LEDS.setBrightness(LED_BRIGHTNESS);
  */

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(matrix.Color(200, 200, 200));
  matrix.setFont(&TomThumb);

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      matrix.drawPixel(i, j, matrix.Color(255, 255, 255));
      matrix.show();
      delay(50);
    }
  }

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      matrix.drawPixel(i, j, matrix.Color(0, 0, 0));
      matrix.show();
      delay(50);
    }
  }

  Serial.println("Ready");
}

void loop()
{
  webSocket.loop();
  server.handleClient();
  /*matrix.drawLine(1,2,25,6,White);

    matrix.drawRect(31-5,2,5,5,White);

    matrix.show();
    delay(2000);
  */
}