// NeoPixel strips lightshow
void lightShow() {
  theaterChaseSync(strip1, strip2, strip1.Color(127, 127, 127), 50);
  rainbowSync(strip1, strip2, 10);
}

// Syncs the two strips / led circles
void colorWipeSync(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, uint32_t color, int wait) {
  for (int i = 0; i < strip1.numPixels(); i++) {
    strip1.setPixelColor(i, color);
    strip2.setPixelColor(i, color);
    strip1.show();
    strip2.show();
    delay(wait);
  }
}

// The pixels "chase" each other, i.e. they run around
void theaterChaseSync(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, uint32_t color, int wait) {
  for (int a = 0; a < 20; a++) {
    for (int b = 0; b < 3; b++) {
      strip1.clear();
      strip2.clear();
      for (int c = b; c < strip1.numPixels(); c += 3) {
        strip1.setPixelColor(c, color);
        strip2.setPixelColor(c, color);
      }
      strip1.show();
      strip2.show();
      delay(wait);
    }
  }
}

// Pretty rainbow
void rainbowSync(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 8192; firstPixelHue += 256) {
    strip1.rainbow(firstPixelHue);
    strip2.rainbow(firstPixelHue);
    strip1.show();
    strip2.show();
    delay(70);
    }
  }