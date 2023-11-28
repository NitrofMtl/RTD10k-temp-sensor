/* 
RTD10kB3950 is a formula for an RTD NTC (negative temperature coeficient)
of 10Kohm at 25 degres C with a Beta of 3950.
  

Formula is:

B = Beta,
T = current temperature
R25C = resistance of RTD at 25 Celsius
R = RTD resistance at current temp

    -------------------

    T = ( 1/ ( (1/B) * ln( R/R25C ) +  ( 1/298.00 ) )  -273 );

    ------------------
*/

#include <RTD10K.h>

int Ainput = A0; //set input pin for RTD
float temperature = 0; //ouput variable
//options fo analog resolution are reso8 to reso16, 8 to 16 bits respectyvely
//default is RESO_10
RTD10k rtd(RTD_Reso::RESO_10);

void setup() {
  Serial.begin(9600);//start serial port
}

void loop() {
  temperature = rtd.getTemp(analogRead(Ainput)); //do the reading temps
  Serial.print("Temperature is: ");
  Serial.print(temperature);
  Serial.println('c');
  delay (1000);
}


