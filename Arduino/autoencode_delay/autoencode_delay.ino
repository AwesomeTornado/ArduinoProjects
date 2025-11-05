
short audio[2048];

int microseconds = 0;


#define sample_rate 2048

int sleep_time = 1000000/sample_rate;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(2000000);

}

void loop() {
  // put your main code here, to run repeatedly:

    /*SAMPLING*/
  for (int i = 0; i < 2047; i++)
  {
    microseconds = micros();    //Overflows after around 70 minutes!

    audio[i] = analogRead(A1)>>3;

    while (micros() < (microseconds + sleep_time)) {
    }
  }

    for (int i = 0; i < 2047; i++)
  {
    microseconds = micros();    //Overflows after around 70 minutes!
    Serial.println(audio[i]);

    analogWrite(A0, audio[i]);

    while (micros() < (microseconds + sleep_time)) {
    }
  }

}
