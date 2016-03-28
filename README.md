# RTD10k-temp-sensor

Read temperature with thermodynamic resistor with negative temperature coefficien (NTC).

the probe is PANR103395 10kOhm with a Beta of 3950.

Source formula for temp calculation:

  ---    T = ( 1/ ( (1/B) * ln( R/R25C ) +  ( 1/298.00 ) )  -273 );
  
  
