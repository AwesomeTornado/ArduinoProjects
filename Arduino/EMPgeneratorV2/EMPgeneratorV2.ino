int t = 120000;
int i = 13;
int r = 12;
void setup() {
  // put your setup code here, to run once:
pinMode(i, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(i, HIGH);
delayMicroseconds(t);
digitalWrite(i, LOW);
delayMicroseconds(t);
digitalWrite(r, HIGH);
digitalWrite(i, HIGH);
delayMicroseconds(t);
digitalWrite(i, LOW);
delayMicroseconds(t);
digitalWrite(r, LOW);
}
