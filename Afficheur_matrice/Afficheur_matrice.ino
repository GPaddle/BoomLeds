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
  matrix.setFont(&TomThumb);

}

//const 
double graphique[20] = {4, 20, 51, 41, 2, 30, 4, 54, 8, 1, 60, 42, 48, 75, 6, 2.0, 14.5, 16, 17, 18};


const boolean chiffres[5][30] = {
  {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}
};

const uint16_t thermometre[8][32] = {
  {0,  0,  0,  White,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  0,  White,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  0,  White,  0,  White,  0,  0,  0,  White,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  White,  0,  0,  0,  White,  0,  0,  0,  White,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, White,  0,  0,  0,  0,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, White,  0,  0,  0,  0,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  White,  0,  0,  0,  White,  0,  0,  White,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {0, 0,  0,  White,  White,  White,  0,  0,  0,  0,  White,  0,  White,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};

unsigned const long SECONDE = 1000;
unsigned const long MINUTE = 60000;
unsigned const long HEURE = 3600000;
uint32_t tempsDepart = 3 * HEURE + 9 * MINUTE;


uint16_t Strava[8][8] = {
  {0,  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  0},
  {matrix.Color(242.0, 91.0, 14.0), matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0)},
  {matrix.Color(242.0, 91.0, 14.0), matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0)},
  {matrix.Color(242.0, 91.0, 14.0), White,  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0)},
  {matrix.Color(242.0, 91.0, 14.0), matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  White},
  {matrix.Color(242.0, 91.0, 14.0), matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0)},
  {matrix.Color(242.0, 91.0, 14.0), matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0)},
  {0, matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  matrix.Color(242.0, 91.0, 14.0),  White,  matrix.Color(242.0, 91.0, 14.0),  0}
};



void loop() {
  matrix.setBrightness(5);

  /*matrix.drawLine(1,2,25,6,White);

    matrix.drawRect(31-5,2,5,5,White);

    matrix.show();
    delay(2000);
  */
  matrix.fillScreen(0);


  /* demoHorloge();
    demoAffichageNumEtImage();
    demoAffichageTexte();
    demoThermometre() ;
  */

  dessinGraph(graphique);
  demoAffichageScrollInOut();



  //  demoAll();

}

// Function used to display a 8x32 image store in a uint16_t array

void affichageTab(uint16_t t[][32]) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 8; j++) {
      matrix.drawPixel(i, j, t[j][i]);
    }
  }
}

void affichageIcone(uint16_t t[][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      matrix.drawPixel(i, j, t[j][i]);
    }
  }
}

void affichageTexte(String s, int x, int y) {
  matrix.setCursor(x, 7 - y);
  matrix.print(s);
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
  // Little c
  //Drawing the celcius symbol on the bottom right of the display

  matrix.drawPixel(30, 6, c);
  matrix.drawPixel(30, 4, c);
  matrix.drawPixel(29, 6, c);
  matrix.drawPixel(29, 5, c);
  matrix.drawPixel(29, 4, c);

  //function to display the temperature value
  int lon = String(temperature).length();

  matrix.setCursor(15 + (3 - lon) * 4, 7);

  matrix.print(temperature);


}





//Clock function, take a boolean to know if we display the seconds

void affichageHorloge(boolean affichageLong) {

  matrix.fillScreen(0);
  int decalageSecondes = 10;

  uint32_t temps = tempsDepart + millis();

  uint16_t h = (temps / HEURE);
  uint16_t m = (temps % HEURE) / MINUTE;
  uint16_t s = ((temps % HEURE) % MINUTE) / SECONDE;

  String heureAffiche = "";

  if (affichageLong) {
    decalageSecondes = 0;
  }

  if (h < 10) {
    matrix.setCursor(4 + 4 + decalageSecondes, 6);
  } else {
    matrix.setCursor(4 + decalageSecondes, 6);
  }

  heureAffiche += h;
  heureAffiche += ":";

  if (m < 10) {
    heureAffiche += "0";
  }
  heureAffiche += m;




  if (affichageLong) {
    heureAffiche += ":";
    if (s < 10) {
      heureAffiche += "0";
    }

    heureAffiche += s;
    decalageSecondes = 10;

  }

  matrix.print(heureAffiche);
}




int borne = 6;

void scrollInVertical(String s, int x, int y) {
  for (int i = borne; i >= 1 ; i--) {

    matrix.fillScreen(0);

    affichageTexte(s, x, y + i);

    delay(350 / (abs(i)));
    matrix.show();
  }
}

void scrollOutVertical(String s, int x, int y) {
  for (int i = borne; i >= 1 ; i--) {

    matrix.fillScreen(0);

    affichageTexte(s, x, y + i );

    delay(350 / (abs(i)));
    matrix.show();
  }
}


void scrollInOutVertical(String s, int x, int y) {

  scrollInVertical(s, x, y);

  if (s.length() > 4) {
    int x2 = x;
    int taille = s.length();
    while (x2 < taille * 3.2) {
      matrix.fillScreen(0);
      affichageTexte(s, x--, y);
      matrix.show();
      delay(100);
      x2++;

    }
    x++;
  } else {
    matrix.fillScreen(0);
    affichageTexte(s, x, y);
    delay(3000);
    matrix.show();

  }
  scrollOutVertical(s, x, y);

}



/*
   ####################################################
   ####################################################
   ############# Demo functions #######################
   ####################################################
   ####################################################
*/




/*
   Show how the clock is display
  first 15 seconds with a long display (HH:MM:SS)
  then short display (HH:MM)
*/
void demoHorloge() {

  affichageHorloge(millis() <= 15000);
  matrix.show();
  delay(100);

}

void demoAffichageNumEtImage() {

  long affiche = 123456;
  for (int i = 0; i < 7; i ++) {
    matrix.fillScreen(0);
    affichageIcone(Strava);

    matrix.setCursor(9, 6);
    matrix.print(affiche);

    delay(600);
    affiche /= 10;

    matrix.show();
  }
}

void demoAffichageTexte() {
  affichageTexte("Hello", 1, 1);
  delay(1000);
  matrix.show();
}


//Demo for the thermometer function

void demoThermometre() {

  for (int i = -20; i < 30; i ++) {
    affichageThermometre(i);
    matrix.show();
    delay(300);
  }
}

void demoAffichageScrollInOut() {

  scrollInOutVertical("Daft Punk - Harder Better Faster Stronger", 4, 1);
  matrix.show();
  delay(200);

  scrollInOutVertical("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do", 4, 1);
  matrix.show();
  delay(200);

}

void demoAll() {
  demoAffichageScrollInOut();
  demoAffichageTexte();
  demoAffichageNumEtImage() ;
  demoHorloge();
  demoThermometre() ;
}

void dessinGraph( double datas[20]) {
  int maxi = datas[0];
  int mini = datas[0];

  for (int i = 0; i < 20; i++) {
    if (maxi < datas[i]) {
      maxi = datas[i];
    } if (mini > datas[i]) {
      mini = datas[i];
    }
  }

matrix.setCursor(1,7);
matrix.print(maxi);
matrix.show();
delay(1000);

  for (int i = 0; i < 20; i++) {
    matrix.drawLine(i,7,i,map(datas[i], mini, maxi, 7,0) ,White);
  if (datas[i]==maxi){
   matrix.drawPixel(i,map(datas[i], mini, maxi, 7,0),Red); 
  }
    if (datas[i]==mini){
   matrix.drawPixel(i,map(datas[i], mini, maxi, 7,0),Green); 
  }
  }
  matrix.show();
  delay(3000);
}
