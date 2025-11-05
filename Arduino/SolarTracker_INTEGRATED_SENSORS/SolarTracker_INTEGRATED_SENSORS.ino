#include <Bonezegei_DHT11.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Servo.h>      //interfaces with the servo, frequent adjustment
#include <Stepper.h>    //interfaces with the stepper, infrequent adjustment

/*
   Pin Layout:
                                                     +-----+
                        +----[PWR]-------------------| USB |--+
                        |                            +-----+  |
                        |         GND/RST2  [ ][ ]            |
                        |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5
                        |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4
                        |                             AREF[ ] |   812 mV
                        |                              GND[ ] |
                        | [ ]N/C                    SCK/13[ ] |   stepper data
                        | [ ]IOREF                 MISO/12[ ] |   stepper data
                        | [ ]RST                   MOSI/11[ ]~|   stepper data
                        | [ ]3V3    +---+               10[ ]~|   stepper data
                        | [ ]5v    -| A |-               9[ ]~|   RELAY ON/OFF
                        | [ ]GND   -| R |-               8[ ] |   .
                        | [ ]GND   -| D |-                    |
                        | [ ]Vin   -| U |-               7[ ] |   .
                        |          -| I |-               6[ ]~|   .
          Solar cell    | [ ]A0    -| N |-               5[ ]~|   servo signal wire
  photoresistor right   | [ ]A1    -| O |-               4[ ] |   HIGH for DHT11 (VCC)
  photoresistor top     | [ ]A2     +---+           INT1/3[ ]~|   DATA for DHT11
  photoresistor left    | [ ]A3                     INT0/2[ ] |   LOW for DHT11 (GROUND)
         SDA for I2C    | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   SERIAL COMM - UNUSED
         SCL for I2C    | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   SERIAL COMM - UNUSED
                        |            [ ] [ ] [ ]              |
                        |  UNO_R3    GND MOSI 5V  ____________/
                         \_______________________/

   http://busyducks.com/ascii-art-arduinos
*/

#define DHTGND 2
#define DHTVCC 4
#define DHTDAT 3
#define D_ldr_right A1
#define D_ldr_top A2
#define D_ldr_left A3
#define relay 9
#define solar A0
int servopos = 90;
int stepperpos = 0;
float cella = 0;
float cellb = 0;
char cell;
const float analogStep = 0.79296875; //millivolts per unit measured on the analog pins, equal to  812/1024
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution for your motor
const double degreesPerStep = 0.176;

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

//param = DHT11 signal pin
Bonezegei_DHT11 dht(DHTDAT);

// initialize the stepper library on pins 8 through 11:
Stepper base_motor(stepsPerRevolution, 13, 11, 12, 10);

/*
   10 = a, 11 = b, 12 = c, 13 = d

   a b c d
   d a b c
   c d a b
   b c d a



*/

// initialize the servo library
Servo servo;

void setup() {
  pinMode(DHTVCC, OUTPUT);
  pinMode(DHTGND, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(solar, INPUT);
  digitalWrite(DHTVCC, HIGH);
  digitalWrite(DHTGND, LOW);

  Serial.begin(115200);

  dht.begin();
  bmp.begin();
  servo.attach(5);

  analogReference(EXTERNAL); // use AREF for reference voltage
}



void printEnv() {
  //__________________________________________PRINT WEATHER DATA____________________________________________________________
  if (dht.getData()) {                         // get All data from DHT11
    Serial.print("DHT TEMPERATURE=" + (String)dht.getTemperature() + "C\nDHT HUMIDITY=" + dht.getHumidity() + "%\n");
  }
  sensors_event_t event;
  bmp.getEvent(&event);
  if (event.pressure)
  {
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("BMP TEMPERATURE=" + (String)temperature + "C\nBMP PRESSURE=" + event.pressure + "hPa\n");
  }
  //__________________________________________PRINT WEATHER DATA____________________________________________________________

}

void printCell() {
  int value;
  value = analogRead(A0);
  value = (value + analogRead(A0)) / 2;
  //read every value twice and average for more accurate readings
  float voltage;
  voltage = (((float)value) * analogStep);
  Serial.print("CELL CURRENT=" + (String)voltage + "mA\n");

}

void sensor_operation() {
  int ldr_right = 0;
  int ldr_left = 0;
  int ldr_top = 0;

  float netX;
  float netY;
  int stepsY;
  base_motor.setSpeed(10);

  //read every value twice and average for more accurate readings
  ldr_right = analogRead(A1);
  ldr_right = (ldr_right + analogRead(A1)) / 2;
  ldr_top = analogRead(A2);
  ldr_top = (ldr_top + analogRead(A2)) / 2;
  ldr_left = analogRead(A3);
  ldr_left = (ldr_left + analogRead(A3)) / 2;

  float xmag = 2;//influences how sensitive the x movement is. higher means more movement.

  netX = (cos(-1 * (2 * PI) / 6) * (ldr_right * xmag)) + (cos(-3 * (2 * PI) / 6) * (ldr_left * xmag));
  netY = (((sin(1.909859) * ldr_right) + (sin(1.909859) * ldr_left)) - ldr_top);

  stepsY = netY / degreesPerStep;
  int actualsteps = -(max(-2, min(2, stepsY)));
  if (abs(stepsY) >= 75) {
    if ((stepperpos + actualsteps) > 0) {
      base_motor.step(actualsteps);
      stepperpos += actualsteps;
    }

  }

  servopos = ((servopos * .9) + ((netX + 180) * .1));
  servo.write(servopos);

}

void loop() {
  cell = "M";
  //motorized solar cell
  Serial.println("m");
  digitalWrite(relay, LOW);
  delay(1000);
  printEnv();
  printCell();
  sensor_operation();
  cell = "C";
  //control solar cell
  Serial.println("c");
  digitalWrite(relay, HIGH);
  delay(1000);
  printEnv();
  printCell();
  sensor_operation();
}
