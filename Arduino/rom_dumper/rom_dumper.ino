#include <OneWire.h>

OneWire  ds(12);    // 1-wire on pin 2
byte     addr[8];  // Contains the eeprom unique ID
void setup(void)
{
  Serial.begin(9600);
}
  
void loop(void) 
{
  byte i;
  byte dat[13];

  SearchAddress(addr);

  dat[0] = 0x01;
  dat[1] = 0x02;
  dat[2] = 0x03;
  dat[3] = 0x04;
  dat[4] = 0x05;
  dat[5] = 0x06;
  dat[6] = 0x07;
  dat[7] = 0x08;
  
  WriteRow(0,dat);
  ReadAllMem();    //print all mem content
  
  while(1);
}

void SearchAddress(byte* address) //Search for address and confirm it
{
  int i;
  if ( !ds.search(address))
  {
    Serial.print("No device found.\n");
    ds.reset_search();
    delay(250);
    return;
  }
  
  Serial.print("ADDR= ");
  for( i = 0; i < 8; i++)
  {
    Serial.print(address[i], HEX);
    Serial.print(" ");
  }

  if ( OneWire::crc8( address, 7) != address[7])
  {
      Serial.print("CRC is not valid, address is corrupted\n");
      return;
  }
  
  if ( address[0] != 0x2D) 
  {
      Serial.print("Device is not a 1-wire Eeprom.\n");
      return;
  }
  Serial.println();
}

void WriteReadScratchPad(byte TA1, byte TA2, byte* data)
{
  int i;
  ds.reset();
  ds.select(addr);
  ds.write(0x0F,1);  // Write ScratchPad
  ds.write(TA1,1); 
  ds.write(TA2,1); 
  for ( i = 0; i < 8; i++)
    ds.write(data[i],1);  
  
  ds.reset();
  ds.select(addr);    
  ds.write(0xAA);         // Read Scratchpad
  
  for ( i = 0; i < 13; i++)     
    data[i] = ds.read();
}

void CopyScratchPad(byte* data)
{
  ds.reset();
  ds.select(addr);
  ds.write(0x55,1);  // Copy ScratchPad
  ds.write(data[0],1); 
  ds.write(data[1],1);  // Send TA1 TA2 and ES for copy authorization
  ds.write(data[2],1); 
  delay(25); // Waiting for copy completion
  //Serial.print("Copy done!\n");
}

void ReadAllMem()
{
  int i;
  ds.reset();
  ds.select(addr);
  ds.write(0xF0,1);  // Read Memory
  ds.write(0x00,1);  //Read Offset 0000h
  ds.write(0x00,1);
  
  for ( i = 0; i < 512; i++) //whole mem is 144 
  {
    Serial.print(ds.read(), HEX);
    //Serial.print(" ");
  }
  Serial.println();
}

void WriteRow(byte row, byte* buffer)
{
  int i;
  if (row < 0 || row > 15) //There are 16 row of 8 bytes in the main memory
    return;                //The remaining are for the 64 bits register page
    
  WriteReadScratchPad(row*8, 0x00, buffer);
  
  /*  Print result of the ReadScratchPad
  for ( i = 0; i < 13; i++) 
  {
    Serial.print(buffer[i], HEX);
    Serial.print(" ");
  }
  */
  CopyScratchPad(buffer);
  
}
