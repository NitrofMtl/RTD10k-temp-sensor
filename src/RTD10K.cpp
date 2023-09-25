/* RTD10kB3950 is a formula for an RTD NTC (negative tempeture coeficient) 
  of 10Kohm at 25 degres C with a Beta of 3950.


Formula is:

B = Beta,
T = current temperature
R25C = resistance of RTD at 25 Celsius
R = RTD resistance at current temp

    -------------------
    
    T = ( 1/ ( (1/B) * ln( R/R25C ) +  ( 1/298.00 ) )  -273 );
    
    -------------------

    Instead of do complex calculation into arduino, the library use a precalculated lookup table.
*/

#include "RTD10k.h"

//////////---------------------------------------////////////////////////////////////////////

RTD10k::RTD10k(int reso) : bitTable{4093/reso, 3994/reso, 3953/reso, 3899/reso, 3828/reso, 3739/reso, 3628/reso, 3494/reso, 3336/reso, 3156/reso, 2954/reso,
    2737/reso, 2509/reso, 2277/reso, 2047/reso, 1824/reso, 1613/reso, 1418/reso, 1240/reso, 1080/reso, 938/reso, 814/reso, 706/reso, 612/reso, 530/reso,
    461/reso, 400/reso, 349/reso, 304/reso, 266/reso, 233/reso, 205/reso, 181/reso, 160/reso, 141/reso, 126/reso, 112/reso, 100/reso, 89/reso, 80/reso,0
    },
    tempTable{-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,
    90,95,100,105,110,115,120,125,130,135,140,145,150,155}
  {}

float RTD10k::getTemp(int x) const
{//do reading loop
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
