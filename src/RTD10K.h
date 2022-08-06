/* RTD10kB3950 is a formula for an RTD NTC (negative tempeture coeficient) 
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

#define RTD10K_ADC_10BIT 4
#define RTD10K_ADC_12BIT 1

const int scale = 16;
#define longToFixed(x)(x*(long)(1<<scale))
#define fixedTofloat(x)(x/(float)(1<<scale))

class RTD10k
{
  public:
    RTD10k(int RESO = RTD10K_ADC_10BIT);
    float getTemp(int x) const; //input by value directly trough sequencer
  private:  
    const int bitTable[41];
    const int tempTable[41];
};

#endif //RTD10k_h
