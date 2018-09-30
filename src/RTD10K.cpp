/* RTD10kB3950 is a simple, low cost formula for an RTD NTC (negative tempeture coeficient) 
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

#include "RTD10k.h"


//////////---------------------------------------////////////////////////////////////////////

RTD10k::RTD10k() : bitTable{4093,3994,3953,3899,3828,3739,3628,3494,3336,3156,
    2954,2737,2509,2277,2047,1824,1613,1418,1240,1080,938,814,706,612,530,461,400,349,304,266,233,
    205,181,160,141,126,112,100,89,80,0
    },
     tempTable{-45, -40,-35,-30,-25,-20,-15,10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,
90,95,100,105,110,115,120,125,130,135,140,145,150,155}
{}

RTD10k::RTD10k(int RESO) : bitTable{4093,3994,3953,3899,3828,3739,3628,3494,3336,3156,
    2954,2737,2509,2277,2047,1824,1613,1418,1240,1080,938,814,706,612,530,461,400,349,304,266,233,
    205,181,160,141,126,112,100,89,80,0
    },
     tempTable{-45,-40,-35,-30,-25,-20,-15,10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,
90,95,100,105,110,115,120,125,130,135,140,145,150,155}
     {
  if(RESO == 12) _RESO = 4095;
}

void RTD10k::setRtd(int RESO){
  if(RESO == 12) _RESO = 4095;
}


float RTD10k::read(int selecInput) {//do reading loop   
  int x = analogRead(selecInput); //analoRead(selecInpput)
  return readBit(x);
}

float RTD10k::readBit(int x) {//do reading loop
   
  //find where look up on table
  int i=0;
  while(bitTable[i]>x) i++;
  //find m and b value of y=mx+b ==>
  // m = (y1-y2)/(x1-x2) 
  long y1 = longToFixed(tempTable[i-1]);
  long y2 = longToFixed(tempTable[i]);
  long x1 = bitTable[i-1];
  long x2 = bitTable[i];
  long mFixed = (y1-y2) / (x1-x2);
  //b = y1 - m*x1
  long bFixed = y1 - mFixed*x1;
  //return mx+b
  return fixedTofloat(mFixed*x)+fixedTofloat(bFixed);
}