#include <Arduino.h>
#include <SimpleEncoder.h>


#define clk 8
#define dt 13
#define sw 4
#define g 9
#define r 5
#define b 11

const float rad_offset = (2*PI)/3; 

SimpleEncoder encoder(sw, clk, dt, -5, 0, 365);

const uint8_t HSVlights[61] = 
{0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51, 55, 59, 64, 68, 72, 76,
81, 85, 89, 93, 98, 102, 106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208,
212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255};

void trueHSV(int angle)
{
  byte red, green, blue;

  if (angle<60) {red = 255; green = HSVlights[angle]; blue = 0;} else
  if (angle<120) {red = HSVlights[120-angle]; green = 255; blue = 0;} else 
  if (angle<180) {red = 0, green = 255; blue = HSVlights[angle-120];} else 
  if (angle<240) {red = 0, green = HSVlights[240-angle]; blue = 255;} else 
  if (angle<300) {red = HSVlights[angle-240], green = 0; blue = 255;} else 
                 {red = 255, green = 0; blue = HSVlights[360-angle];} 
  analogWrite(r, red);
  analogWrite(g, green);
  analogWrite(b, blue);
}

void setup() {
    Serial.begin(9600);
    
}

void loop() {
    if (encoder.CLOCKWISE) {
        Serial.println("Encoder moving clockwise " + String(encoder.VALUE));
        if(encoder.VALUE <= -1){
          encoder.setValue(360);
        }
        trueHSV(encoder.VALUE);
    }
    if (encoder.COUNTERCLOCKWISE) {
        Serial.println("Encoder moving counter clockwise " + String(encoder.VALUE));
        if(encoder.VALUE >= 361){
          encoder.setValue(0);
        }
        trueHSV(encoder.VALUE);
    }
    if (encoder.BUTTON_PRESSED) {
        Serial.println("Button Pressed");
    }
}
