void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}
int i;
void loop() {
  // put your main code here, to run repeatedly:
Serial.print(g_APinDescription[i].ulPinType);
Serial.print("\t");
Serial.println(i);
delay(100);
i++;
}
