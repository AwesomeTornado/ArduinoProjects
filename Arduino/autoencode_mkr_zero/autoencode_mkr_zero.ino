void setup() {
  // put your setup code here, to run once:
analogWriteResolution(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  
analogWrite(A0, analogRead(A3) >> 1);
}
