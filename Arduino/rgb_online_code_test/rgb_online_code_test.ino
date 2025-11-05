#include <ColorConverterLib.h>
ColorConverter CConvert;
//#include "ColorConverter.h"

#include <FastLED.h>
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define RGB_PIN           6              // LED DATA PIN
#define RGB_LED_NUM    300            // 10 LEDs [0...9]
#define BRIGHTNESS       255
// brightness range [0..255]
#define CHIP_SET       WS2812B      // types of RGB LEDs
#define COLOR_CODE    GRB          //sequence of colors in data stream
#define scalar        0.05 //speed of hsl change
double d_a;
double d_b;
double d_c;

enum buttons {
  b_0_0 = 66, //7
  b_0_1 = 82, //8
  b_0_2 = 74, //9
  b_1_0 = 8,  //4
  b_1_1 = 28, //5
  b_1_2 = 90, //6
  b_2_0 = 12, //1
  b_2_1 = 24, //2
  b_2_2 = 94, //3
  b_3_0 = 22, //0
  b_3_1 = 25, //EQ
  b_3_2 = 13, //st/rept
  b_4_0 = 7,  // down
  b_4_1 = 21, //vol-
  b_4_2 = 9,  // up
  b_5_0 = 68, // <<
  b_5_1 = 64, //play/pause
  b_5_2 = 67, // >>
  b_6_0 = 69, //pwr
  b_6_1 = 70, //vol+
  b_6_2 = 71,  //func/stop
  seven = 66, //7
  eight = 82, //8
  nine = 74, //9
  four = 8,  //4
  five = 28, //5
  six = 90, //6
  one = 12, //1
  two = 24, //2
  three = 94, //3
  zero = 22, //0
  EQ = 25, //EQ
  ST_REPT = 13, //st/rept
  down = 7,  // \/
  vol_down = 21, //vol-
  up = 9,  // /\\
  prev = 68, // <<
  play_pause = 64, //play/pause
  next = 67, // >>
  power = 69, //pwr
  vol_up = 70, //vol+
  func_stop = 71  //func/stop
};

// Define the array of LEDs
CRGB LEDs[RGB_LED_NUM];

// define 3 byte for the random color
uint8_t  a, b, c;
#define UPDATES_PER_SECOND 100

int IRinput = 0;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(11, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.println("WS2812B LEDs strip Initialize");
  Serial.println("Please enter the 1 to 6 value.....Otherwise no any effect show");
  FastLED.addLeds<CHIP_SET, RGB_PIN, COLOR_CODE>(LEDs, RGB_LED_NUM);
  randomSeed(analogRead(0));
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();

}

void loop() {
  if (IrReceiver.decode()) {
    // read the incoming byte:

    IRinput = IrReceiver.decodedIRData.command;
    Serial.println(IRinput);
    switch (IRinput) {
      case buttons::b_6_0: Toggle_RED_LED();
        Serial.println("1.Toggle LED Complete");
        break;
      case buttons::b_6_1: Scrolling_RED_LED();
        Serial.println("2.Scrolling RED LED Complete");
        break;
      case buttons::b_6_2: O_W_G_scroll();
        Serial.println("3.Flag Show Complete");
        break;
      case buttons::b_5_0:  Rotate_color();
        Serial.println("4.Rotate color Complete");
        break;
      case buttons::b_5_1:  r_g_b();
        Serial.println("5.R_G_B color Complete");
        break;
      case buttons::b_5_2: random_color();
        Serial.println("6.Random color Show Complete");
        break;
      case buttons::one: hue_increace();
        break;
      case buttons::two: saturation_increace();
        break;
      case buttons::three: lightness_increace();
        break;
      case buttons::four: hue_reset();
        break;
      case buttons::five: saturation_reset();
        break;
      case buttons::six: lightness_reset();
        break;
      case buttons::seven: hue_decreace();
        break;
      case buttons::eight: saturation_decreace();
        break;
      case buttons::nine: lightness_decreace();
    }
    IrReceiver.resume(); // Enable receiving of the next value
  }
}
// RED LED TOGGLE
void Toggle_RED_LED(void) {
  // Red Green Blue
  for (int i = 0; i < RGB_LED_NUM; i++)
    LEDs[i] = CRGB(255, 0, 0 );
  FastLED.show();
  delay(1000);
  for (int i = 0; i < RGB_LED_NUM; i++)
    LEDs[i] = CRGB(0, 0, 0 );
  FastLED.show();
  delay(1000);

}
// Move the Red LED
void Scrolling_RED_LED(void)
{
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB::Red;
    FastLED.show();
    delay((400 / RGB_LED_NUM));
    LEDs[i] = CRGB::Black;
    FastLED.show();
    delay((100 / RGB_LED_NUM));

  }
}
// Orange/White/Green color green
void O_W_G_scroll() {
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB::Orange;
    delay(50 / RGB_LED_NUM);
    FastLED.show();
  }
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB::Black;
    delay(50 / RGB_LED_NUM);
    FastLED.show();
  }
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB::White;
    delay(50 / RGB_LED_NUM);
    FastLED.show();
  }
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB::Black;
    delay(50 / RGB_LED_NUM);
    FastLED.show();
  }
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB::Green;
    delay(50 / RGB_LED_NUM);
    FastLED.show();
  }
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB::Black;
    delay(50 / RGB_LED_NUM);
    FastLED.show();
  }
}
// Red/Green/Blue color Rotate
void Rotate_color(void) {
  for (int clr = 0; clr < RGB_LED_NUM; clr++) {
    LEDs[clr]     = CRGB::Red;
    LEDs[clr + 1] = CRGB::Green;
    LEDs[clr + 2] = CRGB::Blue;
    FastLED.show();
    delay(100 / RGB_LED_NUM);
    for (int clr = 0; clr < RGB_LED_NUM; clr++) {
      LEDs[clr] = CRGB::Black;
      delay(5 / RGB_LED_NUM);
    }
  }
}
// Blue, Green , Red
void r_g_b() {
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB ( 0, 0, 255);
    FastLED.show();
    delay(50 / RGB_LED_NUM);
  }
  for (int i = RGB_LED_NUM; i >= 0; i--) {
    LEDs[i] = CRGB ( 0, 255, 0);
    FastLED.show();
    delay(50 / RGB_LED_NUM);
  }
  for (int i = 0; i < RGB_LED_NUM; i++) {
    LEDs[i] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(50 / RGB_LED_NUM);
  }
  for (int i = RGB_LED_NUM; i >= 0; i--) {
    LEDs[i] = CRGB ( 0, 0, 0);
    FastLED.show();
    delay(50 / RGB_LED_NUM);
  }
}
// random color show
void random_color(void) {
  // loop over the NUM_LEDS
  for (int i = 0; i < RGB_LED_NUM; i++) {
    // choose random value for the r/g/b
    a = random(0, 255);
    b = random(0, 255);
    c = random(0, 255);
    // Set the value to the led
    LEDs[i] = CRGB (a, b, c);
    // set the colors set into the physical LED
    FastLED.show();

    // delay 50 millis
    FastLED.delay(200 / RGB_LED_NUM);
  }
}
void hue_increace() {

  d_a = d_a + scalar;
    reset_overflow();
  CConvert.HsvToRgb(d_a, d_b, d_c, a, b, c);
  for (int i = 0; i < RGB_LED_NUM; i++) {
    // Set the value to the led
    LEDs[i] = CRGB (a, b, c);

  }
  // set the colors set into the physical LED
  FastLED.show();
}
void saturation_increace() {
  d_b = d_b + scalar;
    reset_overflow();
  CConvert.HsvToRgb(d_a, d_b, d_c, a, b, c);
  for (int i = 0; i < RGB_LED_NUM; i++) {
    // Set the value to the led
    LEDs[i] = CRGB (a, b, c);
  }
  // set the colors set into the physical LED
  FastLED.show();
}
void lightness_increace() {

  d_c = d_c + scalar;
    reset_overflow();
  CConvert.HsvToRgb(d_a, d_b, d_c, a, b, c);
  for (int i = 0; i < RGB_LED_NUM; i++) {
    // Set the value to the led
    LEDs[i] = CRGB (a, b, c);

  }
  // set the colors set into the physical LED
  FastLED.show();
}
void hue_reset() {

}
void saturation_reset() {

}
void lightness_reset() {

}
void hue_decreace() {

  d_a = d_a - scalar;
    reset_overflow();
  CConvert.HsvToRgb(d_a, d_b, d_c, a, b, c);
  for (int i = 0; i < RGB_LED_NUM; i++) {
    // Set the value to the led
    LEDs[i] = CRGB (a, b, c);

  }
  // set the colors set into the physical LED
  FastLED.show();
}
void saturation_decreace() {

  d_b = d_b - scalar;
    reset_overflow();
  CConvert.HsvToRgb(d_a, d_b, d_c, a, b, c);
  for (int i = 0; i < RGB_LED_NUM; i++) {
    // Set the value to the led
    LEDs[i] = CRGB (a, b, c);

  }
  // set the colors set into the physical LED
  FastLED.show();
}
void lightness_decreace() {
  d_c = d_c - scalar;
    reset_overflow();
  CConvert.HsvToRgb(d_a, d_b, d_c, a, b, c);
  for (int i = 0; i < RGB_LED_NUM; i++) {
    // Set the value to the led
    LEDs[i] = CRGB (a, b, c);

  }
  // set the colors set into the physical LED
  FastLED.show();
}
void reset_overflow() {
  if (d_a > 1) {
    d_a = 0;
  }
  if (d_b > 1) {
    d_b = 1;
  }
  if (d_c > 1) {
    d_c = 1;
  }
    if (d_a < 0) {
    d_a = 1;
  }
  if (d_b < 0) {
    d_b = 0;
  }
  if (d_c < 0) {
    d_c = 0;
  }
}
