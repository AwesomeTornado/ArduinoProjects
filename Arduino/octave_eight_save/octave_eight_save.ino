#include "avdweb_AnalogReadFast.h"

uint64_t pattern;
uint64_t stream;

void setup() {
  Serial.begin(115200);
  analogReadResolution(10);
  analogWriteResolution(12);
  delay(1000);
}


#define samples 4000


short first_samples[samples];
short second_samples[samples];
short sample_in_location;
short sample_out_location;
bool toggle;
short end1;
short end2;


const uint64_t m1  = 0x5555555555555555; //binary: 0101...
const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64_t hff = 0xffffffffffffffff; //binary: all ones
const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...

//This is a naive implementation, shown for comparison,
//and to help in understanding the better functions.
//It uses 24 arithmetic operations (shift, add, and).
int BitCount(uint64_t x) {
    x = (x & m1 ) + ((x >>  1) & m1 ); //put count of each  2 bits into those  2 bits 
    x = (x & m2 ) + ((x >>  2) & m2 ); //put count of each  4 bits into those  4 bits 
    x = (x & m4 ) + ((x >>  4) & m4 ); //put count of each  8 bits into those  8 bits 
    x = (x & m8 ) + ((x >>  8) & m8 ); //put count of each 16 bits into those 16 bits 
    x = (x & m16) + ((x >> 16) & m16); //put count of each 32 bits into those 32 bits 
    x = (x & m32) + ((x >> 32) & m32); //put count of each 64 bits into those 64 bits 
    return (int)x;
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
if( sample_in_location > 1000){
    //if (BitCount(pattern ^ stream) < 3) {
    if (toggle == 0) {
      end1 = sample_in_location - 64;
    } else {
      end2 = sample_in_location - 64;
    }
    sample_in_location = 0;
    sample_out_location = 0;
    toggle = !toggle;
  //}
}
BitCount(pattern ^ stream);


  if (sample_in_location >= samples - 1) {
    sample_in_location = 0;
    sample_out_location = 0;
    toggle = !toggle;
    end1 = samples;
    end2 = samples;
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
