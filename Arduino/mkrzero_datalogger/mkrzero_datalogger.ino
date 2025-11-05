#include <SPI.h>
#include <SD.h>

const int chipSelect = SDCARD_SS_PIN;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1)
      ;
  }
  Serial.println("card initialized.");
}

void loop() {
  File firstFile = SD.open("DATA.txt", FILE_WRITE);
  firstFile.println("\nTHIS IS THE FIRST ENTRY OF MANY. GODSPEED, AND MAY THE LUCK BE EVER IN YOUR FAVOR\n");
  firstFile.close();
  while (true) {
    File dataFile = SD.open("DATA.txt", FILE_WRITE);

    String dataString = "";
    while (Serial1.available() == 0) {delay(300);}     //wait for data available
    dataString += Serial1.readString();

    // if the file is available, write to it:
    if (dataFile) {
      dataFile.print(dataString);
      // print to the serial port too:
      Serial.println(dataString);
      dataFile.close();
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening DATA.txt");
    }
  }
}