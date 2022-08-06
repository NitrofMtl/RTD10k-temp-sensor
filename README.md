# RTD10k-temp-sensor

Read temperature with thermodynamic resistor with negative temperature coefficien (NTC).

the probe is PANR103395 10kOhm with a Beta of 3950.

Source formula for temp calculation:

  ---    T = ( 1/ ( (1/B) * ln( R/R25C ) +  ( 1/298.00 ) )  -273 );
  
  
## usage

-create an instance
````
RTD10K rtd;
//or, for 12 bits ADC
//RTD10k rtd(RTD10K_ADC_12BIT);
````

-Convert analog reading to temperature
````
  int aInput1 = A0;
  int aInput2 = A2;
  float temperature1 = rtd.getTemp(analogRead(aInput1)); //do the reading temps
  float temperature2 = rtd.getTemp(analogRead(aInput2));
  
  Serial.print("Temperature 1 is: ");
  Serial.print(temperature);
  Serial.write(186);
  Serial.println('c');
````