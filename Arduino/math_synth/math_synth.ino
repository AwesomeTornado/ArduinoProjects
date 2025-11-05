#include "avdweb_AnalogReadFast.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(112500);

  analogWriteResolution(12);
  analogReadResolution(10);
}

double prev_read = 0;
double curr_read = 0;
double next_read = 0;

double output = 0;

double keyframes[31];
double timings[31];
uint8_t pointer = 15;

void insert() {
  pointer--;
  timings[30] = micros() + 10000;
  keyframes[30] = curr_read;
  for (int x = 0; x < 30; x = x + 1) {
    keyframes[x] = keyframes[x + 1];
    timings[x] = timings[x + 1];
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  prev_read = curr_read;
  curr_read = next_read;
  next_read = (analogReadFast(A3) * 0.8 + curr_read* 0.2);

  if (prev_read < curr_read) {
    if (curr_read > next_read) {
      insert();
    }
  } else if (curr_read < next_read) {
    insert();
  }


  output = (output * 0.6 + keyframes[pointer] * 0.4);

  if (micros() >= timings[pointer]) {
    pointer++;
  }

  analogWrite(A0, output);
  // Serial.print(curr_read);
  // Serial.print("\t");
  // Serial.print(output);
  // Serial.print("\t");
  // Serial.println(analogReadFast(A6));
}