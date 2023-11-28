# RTD10k-temp-sensor

Read temperature with thermodynamic resistor with negative temperature coefficien (NTC).

the probe is PANR103395 10kOhm with a Beta of 3950.

Source formula for temp calculation:

  ---    T = ( 1/ ( (1/B) * ln( R/R25C ) +  ( 1/298.00 ) )  -273 );
  
  
## usage

-create an instance
````
//For analog resolution from 8 to 16 bits:
//RTD_Reso::RESO_8 to RTD_Reso::RESO_16
//Value must fit the analogResolution

RTD10k rtd(RTD_Reso::RESO_10);
````

-Default resolution is RESO10, so you can call the constructor emty:
```
RTD10k rtd();
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