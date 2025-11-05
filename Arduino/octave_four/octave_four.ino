#include "avdweb_AnalogReadFast.h"




void setup() {
  Serial.begin(115200);
  analogReadResolution(10);
  analogWriteResolution(12);
  delay(1000);
}
#define samples 1000
#define octave -1

float first_samples[samples + abs(octave)];
float second_samples[samples + abs(octave)];
int sample_in_location;
int sample_out_location;
bool toggle;



void loop() {
  if (toggle == 0) {
    if (octave > 0) {
      for (int x = 0; x <= octave; x ++) {
        analogWrite(A0, first_samples[sample_out_location]);
        sample_out_location++;

        second_samples[sample_in_location] = analogReadFast(A3);
        sample_in_location++;
      }
      analogWrite(A0, first_samples[sample_out_location]);
      sample_out_location++;
    } else {
      for (int x = 0; x >= octave; x --) {
        second_samples[sample_in_location] = analogReadFast(A3);
        sample_in_location++;

        analogWrite(A0, first_samples[sample_out_location]);
        sample_out_location++;
      }
      second_samples[sample_in_location] = analogReadFast(A3);
      sample_in_location++;
    }
  } else {
    if (octave > 0) {
      for (int x = 0; x <= octave; x ++) {
        analogWrite(A0, second_samples[sample_out_location]);
        sample_out_location++;

        first_samples[sample_in_location] = analogReadFast(A3);
        sample_in_location++;
      }
      analogWrite(A0, second_samples[sample_out_location]);
      sample_out_location++;
    } else {
      for (int x = 0; x >= octave; x --) {
        first_samples[sample_in_location] = analogReadFast(A3);
        sample_in_location++;

        analogWrite(A0, second_samples[sample_out_location]);
        sample_out_location++;
      }
      first_samples[sample_in_location] = analogReadFast(A3);
      sample_in_location++;
    }
  }

  if (octave < 0) {
    if (sample_out_location >= samples - 1) {
      sample_in_location = 0;
      sample_out_location = 0;
      toggle = !toggle;
    }

    if (sample_in_location >= samples - 1) {
      sample_in_location = 0;
    }
  } else {
    if (sample_in_location >= samples - 1) {
      sample_in_location = 0;
      sample_out_location = 0;
      toggle = !toggle;


    }

    if (sample_out_location >= samples - 1) {
      sample_out_location = 0;
    }
  }

}
