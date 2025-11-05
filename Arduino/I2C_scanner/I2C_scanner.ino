// SPDX-FileCopyrightText: 2023 Carter Nelson for Adafruit Industries
//
// SPDX-License-Identifier: MIT
// --------------------------------------
// i2c_scanner
//
// Modified from https://playground.arduino.cc/Main/I2cScanner/
// --------------------------------------

#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire

void setup() {
  WIRE.begin();

  Serial.begin(9600);
  while (!Serial)
     delay(100);
  Serial.println("\nI2C Scanner");
}
void print_address(uint8_t address){
  if (address<16)
        Serial.print("0");
  Serial.print(address,HEX);
}

void loop() {
  uint8_t error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      print_address(address);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      print_address(address);
    }
    else if(error!=2){
      Serial.print("Unexpected error code at address 0x");
      print_address(address);
      Serial.print("\n\t\tError code is as follows:\t");
      Serial.println(error);
    }/*
    else{
      print_address(address);
    }*/
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}
