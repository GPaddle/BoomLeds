#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include "config.h"
#include <WebTime.h>

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

String txt = "";
int place = 0, xText, yText;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                                               NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

const size_t capacity = JSON_ARRAY_SIZE(6);
DynamicJsonDocument doc(capacity);

WiFiClient client;
unsigned long timeReceived;
unsigned long timeOffset;
boolean timeDisplay = true;

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
  String txtReceived = "";
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_TEXT:

    if (timeDisplay)
    {

      timeDisplay = false;
      matrix.fillScreen(0);
    }
    Serial.printf("[%u] get Text: %s\n", num, payload);

    deserializeJson(doc, payload);
    desc = doc[0];

    if (desc != 4)
    {
      txt = "";
    }

    switch (desc)
    {

      //Display Code
    case 1:

      //          Serial.println("SHOW");
      matrix.show();
      delay(50);

      break;

      //Image Code
    case 2:
      x = doc[1];
      y = doc[2];
      r = doc[3];
      g = doc[4];
      b = doc[5];

      //Serial.printf("xy (%d,%d) rgb (%d,%d,%d)", x, y, r, g, b);
      //      Serial.println("IMAGE");
      matrix.drawPixel(x, y, matrix.Color(r, g, b));

      break;

      //Single pixel Code
    case 3:

      x = doc[1];
      y = doc[2];
      r = doc[3];
      g = doc[4];
      b = doc[5];
      //      Serial.println("PIXEL");

      //Serial.printf("xy (%d,%d) rgb (%d,%d,%d)", x, y, r, g, b);

      matrix.drawPixel(x, y, matrix.Color(r, g, b));
      matrix.show();
      //      delay(50);

      break;

      //Text Code
    case 4:
      //      Serial.println("TEXT");

      xText = doc[1];
      yText = doc[2];

      txtReceived = (const char *)doc[3];
      txtReceived = doc[3].as<const char *>();
      txtReceived = doc[3].as<String>();

      if (txtReceived.equals("") && !txt.equals(""))
      {
        matrix.fillScreen(0);
        matrix.show();
      }

      txt = txtReceived;

      break;

    case 5:

      r = doc[3];
      g = doc[4];
      b = doc[5];

      matrix.fillRect(0, 0, 32, 8, matrix.Color(r, g, b));
      matrix.show();
      delay(50);
      //      Serial.println("FILL");

      break;

    case 6:
      //APP Case
      txtReceived = (const char *)doc[3];
      txtReceived = doc[3].as<const char *>();
      txtReceived = doc[3].as<String>();

      if (txtReceived.equals("clock"))
      {
        timeDisplay = true;
      }

    default:
      Serial.println("Unknow code");
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

void textLoop()
{

  //If coordinates, set on these

  //If no coordinates, set on the bottom left corner

  if (!txt.equals(""))
  {
    if (xText == -1)
    {
      xText = 0;
      yText = 7;
    }

    if (xText == 0 && txt.length() > (matrixWidth / 4))
    {
      xText = 3;
    }

    if (txt.length() > (matrixWidth / 4))
    {
      int l = txt.length();

      if (place < (l - 8) * 4 + 3)
      {

        matrix.fillScreen(0);

        matrix.setCursor(xText - place, yText);

        matrix.print(txt);
        matrix.show();
        delay(250);
        place++;
      }
      else
      {
        delay(1000);
        place = 3;
      }
    }
    else
    {
      matrix.fillScreen(0);
      matrix.setCursor(xText, yText);
      matrix.print(txt);
      matrix.show();
      delay(50);
    }
  } /*
  else
  {
    matrix.fillScreen(0);
    matrix.show();
  }*/
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
  serve(server, "/style.css", "/style.css.gz", "text/css");
  //serve(server, "/all.css", "/node_modules/@fortawesome/fontawesome-free/css/all.css", "text/css");
  serve(server, "/app.js", "/app.js.gz", "application/javascript");
  serve(server, "/favicon.ico", "/favicon.ico.gz", "image/x-icon");
  server.begin();
  Serial.println("HTTP Server started");

  webSocket.begin();
  webSocket.onEvent(handleWebSocket);
  Serial.println("Websocket Server started");

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(matrix.Color(200, 200, 200));
  matrix.setFont(&TomThumb);

  //  splashScreen();

  timeReceived = webUnixTime(client) + 1 * 60 * 60;
  timeOffset = millis();

  Serial.println("Ready");
}

void splashScreen()
{
  int len = 20;

  for (int i = (32 - len) / 2; i < len + (32 - len) / 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      matrix.drawPixel(i, j, matrix.Color(255, 255, 255));
      matrix.show();
      delay(50);
    }
  }

  for (size_t i = 0; i < 2; i++)
  {

    while (matrix.getBrightness() > 1)
    {
      matrix.setBrightness(matrix.getBrightness() - 1);
      matrix.show();
      delay(50);
    }
    while (matrix.getBrightness() < 5)
    {
      matrix.setBrightness(matrix.getBrightness() + 1);
      matrix.show();
      delay(50);
    }
  }

  for (int i = (32 - len) / 2; i < len + (32 - len) / 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      matrix.drawPixel(i, j, matrix.Color(0, 0, 0));
      matrix.show();
      delay(50);
    }
  }
}

void timeLoop()
{

  unsigned long currentTime = (millis() - timeOffset) / 1000 + timeReceived;
  int sec = currentTime % 60;
  currentTime -= sec;
  currentTime /= 60;
  int min = currentTime % 60;
  currentTime -= min;
  currentTime /= 60;
  int hour = currentTime % 24;
  currentTime -= hour;
  currentTime /= 24;
  int rest = currentTime; //All the rest of the date since 1970 (nb of days since this date)

  matrix.fillScreen(0);
  matrix.setCursor(1, 7);
  String goodLength = (hour < 10) ? "0" : "";
  matrix.print(goodLength);
  matrix.print(hour);

  matrix.setCursor(9, 7);
  matrix.print(":");
  goodLength = (min < 10) ? "0" : "";
  matrix.print(goodLength);
  matrix.print(min);

  matrix.setCursor(19, 7);
  matrix.print(":");
  goodLength = (sec < 10) ? "0" : "";
  matrix.print(goodLength);
  matrix.print(sec);
  matrix.show();
  delay(200);
}

void loop()
{
  webSocket.loop();
  server.handleClient();
  textLoop();
  if (timeDisplay)
  {
    timeLoop();
  }
}