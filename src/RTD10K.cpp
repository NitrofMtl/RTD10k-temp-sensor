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

#include "RTD10K.h"

//////////---------------------------------------////////////////////////////////////////////
namespace
{
  constexpr uint16_t RTD_AnalogRead[]
  {
    0, 1200, 2850, 4500, 6150, 7800, 9450, 11100, 12750, 14400, 16050, 17700, 19350, 21000, 22650, 24300, 25950, 27600, 29250, 30900, 32550, 34200,
    35850, 37500, 39150, 40800, 42450, 44100, 45750, 47400, 49050, 50700, 52350, 54000, 55650, 57300, 58950, 60600, 62250, 63900, 65535
  };

  //temp table in hundred of celcius degrees
  constexpr int16_t RTD_Temp[]
  {
    15296, 15296, 11562, 9797, 8650, 7801, 7125, 6562, 6077, 5650, 5266, 4916, 4593, 4292, 4008, 3738, 3481, 3233, 2993, 2759, 2530,
    2305, 2082, 1860, 1638, 1416, 1191, 962, 727, 486, 235, -28, -308, -608, -937, -1305, -1729, -2241, -2913, -3956, -3956
  };

};



RTD10k::RTD10k(RTD_Reso reso)
{
  switch (reso){
    case RTD_Reso::RESO_16 :
    bitsUpgrade = 0;
    break;
    case RTD_Reso::RESO_15 :
    bitsUpgrade = 1;
    break;
    case RTD_Reso::RESO_14 :
    bitsUpgrade = 2;
    break;
    case RTD_Reso::RESO_13 :
    bitsUpgrade = 3;
    break;
    case RTD_Reso::RESO_12 :
    bitsUpgrade = 4;
    break;
    case RTD_Reso::RESO_11 :
    bitsUpgrade = 5;
    break;
    case RTD_Reso::RESO_10 :
    bitsUpgrade = 6;
    break;
    case RTD_Reso::RESO_9 :
    bitsUpgrade = 7;
    break;
    case RTD_Reso::RESO_8 :
    bitsUpgrade = 8;
    break;
  }
  
}

float RTD10k::getTemp(unsigned int read) const
{ 
  //upgrade read to 16 bits resolution
  read = read << bitsUpgrade;
  //find where <<read>> is in look up on table
  int i=0;
  if ( read > 0xFFFF ) { //protect 16bits from overflow
    return NAN;
  }
  while( RTD_AnalogRead[i] < read ) i++;
  //find m and b value of y=mx+b ==>
  // Sloap: m = (y2-y1)/(x2-x1)
  float m = ( RTD_Temp[i]-RTD_Temp[i-1] ) / ( static_cast<float>(RTD_AnalogRead[i]-RTD_AnalogRead[i-1]) );
  // y at x0: b = y1 - m*x1
  float b = RTD_Temp[i-1] -m*RTD_AnalogRead[i-1];
  
  //return temp back from hundred to celcius
  return (m*read+b) /100;
}
