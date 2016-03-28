/* RTD10kB3950 is a simple, low cost formula for an RTD NTC (negative tempeture coeficient) 
  of 10Kohm at 25 degres C with a Beta of 3950.
  
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

#ifndef RTD10k_h
#define RTD10k_h
#include "Arduino.h"
#include <math.h>
    
class RTD10k
{
  public:
    float temp;   //give tempeture
    float Vin;  //voltage to the analoge pin input
    float resistance;   //resistance in ohm of the RTD
    int average(int inputAv); //average calculation function

    void initialize(float Vref = 5,int reso = 10);  //referance voltage 3.3 or 5 V and input resolution
    float read(int selecInput);
    void serialInputMon(String StrInput);
    void runCalibration(int input);
    void calibrateRref(int input, float offset);

  private:
  
    int _selecInput;
    float _temp;
    int _reso;
    float _Vref;
    float _RrefOffset[12];
   
};

#endif
