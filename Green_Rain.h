#ifndef GREEN_RAIN_H
#define GREEN_RAIN_H

//----------- Includes ------------------------------
#include <Arduino.h>
#include <FastLED.h>
#include "Defines.h"
//---------------------------------------------------


//----------- Defines -------------------------------
#define FRAMES_PER_SECOND 50        //it takes ~20ms to push all the data to all 579 LEDs so the hard limit is ~50fps
#define rainbowSpeed 100            //bigger = faster rainbow

const int size = NUM_LEDS / NUM_ROWS; //size of the rainbow, per row of LEDs
//---------------------------------------------------

//---------- Classes --------------------------------
class Green_Rain{
  
  private:
    int pot1_pin;
    int frequency;
    bool initialized;
    CRGB colorsArray[NUM_LEDS];
    void initColorArray();
    
    
  public:
    Green_Rain();
    void init();
    void loopLogic(CRGB leds[]);
    void Glitter(CRGB leds[]);
    bool isInitialized();
};
//---------------------------------------------------
#endif
