/* detection of C4 = 262Hz  for stopping the car and for other frequencies including A4=440Hz car moves
If the note is “C4”, stop the robot car. If the note is “A4”, allow the robot car to continue its movement.
To match with the frequencies, an error of 2% is allowed. For example, you can
recognize the note as C4 if the peak frequency is in the range of between 257Hz and
267Hz.Based on Professor Yan code 
Example of use of the FFT libray to compute FFT for a signal sampled through the ADC.
  
  Copyright (C) 2018 Enrique Condés and Ragnar Ranøyen Homb
  Copyright (C) 2020 Bim Overbohm (template, speed improvements)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "arduinoFFT.h"
/*
These values can be changed in order to evaluate the functions
*/
#define CHANNEL A0
const uint16_t samples = 64; //This value MUST ALWAYS be a power of 2
const double samplingFrequency = 880; //Hz, must be less than 10000 due to ADC
unsigned int sampling_period_us;
unsigned long microseconds;

/*
/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samples];
double vImag[samples];

/* Create FFT object */
arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, samplingFrequency);

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03
void init_Sound_Sensor() //Sound sampling done using FFT
{
   sampling_period_us = round(1000000*(1.0/samplingFrequency));  //sampling_period_us = round(1000000*(1.0/samplingFrequency));
}
bool sound_sampling_fft()
{
   /*SAMPLING*/
  microseconds = micros();
  for(int i=0; i<samples; i++)
  {
      vReal[i] = analogRead(CHANNEL);
      vImag[i] = 0;
      while(micros() - microseconds < sampling_period_us){
        //empty loop
      }
      microseconds += sampling_period_us;
  }
  PrintVector(vReal, samples, SCL_TIME);/*  the results of the sampling according to time */
  FFT.Windowing(FFTWindow::Hamming, FFTDirection::Forward);	/* Weigh data */
  PrintVector(vReal, samples, SCL_TIME);
  FFT.Compute(FFTDirection::Forward); /* Compute FFT */
  PrintVector(vReal, samples, SCL_INDEX);
  PrintVector(vImag, samples, SCL_INDEX);
  FFT.ComplexToMagnitude(); /* Compute magnitudes */
  PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
  double x = FFT.MajorPeak();
  Serial.println(x, 6); //Print out what frequency is the most dominant.
 
  //  Detect sound is 440hz and would be acceptable +/- 2%
  if((x >= 431.2) && (x <= 448.8))    
  {
    return Serial.println("Car stops");//code for car stopping goes here
  }
  else if ((x >= 257) && (x < 267))
  {
    return Serial.println("Car moves"); // code for car moving forward goes here
  }
  else {
    return Serial.println("Car moves"); 
  }
}void setup()
{
  init_Sound_Sensor();
  
  Serial.begin(9600); 
  while(!Serial);//wait till Serial port buffer is full
}
bool sound_status;

void loop()
{
/*SAMPLING*/
  sound_status = sound_sampling_fft();
  //Serial.println(sound_status);
  while(1);
}
void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
	break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
	break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
	break;
    }
  }
}


