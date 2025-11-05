//this code is not finished. currently it has complete code for sensor based operation
//and math to find the sun without sensors (no motor movement)

//this has not been properly tested, and will likely need to be revised


#include <EEPROM.h>     //used to save information about geographic location and preferences
#include <Servo.h>      //interfaces with the servo, frequent adjustment
#include <Stepper.h>    //interfaces with the stepper, infrequent adjustment
#include <SunPosition.h>//gets the position of the sun, dumbass

#define SKIP_CONF 12   //pin 12 toggles configuration, when pulled high, config is not required
#define MODE_ADDR 0    //memory address in eeprom that contains the tracking mode
#define TIME_ADDR 9   //memory address in eeprom that contains the time
#define LOCATION_ADDR 1//memory address in eeprom that contains location struct
#define SPEED (480000)  //multiplier for how fast time moves. ignore this, as it is used for debugging.

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

const double degreesPerStep = 0.176;

// initialize the stepper library on pins 8 through 11:
Stepper base_motor(stepsPerRevolution, 8, 10, 9, 11);

// initialize the servo library
Servo servo;

struct location {
  float Latitude;
  float Longitude;
};

struct sunLocation {
  float Altitude;
  float Azimuth;
  float Declination;
};

double epoch;
location Location;
bool mode;

bool char2bool(char in) {
  switch (in) {
    case '1':
      return false;
      break;
    case '2':
      return true;
      break;
    default:
      return false;
      break;
  }
}

void printLocation(location x) {
  Serial.print("\nLocation:\n\tLatitude: ");
  Serial.print(x.Latitude);
  Serial.print("\n\tLongitude: ");
  Serial.println(x.Longitude);
}
void graphLocation(location x) {
  Serial.print("Latitude:");
  Serial.print(x.Latitude);
  Serial.print(",");
  Serial.print("Longitude:");
  Serial.println(x.Longitude);
}
void printSunLocation(sunLocation x) {
  Serial.print("\nLocation:\n\tAltitude: ");
  Serial.print(x.Altitude);
  Serial.print("\n\tAzimuth: ");
  Serial.print(x.Azimuth);
  Serial.print("\n\tDeclination: ");
  Serial.println(x.Declination);
}
void graphSunLocation(sunLocation x) {
  Serial.print("Altitude:");
  Serial.print(x.Altitude);
  Serial.print(" ");
  Serial.print("Azimuth:");
  Serial.print(x.Azimuth);
  Serial.print(" ");
  Serial.print("Declination:");
  Serial.println(x.Declination);
}

void inputDelay() {
  while (Serial.available() < 1) {
    delay(100);
  }
}

void configuration() {//set up eeprom
  Serial.println("Settings:\n1 : Mode\n2 : Location\n3 : Time and Date");
  inputDelay();
  switch (Serial.read()) {
    case '1':
      {
        Serial.println("\nSettings:Mode\n\t1 : Sensor based\n\t2 : Math based");
        inputDelay();
        EEPROM.write(MODE_ADDR, char2bool(Serial.read()));
        break;
      }
    case '2':
      {
        Serial.println("\nSettings:Location\n\tLatitude:");
        inputDelay();
        double in_latitude = Serial.parseFloat();
        Serial.println("\nSettings:Location\n\tLongitude:");
        inputDelay();
        double in_longitude = Serial.parseFloat();
        location this_location;
        this_location.Latitude = in_latitude;
        this_location.Longitude = in_longitude;
        EEPROM.put(LOCATION_ADDR, this_location);
        break;
      }
    case '3':
      {
        Serial.println("\nSettings:Date and Time\n\tSeconds past the epoch:");
        inputDelay();
        EEPROM.put(TIME_ADDR, Serial.parseFloat());
        break;
      }
    default:
      Serial.println("\n\nInvalid Option\n\n");
      break;
  }
}

void initVars() {
  mode = EEPROM.read(MODE_ADDR);
  EEPROM.get(LOCATION_ADDR, Location);
  EEPROM.get(TIME_ADDR, epoch);

  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//clear screen
  Serial.print("Settings:\n\tMode: ");
  Serial.print(mode);
  Serial.print("\n\tLocation:\n\t\tLatitude: ");
  Serial.print(Location.Latitude);
  Serial.print("\n\t\tLongitude: ");
  Serial.print(Location.Longitude);
  Serial.print("\n\tTime: ");
  Serial.print(epoch);
  Serial.println("\nFinished initalizing vars.\n");
}

void initVarsQuiet() {
  mode = EEPROM.read(MODE_ADDR);
  EEPROM.get(LOCATION_ADDR, Location);
  EEPROM.get(TIME_ADDR, epoch);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (digitalRead(SKIP_CONF) == LOW) { //check if the skip configuration jumper is turned on
    while (!Serial) {
      // wait for serial port to connect. Needed for native USB
    }
    Serial.println("Serial initalized");
    configuration();  //get config data from user
    delay(100);
  }
  initVarsQuiet();
  servo.attach(7);
}


double getTime() {
  return (((micros() / 100000) * SPEED) + epoch);
}

void math_operation() {
  Serial.println("math operation started");
  // great visualization on how this math works,
  //https://sciencepickle.com/earth-systems/sun-earth-connection/declination-circles/solar-time-angle-and-direction/
  sunLocation sunPos;
  //initialize sun position library
  SunPosition sunCalc(55.75, 37.62, getTime());
  float current_rotation = 0; 
  int stepsX = 0;
  base_motor.setSpeed(3);
  while (true) {
    sunCalc.compute(55.75, 37.62, getTime());
    sunPos.Altitude = sunCalc.altitude();
    sunPos.Azimuth = sunCalc.azimuth();
    sunPos.Declination = sunCalc.declination();
    graphSunLocation(sunPos);
    //servo.write(sunPos.Azimuth);
    stepsX = (sunPos.Declination - current_rotation) / degreesPerStep;
    current_rotation = current_rotation + (stepsX * degreesPerStep);
    base_motor.step(stepsX);
    Serial.println(stepsX);
  }
}


/*    v=== sensor 1
   +  0       0 <=== sensor 0
   /\  \     /
   |    \   /
   |      X
   Y      |
   |      |
   |      0  <=== sensor 2
   V
   -
   - <=== X ===> +
*/

void sensor_operation() {
  float value_0;
  float value_1;
  float value_2;

  float netX;
  float netY;
  int stepsY;
  base_motor.setSpeed(10);
  while (true) {
    value_0 = analogRead(A0);
    value_1 = analogRead(A1);
    value_2 = analogRead(A2);

    netX = (cos(1.909859) * value_0) - (cos(1.909859) * value_1);
    netY = ((sin(1.909859) * value_0) + (sin(1.909859) * value_1)) - value_2;
    

    stepsY = netY / degreesPerStep;
    if(abs(stepsY) >= 100){
      base_motor.step(-(max(-2,min(2,stepsY))));
    }
    

    servo.write(netX + 90);
  Serial.print("x:");
  Serial.print(netX);
  Serial.print(" ");
  Serial.print("y:");
  Serial.println(netY);
  delay(1000);
  }
}


void loop() {
  if (mode == 0) {
    sensor_operation();
  }
  math_operation();
}
