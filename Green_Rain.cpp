//Green Rain Matrix Animation 
//adapted from https://pastebin.com/tTuRDBYw 

#include "Green_Rain.h"

Green_Rain::Green_Rain()
{
  
}

void Green_Rain::init() 
{
  initialized = false;
  frequency = 10; //frequency of glitter flashes
  initialized = true;
}

void Green_Rain::loopLogic(CRGB leds[])
{
  //a timer is used to set a maximum fps
  unsigned long start = millis(); //start timer
  FastLED.show();
  Glitter(leds); //randomly lights up LEDs in different colors
  
  unsigned long delta = millis() - start; //end of timer
  if ( 1000 / FRAMES_PER_SECOND > delta) { //adds pause to ensure that fps is at or below the defined fps
    FastLED.delay(1000 / FRAMES_PER_SECOND - delta);
  }
   
}//end loopLogic

void Green_Rain::Glitter(CRGB leds[])
{
  int ledOffset = millis() * rainbowSpeed / FRAMES_PER_SECOND / 100 % NUM_LEDS ; // 0 - NUM_LEDS, calculates how far the generated table should be offset from the starting position for the given cycle count

  int lightToTurnOn[frequency]; //randomly generates which LEDs to turn on
  for (int i = 0; i < frequency; i++) {
    lightToTurnOn[i] = random16(0, NUM_LEDS);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(35);
  }

  for (int i = 0; i < frequency; i++) { //turns on LEDs that were selected
    leds[lightToTurnOn[i]] = CRGB(0,255,0);
  }
   
}//end glitter

bool Green_Rain::isInitialized()
{
    return(initialized);
  
}

void Green_Rain::modifyAnimationParameters()
{
    //return(initialized);
}
