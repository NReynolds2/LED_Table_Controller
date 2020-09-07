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

void Green_Rain::loopLogic(CRGBSet& L)
{
  //a timer is used to set a maximum fps
  unsigned long start = millis(); //start timer
  FastLED.show();
  Glitter(L); //randomly lights up LEDs in different colors
  
  unsigned long delta = millis() - start; //end of timer
  if ( 1000 / FRAMES_PER_SECOND > delta) { //adds pause to ensure that fps is at or below the defined fps
    FastLED.delay(1000 / FRAMES_PER_SECOND - delta);
  }
   
}//end loopLogic

void Green_Rain::Glitter(CRGBSet& L)
{

  int lightToTurnOn[frequency]; //randomly generates which LEDs to turn on
  for (int i = 0; i < frequency; i++) {
    lightToTurnOn[i] = random16(0, NUM_LEDS);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    L[i].fadeToBlackBy(35);
  }

  for (int i = 0; i < frequency; i++) { //turns on LEDs that were selected
    L[lightToTurnOn[i]] = CRGB(0,brightness,0);
  }
   
}//end glitter

bool Green_Rain::isInitialized()
{
    return(initialized);
  
}

void Green_Rain::modifyAnimationParameters(int param1, int param2)
{
    
    brightness = map(param1, 0, 1023, 0, MAX_BRIGHTNESS);
    frequency = map(param2, 0, 1023, 0, MAX_FREQ_FOR_TASTEFULNESS);

#ifdef DEBUG
    Serial.println("frequency: " + frequency);
    Serial.println("brightness: " + brightness);
#endif

}
