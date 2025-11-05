void setup() {
  // put your setup code here, to run once:
pinMode(0, OUTPUT);    // sets the digital pin 13 as output
pinMode(1, OUTPUT);    // sets the digital pin 13 as output
pinMode(2, OUTPUT);    // sets the digital pin 13 as output
pinMode(3, OUTPUT);    // sets the digital pin 13 as output
pinMode(4, OUTPUT);    // sets the digital pin 13 as output
pinMode(5, OUTPUT);    // sets the digital pin 13 as output
pinMode(6, OUTPUT);    // sets the digital pin 13 as output
pinMode(7, OUTPUT);    // sets the digital pin 13 as output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  delay(1000);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(1000);

}
