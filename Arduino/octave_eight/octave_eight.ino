#include "avdweb_AnalogReadFast.h"

uint64_t pattern;
uint64_t stream;

void setup() {
  Serial.begin(115200);
  analogReadResolution(10);
  analogWriteResolution(12);
  delay(1000);
}


#define samples 1000


short first_samples[samples];
short second_samples[samples];
short sample_in_location;
short sample_out_location;
bool toggle;
short end1;
short end2;



int BitCount(uint64_t u)
{
  uint64_t uCount;

  uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
  return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}

void update_pattern1() {
  pattern = pattern << 1;

  if (first_samples[sample_in_location - 1] < first_samples[sample_in_location]) {

    pattern++;

  }
}

void update_pattern2() {
  pattern = pattern << 1;

  if (second_samples[sample_in_location - 1] < second_samples[sample_in_location]) {

    pattern++;

  }
}

void update_stream1() {
  stream = stream << 1;

  if (first_samples[sample_in_location - 1] < first_samples[sample_in_location]) {

    stream++;

  }
}

void update_stream2() {
  stream = stream << 1;

  if (second_samples[sample_in_location - 1] < second_samples[sample_in_location]) {

    stream++;

  }
}

void loop() {
  if (toggle == 0) {
    analogWrite(A0, first_samples[sample_out_location]);
    sample_out_location++;

    second_samples[sample_in_location] = analogReadFast(A3);
    sample_in_location++;

    if (sample_in_location < 64) {
      update_pattern2();
    } else {
      update_stream2();
    }

    analogWrite(A0, first_samples[sample_out_location]);
    sample_out_location++;

  } else {
    analogWrite(A0, second_samples[sample_out_location]);
    sample_out_location++;

    first_samples[sample_in_location] = analogReadFast(A3);
    sample_in_location++;

    if (sample_in_location < 64) {
      update_pattern1();
    } else {
      update_stream1();
    }

    analogWrite(A0, second_samples[sample_out_location]);
    sample_out_location++;

  }

  //Serial.println(BitCount((pattern ^ stream)));

  if (BitCount(pattern ^ stream) < 1) {
    if (toggle == 0) {
      end1 = sample_in_location - 64;
    } else {
      end2 = sample_in_location - 64;
    }
    //sample_in_location = 0;
    //sample_out_location = 0;
    //toggle = !toggle;
  }

  if (sample_in_location >= samples - 1) {
    sample_in_location = 0;
    sample_out_location = 0;
    toggle = !toggle;
  }

  if (toggle == 0) {

    if (sample_out_location >= end2) {
      sample_out_location = 0;
    }

  } else {

    if (sample_out_location >= end1) {
      sample_out_location = 0;
    }

  }



}
