#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>


#include <ArduinoJson.h>



const char* ssid = "SFR-96a8";
const char* password = "DLLW13K2CIPR";

char WebPage[] PROGMEM = R"========(
<!DOCTYPE html>
<html>
  <style>
    html,
body {
    height: 100%;
}

body {
    margin-top: 10px;
    margin-left: 10px;
    margin-right: 10px;
    /* This centers our sketch horizontally. */
    justify-content: center;
    /* This centers our sketch vertically. */
    align-items: center;
    background-image: linear-gradient(to bottom, #051937, #36214f, #6a1f57, #9a1c4d, #bb3232);
    overflow-x: hidden;
    width: 100%
}

canvas {
    margin-left: auto;
    margin-right: auto;
}

input {
    height: 75px;
    width: 100%;
    background: transparent;
    border: transparent;
}

button {
    width: 25%;
    height: 60px;
    margin: 19px 10vw;
    border-radius: 50px;
    background: #bbbbbb20;
    font-size: 100%;
    color: #fff;
    font-family: century-gothic;
    text-transform: full-width uppercase;
}


#Control {

    margin: 0 -20px;

}
  </style>
  <script>
    const props = {
    panelWidth: 32,
    panelHeight: 8,
    borderWidth: 4,
    canvasMargin: 10, // if you change this also change in style.css for centering
  };
  
  const state = {
      cellSize: 0,
      canvasWidth: 0,
      canvasHeight: 0,
      panelData: [],
      lastX: -1,
      lastY: -1,
      ui: {
          canvas: undefined,
          colorPicker: undefined,
          resetButton: undefined,
          fillButton: undefined,
      },
      color: "#ffff00"
  
  };
  
  function initialise() {
  
  
      document.getElementById("fillBucket").style.color=state.color;
      let windowWidth = parseInt(document.body.clientWidth);
  
      computeCellSize();
  
      let canvas = document.getElementById('canvas1');
  
      state.ui.canvas = canvas;
  
      state.canvasWidth = windowWidth;
      state.canvasHeight = windowWidth * (props.panelHeight / props.panelWidth);
      canvas.height = state.canvasHeight;
      canvas.width = state.canvasWidth;
  
      for (let x = 0; x < props.panelWidth; x++) {
          state.panelData[x] = [];
          for (let y = 0; y < props.panelHeight; y++) {
              state.panelData[x][y] = "#000000";
          }
      }
      state.ui.colorPicker = document.getElementById('colorPicker');
      document.getElementById('colorPicker').addEventListener("change", watchColorPicker, false);
  
      state.ui.fillButton = document.getElementById("fill");
      state.ui.fillButton.addEventListener("click", function () {
          fill(state.color);
      });
      state.ui.resetButton = document.getElementById("reset");
      state.ui.resetButton.addEventListener("click", function () {
          fill("#000000");
      });
  
      state.ui.canvas.addEventListener("mousedown", onMouseDown, false);
  
  
      window.addEventListener("resize", reComputeSize);
  
      reComputeSize();
      draw();
  }
  
  function computeCellSize() {
      let windowWidth = parseInt(document.body.clientWidth);
  
      state.cellSize = windowWidth - 2 * props.canvasMargin;
      state.cellSize -= (props.borderWidth * (props.panelWidth + 1));
      state.cellSize /= props.panelWidth;
      state.cellSize = parseInt(state.cellSize);
  }
  
  function reComputeSize() {
  
      let windowWidth = parseInt(document.body.clientWidth);
      computeCellSize();
  
      state.canvasWidth = windowWidth;
      state.canvasHeight = windowWidth * (props.panelHeight / props.panelWidth);
  
      let canvas = document.getElementById('canvas1');
      canvas.height = state.canvasHeight;
      canvas.width = state.canvasWidth;
  
      draw();
  
  }
  
  function fill(color) {
      for (let x = 0; x < props.panelWidth; x++) {
          for (let y = 0; y < props.panelHeight; y++) {
              if (state.panelData[x][y] != color) {
                  state.panelData[x][y] = color;
                  let r = parseInt(color.substring(1, 3), 16);
                  let g = parseInt(color.substring(3, 5), 16);
                  let b = parseInt(color.substring(5, 7), 16);
  
                  sendData(x, y, r, g, b);
              }
          }
      }
      draw();
  }
  
  function watchColorPicker(event) {
      state.color = event.target.value;
      document.getElementById("fillBucket").style.color=state.color;
  }
  
  function onMouseDown(event) {
  
  
      function onMouseMove(event) {
          var canvas_x = event.pageX - 10;
          var canvas_y = event.pageY - 10;
  
  
  
          if (canvas_x >= 0 && canvas_x <= state.canvasWidth && canvas_y >= 0 && canvas_y <= state.canvasHeight) {
  
              let targetX = parseInt(canvas_x / (state.cellSize + props.borderWidth) / 1);
              let targetY = parseInt(canvas_y / (state.cellSize + props.borderWidth) / 1);
  
              if (state.color != state.panelData[targetX][targetY]) {
                  state.panelData[targetX][targetY] = state.color;
                  //console.log(state.color);
                  let r = parseInt(state.color.substring(1, 3), 16);
                  let g = parseInt(state.color.substring(3, 5), 16);
                  let b = parseInt(state.color.substring(5, 7), 16);
  
                  sendData(targetX, targetY, r, g, b);
  
  
              }
              draw();
          }
      }
  
      function onMouseUp(event) {
          document.removeEventListener('mousemove', onMouseMove);
          document.removeEventListener('mouseup', onMouseUp);
      }
      document.addEventListener('mousemove', onMouseMove);
      document.addEventListener('mouseup', onMouseUp);
  }
  
  
  function sendData(x, y, r, g, b) {
      if (webSocket.readyState === webSocket.OPEN) {
          let color = state.panelData[x][y];
  
          let r1 = color.r;
          let g1 = color.g;
          let b1 = color.b;
          if (r != r1 || g != g1 || b != b1) {
              webSocket.send([x, y, r, g, b]);
          }
      }
  }
  
  function draw() {
  
      state.ui.canvas = document.getElementById("canvas1").getContext("2d");
      document.getElementById("canvas1").background = "f00000";
      state.ui.canvas.fillStyle = "#f00000";
      state.ui.canvas.fill();
  
      //    console.log(state.canvasHeight);
  
  
      for (let x = 0; x < props.panelWidth; x++) {
          for (let y = 0; y < props.panelHeight; y++) {
              state.ui.canvas.fillStyle = state.panelData[x][y];
              state.ui.canvas.fillRect((state.cellSize + props.borderWidth) * x,
                  (state.cellSize + props.borderWidth) * y,
                  state.cellSize,
                  state.cellSize);
          }
      }
  }
  
  
  let wsUrl = window.location.protocol === "https:" ? "wss://" : "ws://";
  wsUrl += window.location.host + window.location.pathname;
  wsUrl += "draw";
  
  console.log("WebSocket to", wsUrl);
  const webSocket = new WebSocket(wsUrl);
  </script>
  
<body onload=initialise()>
  <canvas id="canvas1">
    Canvas tag not supported</canvas>
  <div id="Control">
    <input type="color" id="colorPicker" name="colorPicker" value="#ffff00">
    <button id="fill">
      <i class="fas fa-fill-drip" id="fillBucket"></i>fill
    </button>
    <button id="reset">
      <i class="fas fa-fill-drip" aria-hidden="true" style="color: #000;"></i>reset
    </button>
  </div>

</body>

</html>
  )========";

WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);


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
