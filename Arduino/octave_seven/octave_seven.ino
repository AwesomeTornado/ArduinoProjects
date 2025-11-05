#include "avdweb_AnalogReadFast.h"

#define write_resolution 12
#define read_resolution 10

#define samples 1000


short buff_1[samples];
short buff_2[samples];
short buff_3[samples];

short x;

short read_location;
short write_location;


void setup() {
  Serial.begin(115200);
  analogReadResolution(read_resolution);
  analogWriteResolution(write_resolution);
  delay(1000);
}

void loop() {
  if (x == 0) {
    analogWrite(A0, (buff_2[write_location] + buff_3[write_location] + buff_2[samples - write_location] + buff_3[samples - write_location]) / 4);
    write_location++;

    buff_1[read_location] = analogReadFast(A3);
    read_location++;

    analogWrite(A0, (buff_2[write_location] + buff_3[write_location] + buff_2[samples - write_location] + buff_3[samples - write_location]) / 4);
    write_location++;

  } else if (x == 1) {
    analogWrite(A0, (buff_3[write_location] + buff_3[samples - write_location]) / 2);
    write_location++;

    buff_1[read_location] = analogReadFast(A3);
    read_location++;

    analogWrite(A0, (buff_3[write_location] + buff_3[samples - write_location]) / 2);
    write_location++;

  } else if (x == 2) {
    analogWrite(A0, (buff_1[write_location] + buff_3[write_location] + buff_1[samples - write_location] + buff_3[samples - write_location]) / 4);
    write_location++;

    buff_2[read_location] = analogReadFast(A3);
    read_location++;

    analogWrite(A0, (buff_1[write_location] + buff_3[write_location] + buff_1[samples - write_location] + buff_3[samples - write_location]) / 4);
    write_location++;

  } else if (x == 3) {
    analogWrite(A0, (buff_1[write_location] + buff_1[samples - write_location]) / 2);
    write_location++;

    buff_2[read_location] = analogReadFast(A3);
    read_location++;

    analogWrite(A0, (buff_1[write_location] + buff_1[samples - write_location]) / 2);
    write_location++;

  } else if (x == 4) {
    analogWrite(A0, (buff_2[write_location] + buff_1[write_location] + buff_2[samples - write_location] + buff_1[samples - write_location]) / 4);
    write_location++;

    buff_3[read_location] = analogReadFast(A3);
    read_location++;

    analogWrite(A0, (buff_2[write_location] + buff_1[write_location] + buff_2[samples - write_location] + buff_1[samples - write_location]) / 4);
    write_location++;

  } else if (x == 5) {
    analogWrite(A0, (buff_2[write_location] + buff_2[samples - write_location]) / 2);
    write_location++;

    buff_3[read_location] = analogReadFast(A3);
    read_location++;

    analogWrite(A0, (buff_2[write_location] + buff_2[samples - write_location]) / 2);
    write_location++;

  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }


  if (write_location >= samples) {
    if (x == 5) {
      x = 0;
    } else {
      x++;
    }
    write_location = 0;
  }
  if (read_location >= samples) {

    read_location = 0;

  }


}
