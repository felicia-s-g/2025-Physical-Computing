// LIBRARIES
#include <Adafruit_Thermal.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_VL53L0X.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <ESP32Servo.h>
#include <Wire.h>

// VARIABLES

// Buttons
bool btn_left_val = false;
bool old_btn_left_val = false;
int btn_left_pin = 11;
int btn_left_status = 0;  // 0: OFF, 1: RISING EDGE, 2: ON; 3: FALLING EDGE
int old_btn_left_status = -1;

bool btn_right_val = false;
bool old_btn_right_val = false;
int btn_right_pin = 12;
int btn_right_status = 0;
int old_btn_right_status = -1;

// Counter
int count_left = 0;
int count_right = 0;

// Servo motor
Servo servo;

bool eyeOpenStatus = false;

// Cases
enum { INIT,
       READY,
       LEFT,
       RIGHT,
       BOTH,
       STANDBY,
       QUOTE,
       OFF } state = INIT;
int randNumber;

// For the QUOTE case (motivational message print)
long quote_interval = 60 * 1000 * 3;
long last_quote_time = 0;

// NeoPixel strips
#define LED_PIN_1 6
#define LED_COUNT_1 24

#define LED_PIN_2 9
#define LED_COUNT_2 24

Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);

// Proximity sensor
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;
int distance = 0;

// Printer
Adafruit_Thermal printer(&Serial0);
String message;

void setup() {

  Serial.begin(9600);
  Serial0.begin(9600);

  randomSeed(analogRead(0));

  // Buttons
  pinMode(btn_left_pin, INPUT);
  pinMode(btn_right_pin, INPUT);

  strip1.begin();
  strip1.show();
  strip1.setBrightness(50);
  strip2.begin();
  strip2.show();
  strip2.setBrightness(50);

  // Servo motor
  servo.attach(9);
  eyeOpenStatus = true;
  eyeClose();

  // Proximity sensor
  while (!Serial) {
    delay(1);
  }
  Serial.println("Adafruit VL53L0X test.");

  if (!lox.begin(0x29)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));
  lox.startRangeContinuous();

  // Printer
  printer.begin();
  printer.setFont('A'); 
  printer.boldOn();
  printer.setSize('M'); 
  printer.justify('C');
  printer.feed(4);

  printer.sleep();  // Tell printer to sleep
  delay(3000L);     // Sleep for 3 seconds
  printer.wake();   // MUST wake() before printing again, even if reset
  printer.setDefault();
}

// Eyelids
void eyeOpen() {
  if (eyeOpenStatus == false) {
    Serial.println("eye open");
    for (int pos = 0; pos <= 90; pos += 2) {  // Sweep from 0 to 180 degrees
      servo.write(pos);
      delay(10);
    }
    eyeOpenStatus = true;
    delay(500);
  }
}

void eyeClose() {
  if (eyeOpenStatus == true) {
    Serial.println("eye close");
    for (int pos = 90; pos >= 0; pos -= 2) {  // Sweep from 0 to 180 degrees
      servo.write(pos);
      delay(10);
    }
    eyeOpenStatus = false;
    delay(500);
  }
}

// Light feedback functions
void lightNeutral() {
  strip1.clear();
  strip2.clear();

  for (int i = 0; i < LED_COUNT_1; i++) {
    strip1.setPixelColor(i, strip1.Color(255, 255, 255));
    strip2.setPixelColor(i, strip2.Color(255, 255, 255));
  }
  strip1.show();
  strip2.show();
}

void lightRed() {
  strip1.clear();
  strip2.clear();

  for (int i = 0; i < LED_COUNT_1; i++) {
    strip1.setPixelColor(i, strip1.Color(255, 0, 0));
    strip2.setPixelColor(i, strip2.Color(255, 0, 0));
  }
  strip1.show();
  strip2.show();
  delay(2000);
}

void lightGreen() {
  strip1.clear();
  strip2.clear();

  for (int i = 0; i < LED_COUNT_1; i++) {
    strip1.setPixelColor(i, strip1.Color(0, 255, 0));
    strip2.setPixelColor(i, strip2.Color(0, 255, 0));
  }
  strip1.show();
  strip2.show();
  delay(2000);
}


// This code tests if the servo motor works
// >>>>>>
// void testServo() {
//   for (int pos = 0; pos <= 180; pos += 10) { // Sweep from 0 to 180 degrees
//     servo.write(pos);
//     delay(500);
//   }
//   for (int pos = 180; pos >= 0; pos -= 10) { // Sweep back to 0 degrees
//     servo.write(pos);
//     delay(500);
//   }
// }

void loop() {

  Serial.println(quote_interval - millis() - last_quote_time);
  if (millis() - last_quote_time > quote_interval) {

    state = QUOTE;
    last_quote_time = millis();
  }

  // Buttons
  bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
  bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);

  // Proximity sensor
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false);  // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
    distance = measure.RangeMilliMeter;
  } else {
    Serial.println(" out of range ");
  }

  switch (state) {
    case INIT:
      Serial.println("Waiting for motion sensor");
      delay(1000);
      Serial.println("Variable" + distance);
      if (distance <= 400) {
        state = READY;
        Serial.println("Person detected");
      } else {
        Serial.println("No person detected");
      }
      break;

    case READY:
      Serial.println("READY");
      // to add: soundReady();
      lightNeutral();  // {
      eyeOpen();
      delay(700);
      // Reading the buttons
      if (btn_left && btn_right) {
        Serial.println("Both buttons pressed.");
        state = BOTH;
      } else if (btn_left) {
        Serial.println("left button is pressed.");
        state = LEFT;
      } else if (btn_right) {
        Serial.println("right buttons pressed.");
        state = RIGHT;
      }
      break;

    case LEFT:
      lightRed();
      delay(500);
      // soundLeft();
      count_left++;
      getLeftMessage();
      state = READY;  // goes back to ready, for presentation purposes
      break;

    case RIGHT:
      lightGreen();
      delay(500);
      // soundRight();
      count_right++;

      getMessage(false, true, false);

      state = READY;  // goes back to ready, for presentation purposes
      break;

    case BOTH:
      lightShow();
      // soundShow
      // print from String btnBoth[]
      getMessage(true, true, false);
      state = STANDBY;  // first part of the presentation is done, goes to stand-by
      break;

    case STANDBY:  // {
      strip1.clear();
      strip2.clear();
      strip1.show();
      strip2.show();
      Serial.println("standby");
      eyeClose();

      delay(3000);
      last_quote_time = millis();
      state = QUOTE;

      break;
      // }

    case QUOTE:  // prints motivational quote
      lightNeutral();
      eyeOpen();
      // print from String quoteTime[]
      getMessage(false, false, true);
      Serial.println("quote");

      delay(1000);
      state = OFF;
      break;

    case OFF:
      strip1.clear();
      strip2.clear();
      strip1.show();
      strip2.show();
      Serial.println("OFF");
      eyeClose();

      delay(1000);
      state = INIT;
      break;
  }
}
