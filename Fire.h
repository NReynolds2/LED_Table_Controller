#ifndef FIRE_H
#define FIRE_H

//----------- Includes ------------------------------
#include <Arduino.h>
#include <FastLED.h>
#include "Defines.h"
//---------------------------------------------------


//----------- Defines -------------------------------
#define FRAMES_PER_SECOND               60        
#define FLAME_HEIGHT                    40
#define COOLING                         70                    // COOLING: How much does the air cool as it rises?
                                                              // Less cooling = taller flames.  More cooling = shorter flames.
                                                              // Default 50, suggested range 20-100 
#define SPARKING                        120                   // SPARKING: What chance (out of 255) is there that a new spark will be lit?
                                                              // Higher chance = more roaring fire.  Lower chance = more flickery fire.
                                                              // Default 120, suggested range 50-200.
//for mirroring flame animation on table:                                                                                                                            
#define ROWS                            3
#define ROW_OFFSET                      (NUM_LEDS/ROWS)
#define CORNER_OFFSET                   ((NUM_LEDS/ROWS)/2)

//---------------------------------------------------

//---------- Classes --------------------------------
class Fire{
  
  private:
    int frequency;
    int brightness;
    bool initialized;
    
  public:
    Fire();
    void init();
    void loopLogic(CRGB leds[]);
    void renderAnimation(CRGB leds[]);
    bool isInitialized();
    void modifyAnimationParameters(int param1, int param2);
};
//---------------------------------------------------
#endif
