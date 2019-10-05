#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>

#include <ArduinoJson.h>



const char* ssid = "SFR-cdb8";
const char* password = "DZQAPMVIXN9I";

char WebPage[] PROGMEM = R"========(
<!DOCTYPE html>
<html>
  <style>
    input[type="text"]{
      width: 90%;
      height: 3vh;
    }
    input[type="button"]{
      width: 9%;
      height: 3.6vh;
    }
    .rxd{
      height: 90vh;
    }
    textarea{
      width: 99%
      height: 100%;
      resize: none;
    }
  </style>
  <script>
    var Socket;
    function start(){
      Socket=new WebSocket('ws://' + window.location.hostname + ':81/');
      Socket.onmessage=function(evt){
        document.getElementById("rxConsole").value +=evt.data;
      }
    }
    function enterpressed(){
      Socket.send(document.getElementById("txbuff").value); 
      document.getElementById("txbuff").value="";
    }
  </script>
  <body onload="javascript:start();">
    <div>
      <input class="txd" type="text" id="txbuff" onkeydown="if(event.keyCode==13) enterpressed();">
      <input class="txd" type="button" onclick="enterpressed();" value="Envoyer">
          
    </div>
    <br>
    <div class="rxd"> 
      <textarea id="rxConsole" readonly></textarea> 
    </div>
  </body>
</html>
  )========";

WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println(" ");

  pinMode(D0, OUTPUT);    // LED pin as output.
  digitalWrite(D0, 1);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", WebPage);
  });

  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  server.handleClient();
  if (Serial.available() > 0) {
    char c[] = {(char)Serial.read()};
    webSocket.broadcastTXT(c, sizeof(c));
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Deconnexion !\n");
      break;

    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connection : URL : %s\n",  payload);
      }

    case WStype_BIN:
      //Serial.printf("[WSc] get binary lenght: %u\n", length);
      //hexdump(payload, length);
      break;

  }

  if (type == WStype_TEXT) {
    String s = "";
    for (int i = 0; i < length; i++) {
      s += (char)payload[i];
    }
    Serial.println(s);
    Serial.println("");

    StaticJsonDocument<200> doc;

deserializeJson(doc, s);
/*    DeserializationError error = 
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
*/
//    if (s.indexOf("r") >= 0) {
      int r = doc[0];
      int g = doc[1];
      int b = doc[2];
      int x = doc[3];
      int y = doc[4];
      Serial.printf("[%d,%d,%d,%d,%d]", r, g, b, x, y);

      digitalWrite(D0, 0);
      delay(300);
      digitalWrite(D0, 1);

  //  }
    Serial.println();
  }
}
