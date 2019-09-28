#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                            NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);


uint16_t White = matrix.Color(255, 255,  255);
uint16_t Red =   matrix.Color(255, 0,    0);
uint16_t Green = matrix.Color(0,   255,  0);
uint16_t  Blue =  matrix.Color(0,   0,    255);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};



void setup() {

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(matrix.Color(200, 200, 200));
}


const boolean chiffres[5][30] = {
  {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}
};

const uint16_t thermometre[8][32] = {
  {0,  0,  0,  White,  0,  White,  0,  0,  0,  White,  0,  0,  White,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  0,  White,  0,  White,  0,  0,  0,  0,  White,  White,  0,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  0,  White,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  White,  0,  0,  0,  White,  0,  0,  White,  0,  0,  White,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, White,  0,  0,  0,  0,  0,  White,  0,  0,  White,  White,  0,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, White,  0,  0,  0,  0,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  White,  0,  0,  0,  White,  0,  0,  White,  0,  0,  White,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  0,  White,  White,  White,  0,  0,  0,  0,  White,  White,  0,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};

unsigned const long SECONDE = 1000;
unsigned const long MINUTE = 60000;
unsigned const long HEURE = 3600000;
uint32_t tempsDepart = 3 * HEURE + 9 * MINUTE;



void loop() {
  matrix.setBrightness(5);

  long i = millis();
  while (millis() - i < 5000) {
    affichageHorloge(true);
    delay(200);
    matrix.show();
  }

  demoThermometre();

  long j = millis();
  while (millis() - j < 2000) {
    affichageHorloge(false);
    delay(200);
    matrix.show();
  }

  //  affichageTab(tab);








}

// Function used to display a 8x32 image store in a uint16_t array

void affichageTab(uint16_t t[][32]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 8; j++) {
      matrix.drawPixel(i, j, t[j][i]);
    }
  }
}




/*
   n : the number to display
   x : x coordinate
   y : y coordinate

   display a 5 pixels heigh number (2 digits max + negative numbers)
*/

void affichageNum(int n, int x, int y) {



  //Number of digit to display
  int lon = String(n).length();



  int tem = n;

  if (tem < 0) {
    lon--;

    //Choose if it's a 1,2 or 3 digit number to place the minus at the right coordinates
    int decalageSigne = 2;
    if (tem < -99) {
      decalageSigne = 0;
    } else if (tem < -9) {
      decalageSigne = 1;
    }

    //Draw of the - sign
    matrix.drawPixel( x  , y + 2 , White);
    matrix.drawPixel( x + 1 , y + 2 , White);

    //Use the positive value to not worry about the numbers tab position
    tem = abs(tem);

  }


  if (tem > 99) {
    int tem3 = abs(n) / 100;
    affichageChiffre(tem3, x, y);
  }

  if (tem > 9) {
    int tem2 = abs(n) / 10;
    if (lon == 3) {
      tem2 = tem2 % 10;
    }

    if (lon == 3) {
      affichageChiffre(tem2, x + 4, y);
    } else if (lon == 2) {
      affichageChiffre(tem2, x , y);
    }
  }

  //Repeat the procedure to print the unit digit
  tem = tem % 10;

  if (lon == 3) {
    affichageChiffre(tem, x + 8, y);
  } else if (lon == 2) {
    affichageChiffre(tem, x + 4, y);
  } else if (lon == 1) {
    affichageChiffre(tem, x , y);
  }

  //Use the chiffres array that contains all the informations to print numbers in a 5 pixels heigh
}


/*
   Display a single number at the x,y position
*/

void affichageChiffre(int t, int x, int y) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      if (chiffres[j][i + 3 * t]) {
        matrix.drawPixel(x + 3  + i , y + j, White);
      }
    }
  }
}




//Affichage : [-inf;0[
//            [0;5[
//            [5;10[
//            [10;20[
//            [20;+inf[


void affichageThermometre(int temperature) {

  // 5 Colors used in the thermometre function

  long therm1 = matrix.Color(96, 144, 248);
  long therm2 = matrix.Color(111, 131, 212);
  long therm3 = matrix.Color(199, 51, 82);
  long therm4 = matrix.Color(217, 34, 56);
  long therm5 = Red;

  //Background of the thermometre function

  affichageTab(thermometre);

  //Current color
  long c;

  // Choosing the color first :

  // [-inf;0[   ->  Light blue
  //                Low level display
  if (temperature < 0) {

    c = therm1;


    // [0;5[   ->     Light blue
    //                Low level +1 display
  } else  if (temperature < 5) {

    c = therm2;
    matrix.drawPixel(4, 2, c);


    // [5;10[   ->    Light red
    //                Low level+1 display
  } else if (temperature < 10) {

    c = therm3;
    matrix.drawPixel(4, 2, c);


    // [10;20[   ->   Light red
    //                Mid level display
  } else if (temperature < 20) {

    c = therm4;
    matrix.drawPixel(4, 1, c);
    matrix.drawPixel(4, 2, c);


    // [20;+inf[  ->  Red
    //                High level display
  } else {

    c = therm5;
    matrix.drawPixel(4, 1, c);
    matrix.drawPixel(4, 2, c);
    matrix.drawPixel(4, 0, c);
  }


  //Filling a central square with the main color
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      matrix.drawPixel(3 + j, 3 + i, c);
    }
  }

  //Filling the corners

  matrix.drawPixel(2, 4, c);
  matrix.drawPixel(2, 5, c);
  matrix.drawPixel(6, 4, c);
  matrix.drawPixel(6, 5, c);
  //  int x1 = 16, y1 = 2;

  c = White;

  // °
  //Drawing the degree symbol on the top right of the display

  matrix.drawPixel(27, 1, c);
  matrix.drawPixel(28, 1, c);
  matrix.drawPixel(27, 2, c);
  matrix.drawPixel(28, 2, c);

  // c
  //Drawing the celcius symbol on the bottom right of the display

  matrix.drawPixel(30, 6, c);
  matrix.drawPixel(30, 4, c);
  matrix.drawPixel(29, 6, c);
  matrix.drawPixel(29, 5, c);
  matrix.drawPixel(29, 4, c);

  //function to display the temperature value
  int lon = String(temperature).length();

  if (temperature < 0) {
    affichageNum(temperature, 4 * (3 - lon) + 12 + 4, 2);
  } else {
    affichageNum(temperature, 4 * (3 - lon) + 12, 2);
  }
}




//Demo for the thermometer function

void demoThermometre() {

  for (int i = -20; i < 30; i ++) {
    affichageThermometre(i);
    matrix.show();
    delay(300);
  }
}

//Clock function, only take a boolean to know if we display the seconds

void affichageHorloge(boolean affichageLong) {

  matrix.fillScreen(0);
  int decalageSecondes = 0;

  uint32_t temps = tempsDepart + millis();

  uint16_t h = (temps / HEURE);
  uint16_t m = (temps % HEURE) / MINUTE;
  uint16_t s = ((temps % HEURE) % MINUTE) / SECONDE;

  //Check if we want the long display
  if (affichageLong) {
    decalageSecondes = 10;

    //if there is only a single digit second, add a 0 before to keep a 2 digits standard

    if (s < 10) {
      affichageNum(0, 21, 1);
      affichageNum(s, 25, 1);
    } else {

      affichageNum(s, 21, 1);
    }

    //Second range of ":"
    matrix.drawPixel(22 , 4, White);
    matrix.drawPixel(22 , 2, White);
  }

  //Display the HH and MM parts

  if (h < 10) {
    affichageNum(h, 15 - decalageSecondes, 1);
  } else {
    affichageNum(h, 11 - decalageSecondes, 1);
  }

  if (m < 10) {
    affichageNum(0, 21 - decalageSecondes, 1);
    affichageNum(m, 25 - decalageSecondes, 1);

  } else {
    affichageNum(m, 21 - decalageSecondes, 1);
  }

  //First range of ":"

  matrix.drawPixel(22 - decalageSecondes, 4, White);
  matrix.drawPixel(22 - decalageSecondes, 2, White);

}

/*Show how the clock is display
  first 15 seconds with a long display (HH:MM:SS)
  then short display (HH:MM)
*/
void demoHorloge() {

  affichageHorloge(millis() <= 15000);
  matrix.show();
  delay(100);

}
