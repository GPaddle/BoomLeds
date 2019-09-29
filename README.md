# LaMetric-like

Arduino Project with 8x32 LED pannel

## Getting Started

### Prerequisites

Arduino IDE
8x32 LED Pannel (5V Addressable Leds)
Arduino board

## Functions to display on the pannel




void affichageTab(uint16_t t[][32])
    display a n x 32 tab of long (color)
void affichageTab8x8(uint16_t t[][8])
    display a 8 x 8 tab on the left of the screen
void affichageTexte(String s, int x, int y)
    display a 5 pixel heigh text (s) on the coordinates (x,y)
void affichageNumLong(long n, int x, int y)
    display a long number (n) on the coordinates (x,y)
void affichageNum(int n, int x, int y)
    display a short number (n)(2 digit max) positive or negative on the coordinates (x,y)
void affichageChiffre(int t, int x, int y)
    function used to display a single digit (used by the two previous functions)
void affichageThermometre(int temperature)
    display a thermometre and color it in function of the temperature + display the value
void affichageHorloge(boolean affichageLong)
    display the time, two way to display it : long HH:MM:SS or short HH:MM
void scrollInOutVertical(String s, int x, int y)
    display a text on the coordinates (x,y) with a smooth in/out way
    if too long to be display on the screen, it scroll horizontally until the message is show


## Authors

 * **Guillaume Keller** - *Initial work* - [GPaddle](https://github.com/GPaddle)
