/* RTD10kB3950 is a simple low cost formula for an RTD NTC (negative temperature coeficient)
  of 10Kohm at 25 degres C with a Beta of 3950.
  

Formula is:

B = Beta,
T = current temperature
R25C = resistance of RTD at 25 Celsius
R = RTD resistance at current temp

    -------------------

    T = ( 1/ ( (1/B) * ln( R/R25C ) +  ( 1/298.00 ) )  -273 );

    -------------------

    ln in natural logarythme, will be log() fonction in arduino 


 Copyright (c) 20/05/2015

    By Nitrof

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <RTD10k.h>

int Ainput[] = {0,1,2,3,4,5,6,7,8,9}; //set input pin for RTD
float temperature = 0; //ouput variable
String strRoomTemp = "Room Temperature"; //set the name of the input for serial print
//float calibOffset[] = {332.67,262.25,403.59,322.58,222.22,505.76,660.95,132.74,142.65,403.59};
float calibOffset[] = {0,0,0,0,0,0,0,0,0,0};
RTD10k Ain;//start an instance of library

void setup() {
  Serial.begin(9600);//start serial port
  analogReadResolution(12);//arduino DUE only
  Ain.initialize(3.3, 12); //set the reference input voltage to 3.3V or 5V, and input resolution 10 or 12 (arduino DUE only)
for (int i=0; i <= 9; i++){
  Ain.calibrateRref(i,calibOffset[i]); //calibrate shield Reference resistor, (analog in, calibration value find with calibration sketch)
}
}

void loop() {
for (int i=0; i <= 9; i++){
  temperature = Ain.read(Ainput[i]); //do the reading temps loop

  Ain.serialInputMon(strRoomTemp); //pring all value to the serial port
}
  delay (1000);
}
