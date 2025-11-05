#include "MCP_DAC.h"

MCP4921 MCP;

float offset = 0;

bool toggle;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("starting");

  MCP.begin(10);  // select pin = 10

  delay(1000);

  offset = analogRead(1);

  delay(500);
  if (digitalRead(2) == HIGH) {
    while (true) {
      MCP.fastWriteA((analogRead(0) * toggle) + (offset * !toggle));
      toggle = !toggle;
    }
  } else {
    while (true) {
      MCP.fastWriteA(abs(analogRead(0) - offset));
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly
}
