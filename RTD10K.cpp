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

#include "Arduino.h"
#include "RTD10k.h"

const int numReadings = 20; //set average to count

//////////---------------------------------------////////////////////////////////////////////

void RTD10k::initialize(float Vref,int reso) {
  _Vref = Vref;
  _reso = reso;
  for (int i = 0; i < 12; i++){ //initiate the RrefOffset to 0 
    _RrefOffset[i] = 0;
  }
}

//////////---------------------------------------////////////////////////////////////////////

float RTD10k::read(int selecInput) {//do reading loop


  int averageIn = average(selecInput); //analoRead(selecInpput)

  if (_reso == 10) {
    averageIn = map(averageIn, 0, 1023, 0, 4095); //mapping for 10bits resolution, else consider 12bit
  }

  //electric value calculation
  
  Vin = (averageIn) * _Vref / 4095;  //calculate voltage to analog pin
  
  float Rref = 10000; //set default resistor value to 10k ohm
  Rref = 10000 + _RrefOffset[selecInput]; //add the offset to default reference resistor value
  
  resistance = (Vin / (_Vref - Vin) * Rref); //calculate the resistance plug into the input

_temp = (1/( (1/3950.00) * log(resistance/10000.00) +  (1/298.00) )  -273);  // resistance to temp formula
if (_temp < -50){ //limite the lower range to -50C
  _temp = -50;  
}
temp = _temp; //return tempeture in C degre
return temp;
}

//////////---------------------------------------////////////////////////////////////////////

void RTD10k::serialInputMon(String(ipName)) {    ///print all value for an input on demande
  //print on serial port input reading  
  if (Serial.available() > 0) ; {
    Serial.println( "input; " + ipName + "; " + Vin + "Volt; R= " + resistance + " ohm Tempeture= " + temp + "C");
  }
}

//////////---------------------------------------////////////////////////////////////////////

///////////////****** calibration functions !!!
void RTD10k::runCalibration(int selectInput){

 int averageIn = 0;
 averageIn = average(selectInput);

 if (_reso == 10) {
    map(averageIn, 0, 1023, 0, 4095); //mapping for 10bits resolution
  }
  
  //electric value calculation
  Vin = averageIn * _Vref / 4095;

  float realRref = (_Vref-Vin)*10000/Vin;
  float Offset = 0;
  Offset = realRref-10000;

  String prntStatus = "input " ;
  prntStatus += String(selectInput) += ":";
  prntStatus +=  String(realRref) += "ohm , correction = ";
  prntStatus += String(Offset);

  if (Serial.available() > 0) ;{
    Serial.println(prntStatus);
  }
}

//////////---------------------------------------////////////////////////////////////////////



void RTD10k::calibrateRref(int input, float offset){

 _RrefOffset[input] = offset;
 //Serial.println(_RrefOffset[input]); for troubleshoot
}

//////////---------------------------------------////////////////////////////////////////////

int RTD10k::average(int inputAv){

  int output = 0;
  int count = 0;
  for (int i = 0; i < numReadings; i++){
    int reading = analogRead(inputAv);
    count += reading;
  }
  output = count/numReadings;
  return output;
}

//////////---------------------------------------////////////////////////////////////////////
