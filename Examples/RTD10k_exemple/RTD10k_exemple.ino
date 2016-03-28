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

int Ainput = A0; //set input pin for RTD
float temperature = 0; //ouput variable
String strRoomTemp = "Room Temperature"; //set the name of the input for serial print
//float calibOffset = 332.67; // example of get value on calibration example
float calibOffset = 0; //comment to try example calibration
RTD10k Ain;//start an instance of library

void setup() {
  Serial.begin(9600);//start serial port
  analogReadResolution(12);//arduino DUE only
  Ain.init(3.3,12); //set the reference input voltage to 3.3V or 5V, and input resolution 10 or 12 (arduino DUE only)
  Ain.calibrateRref(Ainput,calibOffset); //calibrate shield Reference resistor, (analog in, calibration value find with calibration sketch)
}

void loop() {
  temperature = Ain.read(Ainput); //do the reading temps 
  Ain.serialInputMon(strRoomTemp); //print value to the serial port
  delay (1000);
}
