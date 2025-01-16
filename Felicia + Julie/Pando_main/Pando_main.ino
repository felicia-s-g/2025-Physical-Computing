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
long quote_time = 0;
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

// Printer
Adafruit_Thermal printer(&Serial0);

void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(0));

  // Buttons
  pinMode(btn_left_pin, INPUT);
  pinMode(btn_right_pin, INPUT);

  // NeoPixel
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip1.begin();
  strip1.show();
  strip1.setBrightness(50);
  strip2.begin();
  strip2.show();
  strip2.setBrightness(50);

  // Servo motor
  servo.attach(9);

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

  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault();
}

//   This is code related to the touch sensor that doesn't work
//   >>>
//   //ultra sonic distance sensor
//   //if (lox.isRangeComplete()) {
//   //  Serial.print("Distance in mm: ");
//   //  Serial.println(lox.readRange());
//   //}

//   //if (ultrasonic_distance >= 15 && ultrasonic_distance <= 20 && led_status == false){
//   //  Serial.println("I am activated");
//   //  lightNeutral();  //TODO: i need to make it light up gently
//   //  led_status = true;


// Eyelids
void eyeOpen() {
  servo.write(90);
  delay(1000);
}

void eyeClose() {
  servo.write(0);
  delay(500);
}

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

  // this code doesn't work yet because i haven't figured out the math
  // >>
  // quote_time += millis();
  // if (last_quote_time == 0 && millis() >= 1000 * 50) {
  // state = QUOTE;
  // }
  // else if (quote_time - last_quote_time >= 1000 * 50) {
  //   state = QUOTE;
  // }

  bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
  bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);

  // if (btn_left_status == 1 || btn_left_status == 2) {
  // lightGreen();
  // }
  // if (btn_right_status == 1 || btn_right_status == 2) {
  // lightRed();
  // }

  // Proximity sensor
  if (lox.isRangeComplete()) {
    Serial.print("Distance in mm: ");
    Serial.println(lox.readRange());
  }
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();

    switch (state) {
      case INIT:
        Serial.println("Waiting for motion sensor");
        delay(1000);
        // {
        // if motion sensor Distance in mm <=400 go to:
        state = READY;
        break;
      // }
      case READY:
        Serial.println("READY");
        // to add: soundReady();
        lightNeutral();  // {
        eyeOpen();
        delay(1000);
        // reading the buttons
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
        // }
        // to add: after delay / prolonged inactivity, go to case STANDBY
        break;

      case LEFT:
        {
          lightRed();
          delay(50);
          // soundLeft();
          count_left++;
          String message = getMessage(true, false, false);
          Serial.println(message);
          state = READY;  // goes back to ready, for presentation purposes
          break;
        }
      case RIGHT:
        {
          lightGreen();
          delay(50);
          // soundRight();
          count_right++;
          String message = getMessage(false, true, false);
          Serial.println(message);
          state = READY;  // goes back to ready, for presentation purposes
          break;
        }

      case BOTH:
        {
          lightShow();
          // soundShow
          // print from String btnBoth[]
          String message = getMessage(true, true, false);
          Serial.println(message);


          state = STANDBY;  // first part of the presentation is done, goes to stand-by
        }
        break;

      case STANDBY:  // {
        strip1.clear();
        strip2.clear();
        strip1.show();
        strip2.show();
        Serial.println("standby");
        eyeClose();
        break;
        // }

      case QUOTE:
        {
          // { // printing motivational quote
          eyeOpen();
          // print from String quoteTime[]
          last_quote_time = quote_time;
          quote_time = 0;
          String message = getMessage(false, false, true);
          Serial.println(message);
          Serial.println("q");
          state = OFF;
        }
        break;

      case OFF:
        strip1.clear();
        strip2.clear();
        strip1.show();
        strip2.show();
        Serial.println("OFF");
        // eyeClose();
        break;
    }
  }
