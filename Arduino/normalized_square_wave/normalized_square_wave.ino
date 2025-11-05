#include "MCP_DAC.h"

MCP4921 MCP;

float offset = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("starting");

  MCP.begin(10);  // select pin = 10

  delay(1000);

  offset = analogRead(1);
}

int curr_read;
int prev_read;
int send_out;

void loop() {
  // put your main code here, to run repeatedly
  prev_read = curr_read;
  curr_read = abs(analogRead(0) - offset);
  if (curr_read > prev_read) {

    if (send_out > curr_read) {
      send_out = prev_read;

    }

  } else {

    if (send_out < curr_read) {
      send_out = prev_read;

    }

  }

  MCP.fastWriteA(send_out);

}
