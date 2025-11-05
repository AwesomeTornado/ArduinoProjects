#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT();


#define samples 512             //Must be a power of 2
#define sample_rate 1024

#define frequencys 12

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[samples];
double vImag[samples];

float tones[frequencys] = {};
float values[frequencys] = {};

float temp_mag = 0;

long int filter = 5000;

void fastComplexToMagnitude() {
  for (uint16_t i = 0; i < samples; i++) {
    vReal[i] = sq(vReal[i]) + sq(vImag[i]);
  }
}

void MagnitudeSort() {
  for (int r = 0; r < frequencys; r++) {
    tones[r] = 0;
    values[r] = 0;
  }
  for (uint16_t i = 0; i < samples / 2; i++) { //for every bucket
    if (vReal[i] > filter) {//if the tone is loud enough
      if (vReal[i] > values[0]) {//if the tone is greater than the quitest tone so far
        magsortRECURSE(i);
      }
    }
  }
}

void magsortRECURSE(int i) {
  for (int t = 1; t < frequencys; t = t + 1) {//for every tone louder than the quietest tone
    if (vReal[i] < values[t]) {//if the bucket is quieter
      double delta = 0.5 * ((vReal[i - 1] - vReal[i + 1]) / (vReal[i - 1] - (2.0 * vReal[i]) + vReal[i + 1]));//calculate the offset from the bin
      double interpolatedX = ((i + delta)  * sample_rate) / (samples - 1);//calculate the frequency
      if (interpolatedX > 60) {//freq filter
        for (int l = 0; l < t - 1; l++) { // for all values quieter than the bucket

          tones[l] = tones[l + 1]; //shift them to the left
          values[l] = values[l + 1]; //shift them to the left

        }

        tones[t - 1] = interpolatedX;
        values[t - 1] = vReal[i];

        return;
      }
      return;

    }
  }
  double delta = 0.5 * ((vReal[i - 1] - vReal[i + 1]) / (vReal[i - 1] - (2.0 * vReal[i]) + vReal[i + 1]));//calculate the offset from the bin
  double interpolatedX = ((i + delta)  * sample_rate) / (samples - 1);//calculate the frequency
  if (interpolatedX > 60) {//freq filter
    for (int l = 0; l < frequencys-1; l++) { // for all values quieter than the bucket

      tones[l] = tones[l + 1]; //shift them to the left
      values[l] = values[l + 1]; //shift them to the left

    }

    tones[frequencys-1] = interpolatedX;
    values[frequencys-1] = vReal[i];
  }
}



float freq_calc = sample_rate / samples;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(2000000);
  delay(1000);
  Serial.print("starting");

  sampling_period_us = round(1000000 * (1.0 / sample_rate));

}

void loop() {

  /*SAMPLING*/
  for (int i = 0; i < samples; i++)
  {
    microseconds = micros();    //Overflows after around 70 minutes!

    vReal[i] = analogRead(A1);
    vImag[i] = 0;

    while (micros() < (microseconds + sampling_period_us)) {
    }
  }


  FFT.DCRemoval(vReal, samples);
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
  fastComplexToMagnitude();
  MagnitudeSort();

  for (int i = 0; i < frequencys; i++) {
    Serial.print(tones[i]);
    Serial.print("\t");
  }
  Serial.print("\n");
}
