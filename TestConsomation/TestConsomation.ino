#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
#include <Fonts/TomThumb.h>

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                            NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);


uint16_t White = matrix.Color(255, 255,  255);




void setup() {

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(matrix.Color(200, 200, 200));
  matrix.setFont(&TomThumb);

}

void loop() {


  matrix.setBrightness(40);
  for (int i = 0; i < 32; i++) {
    matrix.fillRect(i, 0, 1, 8, matrix.Color(255, 255, 255));
    matrix.show();
    delay(2000);
  }


  matrix.fillScreen(0);


  matrix.setBrightness(20);
  for (int i = 0; i < 32; i++) {
    matrix.fillRect(i, 0, 1, 8, matrix.Color(255, 255, 255));
    matrix.show();
    delay(2000);
  }


  matrix.fillScreen(0);

  matrix.setBrightness(10);
  for (int i = 0; i < 32; i++) {
    matrix.fillRect(i, 0, 1, 8, matrix.Color(255, 255, 255));
    matrix.show();
    delay(2000);
  }




  for (int i = 1; i <= 5; i++) {


    matrix.fillScreen(0);
    matrix.setBrightness(5 * i);
    matrix.setCursor(0, 7);
    matrix.print(5 * i);
    matrix.show();
    delay(500);

    matrix.fillScreen(matrix.Color(255, 255, 255));
    matrix.fillRect(0, 0, 16, 8, matrix.Color(0, 0, 0));
    matrix.show();

    delay(5000);

    matrix.fillScreen(matrix.Color(255, 255, 255));
    matrix.show();

    delay(5000);

  }
}
