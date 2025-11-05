

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
  delay(10000);
  Serial.println("starstinaoinrto");
}
int i = 25;
void loop() {
Serial.println(i); 

analogRead(i);

i = i +1;
}
