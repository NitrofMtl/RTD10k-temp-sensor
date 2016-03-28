/* RTD10kB3950 is a simple low cost formula for an RTD NTC (negative tempeture coeficient)
  of 10Kohm at 25 degres C with a Beta of 3950.

This sketch have been created to reduce the error of each input due to the reference resistor tolerance.

methode:
  -Put a standar 10k resistor with the smaller tolerance the you can found instead og the RTD.
  -Let the arduino runnig for some time for the resistor reach his operative self tempeture.
  -Run the RTD10K.runCalibration(analogread) function.
  -the function will return to the serial monitor the real value of the reference resistor and the value to add to you sketch to the
    RTD10k::calibrateRref(analogPin, correction)

    Copyright (c) 18/07/2015

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

int Ainput[] = {A0, A1, A2, A3, A4, A4, A6, A7, A7, A9}; //set inputs pins for RTD



RTD10k Ain;//start an instance of library

void setup() {
  Serial.begin(9600);//start serial port
  analogReadResolution(12);//arduino DUE only
  Ain.initialize(3.3, 12); //set the reference input voltage 3.3V or 5V, and input resolution 10 or 12 (arduino DUE only)
}

void loop() {
  for (int i = 0 ; i < 10; i++) { //run loop that scan all first 10 analog input
    Ain.runCalibration(i); //function that calculate the correction value
  }
  delay (3000);
}



