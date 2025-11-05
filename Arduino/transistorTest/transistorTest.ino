int pin1 = 7;
int pin2 = 8;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(pin1, OUTPUT);
pinMode(pin2, INPUT);
digitalWrite(pin1, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(pin2) == LOW){
  Serial.println("yes");
}
else{
  Serial.println("no");
}
}
