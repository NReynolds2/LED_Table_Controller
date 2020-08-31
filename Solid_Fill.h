#ifndef GREEN_RAIN_H
#define GREEN_RAIN_H

//----------- Includes ------------------------------
#include <Arduino.h>
#include <FastLED.h>
#include "Defines.h"
//---------------------------------------------------


//----------- Defines -------------------------------

//---------------------------------------------------

//---------- Classes --------------------------------
class Solid_Fill{
  
  private:
    int pot1_pin;
    int brightness;
    enum BASIC_COLORS color;
    bool initialized;
    bool needsUpdate;
    byte r;
    byte g;
    byte b;
    
  public:
    Solid_Fill();
    void init();//void init(CRGB leds[]);
    void loop(CRGB leds[]);
    void fill(CRGB leds[]);
    bool isInitialized();
    void changeBrightness(int pot1);
    void changeColor(bool forward);
};
//---------------------------------------------------
#endif
