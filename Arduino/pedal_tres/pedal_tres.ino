#include "MCP_DAC.h"

MCP4921 MCP;

int tangent[3] = {};


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("starting");

  MCP.begin(10);  // select pin = 10
}

void loop() {
  // put your main code here, to run repeatedly
  tangent[0] = analogRead(0) >> 2;
   tangent[1] = analogRead(0) >> 2;

  if (tangent[0] < tangent[1]) {
    MCP.fastWriteA(4095);
  }

  if (tangent[0] > tangent[1]) {
    MCP.fastWriteA(0);
  }
}
