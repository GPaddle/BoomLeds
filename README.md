# LaMetric-like

Arduino Project with 8x32 LED pannel

## Getting Started

### Prerequisites

Arduino IDE<br />
8x32 LED Pannel (5V Addressable Leds)<br />
Arduino board<br />

## Functions to display on the pannel




void affichageTab(uint16_t t[][32])<br />
    display a n x 32 tab of long (color)<br />
void affichageTab8x8(uint16_t t[][8])<br />
    display a 8 x 8 tab on the left of the screen<br />
void affichageTexte(String s, int x, int y)<br />
    display a 5 pixel heigh text (s) on the coordinates (x,y)<br />
void affichageNumLong(long n, int x, int y)<br />
    display a long number (n) on the coordinates (x,y)<br />
void affichageNum(int n, int x, int y)<br />
    display a short number (n)(2 digit max) positive or negative on the coordinates (x,y)<br />
void affichageChiffre(int t, int x, int y)<br />
    function used to display a single digit (used by the two previous functions)<br />
void affichageThermometre(int temperature)<br />
    display a thermometre and color it in function of the temperature + display the value<br />
void affichageHorloge(boolean affichageLong)<br />
    display the time, two way to display it : long HH:MM:SS or short HH:MM<br />
void scrollInOutVertical(String s, int x, int y)<br />
    display a text on the coordinates (x,y) with a smooth in/out way<br />
    if too long to be display on the screen, it scroll horizontally until the message is show<br />


## Authors

 * **Guillaume Keller** - *Initial work* - [GPaddle](https://github.com/GPaddle)
