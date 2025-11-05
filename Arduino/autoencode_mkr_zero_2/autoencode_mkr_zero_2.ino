#include "avdweb_AnalogReadFast.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    analogReadResolution(12);
    analogWriteResolution(12);
}

void loop() {
  analogWrite(A0, analogReadFast(A3));

}
