#include "arduinoFFT.h"
  
#define SAMPLES 64               //Must be a power of 2
#define SAMPLING_FREQUENCY 10  //Hz
#define REFRESH_RATE 6          //Hz
#define ARDUINO_IDE_PLOTTER_SIZE 500
  
arduinoFFT FFT = arduinoFFT();
  
unsigned long sampling_period_us;
unsigned long useconds_sampling;
 
unsigned long refresh_period_us;
unsigned long useconds_refresh;
  
double vReal[SAMPLES];
double vImag[SAMPLES];
double vData[SAMPLES];

double temp;
 
uint8_t analogpin = A3;
  
void setup() {
  Serial.begin(2000000);
 
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
  refresh_period_us = round(1000000*(1.0/REFRESH_RATE));
 
  pinMode(analogpin, INPUT);
}
  
void loop() {
  useconds_refresh = micros();
   
  /*SAMPLING*/
  for(int i=0; i<SAMPLES; i++)
  {

    if(i+2 < SAMPLES){
        vReal[i] = vData[i+1];
        vData[i] = vData[i+1];
    }else{
      vData[i] = analogRead(analogpin);

    }
        vImag[i] = 0;
  }  
 
  /*FFT*/ 
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
 
  /*PRINT RESULTS*/
  for(int i=6; i<(SAMPLES/2); i++){
    Serial.println(vReal[i], 1);

Serial.println(vReal[i]);

  }
   
  while(micros() < (useconds_refresh + refresh_period_us)){
    //wait...
  }
}
