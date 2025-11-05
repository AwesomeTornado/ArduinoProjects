#include <arduinoFFT.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
pinMode(9, OUTPUT);

analogWrite(9, 128);

delay(1000);
Serial.println("init");
  arduinoFFT transform = arduinoFFT(5, 10, 1000, 1000);
Serial.println(transform.Revision());
Serial.println(transform.Compute(9));
}

void loop() {
  // put your main code here, to run repeatedly:

}
