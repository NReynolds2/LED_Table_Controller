#ifndef GREEN_RAIN_H
#define GREEN_RAIN_H

//----------- Includes ------------------------------
#include <Arduino.h>
#include <FastLED.h>
#include "Defines.h"
//---------------------------------------------------


//----------- Defines -------------------------------
#define FRAMES_PER_SECOND               50        //it takes ~20ms to push all the data to all 579 LEDs so the hard limit is ~50fps


#define MAX_FREQ_FOR_TASTEFULNESS       200
#define MIN_FREQ_FOR_TASTEFULNESS       0

#define MAX_BRIGHTNESS                  255
#define MIN_BRIGHTNESS                  0
//---------------------------------------------------

//---------- Classes --------------------------------
class Green_Rain{
  
  private:
    int pot1_pin;
    int frequency;
    int brightness;
    bool initialized;
    byte r;
    byte g;
    byte b;
    
  public:
    Green_Rain();
    void init();
    void loopLogic(CRGB leds[]);
    void Glitter(CRGB leds[]);
    bool isInitialized();
    void modifyAnimationParameters(int param1, int param2);
};
//---------------------------------------------------
#endif
