void setup() {
  // put your setup code here, to run once:
  Serial.begin(112500);
}
int prev_read = 0;
int curr_read = 0;
int wave_out = 0;

void loop() {
  // put your main code here, to run repeatedly:
  curr_read = (analogRead(A1) << 3) >> 2;
  if (curr_read < prev_read) {
    wave_out--;
  } else if (curr_read > prev_read) {
    wave_out++;
  } else {
    wave_out = wave_out/1.1;
  }
  prev_read = curr_read;
  //Serial.println(wave_out);
  analogWrite(A0, ((wave_out+100)<<3)>>3);
}
