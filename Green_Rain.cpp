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
  brightness = 255;
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

  int lightToTurnOn[frequency]; //randomly generates which LEDs to turn on
  for (int i = 0; i < frequency; i++) {
    lightToTurnOn[i] = random16(0, NUM_LEDS);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(35);
  }

  for (int i = 0; i < frequency; i++) { //turns on LEDs that were selected
    leds[lightToTurnOn[i]] = CRGB(0,brightness,0);
  }
   
}//end glitter

bool Green_Rain::isInitialized()
{
    return(initialized);
  
}

void Green_Rain::modifyAnimationParameters(int param1, int param2)
{
    brightness = SCALE(param1,MAX_BRIGHTNESS);
    frequency = SCALE(param2,MAX_FREQ_FOR_TASTEFULNESS);
    
    //return(initialized);
}