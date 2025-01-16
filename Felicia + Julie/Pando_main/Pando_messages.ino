#include "Adafruit_Thermal.h"

// #include "adalogo.h"
// #include "adaqrcode.h"

String btnRight[] = {"YAY! You did it! You're basically unstoppable.", "High-five through the airwaves! Pando is so proud of you!", "Woohoo! Green lights all the way, legend. Let us keep this streak going!", "You're on fire (in a good way)! Keep smashing those goals!", "Yas! You're killing it, champ.", "Panda-tastic! You're right on track!", "Panda ears, big cheers!", "Bamboo-tastic! Keep that streak alive!", "Paws up for you, superstar!", "Go you! Pando is blushing with pride!", "You did the thing! Panda proud!", "Pando is blushing because you're amazing!" };
String btnLeft[] = {"Sad panda noises... but hey, even pandas have off days. You got this!", "Uh-oh! Today wasn't the day, but you're still amazing!", "Aw, shoot! It's okay, you'll get it next time! Sending panda hugs.", "Oh no, panda is a little sad… but tomorrow's a new day!", "Uh-oh.. but I'm still here, rooting for you!", "Slow progress is still progress — keep climbing!", "Mistakes mean you're trying. Keep trying!", "Aw shoot.. but pandas take naps too!", "Oops! Today wasn't the day, but don't give up!", "Red light for now, but green vibes are coming soon!"};
String btnBoth[] = {"Oh. My. Panda. YOU DID IT! Celebratory light show!", "Holy bamboo sticks, you're incredible! Time to party with panda lights!", "Achievement unlocked! Panda joy level: MAXIMUM. You're the best!", "WOOHOO! Project complete!", "You're an absolute legend. Take a bow!", "DONEZO! pando is doing the electric slide in your honour. Keep being awesome!", "You crushed it! Pando is doing a happy dance!", "Bamboo-hooray! You're killing it. Success looks good on you!", "Ears are dancing, lights are glowing — YOU. DID. IT!"};
String quoteMessage[] = {"Today's mood: Cute, capable, and crushing it!", "Your vibe: Unstoppable. Your look: Adorable. Your day: Conquered.", "You're like bamboo: growing stronger every day!", "You're 100% that panda. Keep going!", "Big things start with small steps. Keep stepping!", "Be the person your panda thinks you are!", "You're doing bear-y great things, friend!", "The world needs more of you. Stay awesome!", "You're bamboo-zling me with your awesomeness!", "Procrastination? I don't know her. Let's get it!", "Who's doing amazing? It's you, bestie.", "Small steps lead to big leaps. Unless you're a panda, then it's a waddle. Waddle on!", "Good vibes only (and maybe snacks).", "Don't stop now, you're almost at your next bamboo snack!"};
String messageToPrint = "";

void getRightMessage() {
  printer.feed(4);
  printer.setSize('M');
  printer.boldOn();
  printer.justify('C');
  randNumber = random(0, sizeof(btnRight) / sizeof(btnRight[0]));
  messageToPrint = btnRight[randNumber];
  printer.println(messageToPrint);
  
  // Space between
  printer.feed(2);

  printer.setSize('S');
  printer.boldOff();
  printer.justify('L');

  // Updated counter
  printer.print("YES: ");
  printer.println(count_right);
  printer.print("NO: ");
  printer.println(count_left);
  printer.feed(6);
  
}

void getLeftMessage() {
  printer.feed(4);
  printer.setSize('M');
  printer.boldOn();
  printer.justify('C');
  randNumber = random(0, sizeof(btnLeft) / sizeof(btnLeft[0]));
  messageToPrint = btnLeft[randNumber];
  printer.println(messageToPrint);
  
  // Space between
  printer.feed(2);

  printer.setSize('S');
  printer.boldOff();
  printer.justify('L');

  // Updated counter
  printer.print("YES: ");
  printer.println(count_right);
  printer.print("NO: ");
  printer.println(count_left);
  printer.feed(6);
}

void getBothMessage() {
  printer.feed(4);
  printer.setSize('L');
  printer.boldOn();
  printer.justify('C');
  randNumber = random(0, sizeof(btnBoth) / sizeof(btnBoth[0]));
  messageToPrint = btnBoth[randNumber];
  printer.println(messageToPrint);
  
  printer.feed(6);
}

void getQuoteMessage() {
  printer.feed(4);
  printer.setSize('L');
  printer.boldOn();
  printer.justify('C');
  randNumber = random(0, sizeof(quoteMessage) / sizeof(quoteMessage[0]));
  messageToPrint = quoteMessage[randNumber];
  printer.println(messageToPrint);
  // printer.println("U+2764"); trying very hard to add a heart here!! or something else super cute

  printer.feed(6);
}