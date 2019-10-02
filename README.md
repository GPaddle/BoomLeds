
# Big RGB LEDs Panel

Arduino Project with 8x32 LED pannel

## Getting Started

### Prerequisites
<ul>
<ol>
<li>Arduino IDE</li>
<li>8x32 LED Pannel (5V Addressable Leds)</li>
<li>Arduino board</li>
</ol>
</ul>

## Functions to display on the pannel




<ul>
<li>void affichageTab(uint16_t t[][32])</li>
    display a n x 32 tab of long (color)<br />
<li>void affichageTab8x8(uint16_t t[][8])</li>
    display a 8 x 8 tab on the left of the screen<br />
<li>void affichageTexte(String s, int x, int y)</li>
    display a 5 pixel heigh text (s) on the coordinates (x,y)<br />
<li>void affichageNumLong(long n, int x, int y)</li>
    display a long number (n) on the coordinates (x,y)<br />
<li>void affichageNum(int n, int x, int y)</li>
    display a short number (n)(2 digit max) positive or negative on the coordinates (x,y)<br />
<li>void affichageChiffre(int t, int x, int y)</li>
    function used to display a single digit (used by the two previous functions)<br />
<li>void affichageThermometre(int temperature)</li>
    display a thermometre and color it in function of the temperature + display the value<br />
<li>void affichageHorloge(boolean affichageLong)</li>
    display the time, two way to display it : long HH:MM:SS or short HH:MM<br />
<li>void scrollInOutVertical(String s, int x, int y)</li>
    display a text on the coordinates (x,y) with a smooth in/out way<br />
    if too long to be display on the screen, it scroll horizontally until the message is show<br />
</li>
</ul>

## Authors

 * **Guillaume Keller** - *Initial work* - [GPaddle](https://github.com/GPaddle)
