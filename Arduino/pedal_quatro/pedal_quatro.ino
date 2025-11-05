#include "MCP_DAC.h"

MCP4921 MCP;

float offset = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("starting");

  MCP.begin(10);  // select pin = 10

  offset = analogRead(1);
}

void loop() {
  // put your main code here, to run repeatedly

    MCP.fastWriteA(abs(analogRead(0)-offset));

}
