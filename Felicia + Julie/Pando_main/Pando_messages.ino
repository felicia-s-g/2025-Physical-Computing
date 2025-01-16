#include "Adafruit_Thermal.h"

// #include "adalogo.h"
// #include "adaqrcode.h"

String btnRight[] = { "YAY! You did it! You\’re basically unstoppable.", "High-five through the airwaves! Pando is so proud of you!", "Woohoo! Green lights all the way, legend. Let\’s keep this streak going!", "You\’re on fire (in a good way)! Keep smashing those goals!", "Yas! You\’re killing it, champ.", "Panda-tastic! You\’re right on track!", "Panda ears, big cheers!", "Bamboo-tastic! Keep that streak alive!", "Paws up for you, superstar!", "Go you! Pando is blushing with pride!", "You did the thing! Panda proud!", "Pando is blushing because you\’re amazing!" };
String btnLeft[] = { "A", "HB", "C", "G" };

String quote[] = { "1", "2", "3", "4" };
String btnBoth[] = { "Red", "Blue", "Green" };

void getLeftMessage() {
  randNumber = random(0, sizeof(btnLeft) / sizeof(btnLeft[0]));
  Serial.println(btnLeft[randNumber]);

  printer.println(btnLeft[randNumber]);
  printer.feed(4);

}


void getMessage(bool btn_left, bool btn_right, bool btn_time) {
  // if (btn_left && btn_right) {
  //   randNumber = random(0, sizeof(btnBoth) / sizeof(btnBoth[0]));
  //   Serial.println(btnBoth[randNumber]);
  //   return btnBoth[randNumber];
  // }
  // if (btn_left) {
  //   randNumber = random(0, sizeof(btnLeft) / sizeof(btnLeft[0]));
  //   Serial.println(btnLeft[randNumber]);
  //   return btnLeft[randNumber];
  // }
  if (btn_right) {
    randNumber = random(0, sizeof(btnRight) / sizeof(btnRight[0]));
    Serial.println(btnRight[randNumber]);

    printer.print(btnRight[randNumber]);
//    printer.printLongText(btnRight[randNumber], 16);
  }
  // if (state = QUOTE) {
  //   randNumber = random(0, sizeof(quoteTime) / sizeof(quoteTime[0]));
  //   Serial.println(quoteTime[randNumber]);
  //   return quoteTime[randNumber];
  // }
}



// yay you're great
// Y:20       N: 10

// Adafruit_Thermal printer(&Serial0);
// void printMessage(bool btn_left, bool btn_right, bool btn_time) {
// }