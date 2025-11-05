//code to measure the voltage and current at the same time.
//0.31 A
//0.61 V
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void allOpenDrain(){
  pinMode(A0,INPUT);
  pinMode(2, INPUT);
}

float readOpenVoltage(){
  allOpenDrain();
  delay(5);//allow some time for physics to happen
  return (float)(analogRead(A0) * (5.0 / 1023.0));
}

float readShortCurrent(){
  allOpenDrain();
  digitalWrite(2, LOW);
  pinMode(2, OUTPUT);
  delay(5);//allow some time for physics to happen
  float voltage = (analogRead(A0) * (5.0 / 1023.0));
  return (float)(voltage/0.17);
//six parallel one omh resistors per solar panel, 0.17 ohms
  allOpenDrain();
}

void loop() {
  Serial.print(readShortCurrent());
  Serial.print(",");
  Serial.print(readOpenVoltage());
  Serial.print("\n");
  delay(20);
}
