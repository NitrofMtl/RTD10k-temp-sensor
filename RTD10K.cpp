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

//////////---------------------------------------////////////////////////////////////////////

RTD10k::RTD10k(){}

RTD10k::RTD10k(float vRef, int RESO){
    _vRef = vRef;
  if(RESO == 12) _RESO = 4095;
}

void RTD10k::setRtd(float vRef, int RESO){
    _vRef = vRef;
  if(RESO == 12) _RESO = 4095;
}


float RTD10k::read(int selecInput) {//do reading loop
  int averageIn = average(selecInput); //analoRead(selecInpput)

  //electric value calculation
  float Vin = (averageIn) * _vRef / _RESO;  //calculate voltage to analog pin  
  float _rRef = rRef; //add the offset to default reference resistor value  
  float resistance = (Vin / (_vRef - Vin) * _rRef); //calculate the resistance plug into the input

  float temp = (1/( (1/3950.00) * log(resistance/10000.00) +  (1/298.00) )  -273);  // resistance to temp formula
  if (temp < -50){ //limite the lower range to -50C
    temp = -50;  
  }
  return temp;  //return tempeture in C degre
}


//////////---------------------------------------////////////////////////////////////////////

///////////////****** calibration functions !!!
void RTD10k::runCalibration(int selectInput){

 int averageIn = 0;
 averageIn = average(selectInput);
  
  //electric value calculation
  float Vin = averageIn * _vRef / _RESO;

  float realRref = (_vRef-Vin)*10000/Vin;
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
