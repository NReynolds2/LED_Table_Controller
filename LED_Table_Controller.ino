
//Nick Reynolds
//20-08-01
//Supervisor Application for UI and LED animation control

//----------- Arduino Libraries ---------------------
#include <FastLED.h>
//---------------------------------------------------

//----------- Includes ------------------------------
#include "Defines.h"
//---------------------------------------------------

//----------- Application Classes -------------------
#include "UI.h"
#include "Green_Rain.h"
//---------------------------------------------------

//----------- Fast LED Variables --------------------
CRGB leds[NUM_LEDS];
//--------------------------------------------------


//----------- Application Variables -----------------
enum ANIMATION_STATE animation_state = GREEN_RAIN;
 
UI ui(POTENTIOMETER_1_PIN,
      POTENTIOMETER_2_PIN,
      ENCODER_1_BUTTON_PIN,
      ENCODER_2_BUTTON_PIN,
      BUTTON_3_PIN, 
      BUTTON_4_PIN);
      
Green_Rain green_rain;
//--------------------------------------------------


void setup()
{
  delay(3000); //arbitrary

  ui.init();
  
  LEDS.addLeds<LED_TYPE, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(MAX_BRIGHTNESS);
}

void loop()
{
  //Read UI
  ui.readState();
  
  switch (animation_state)
  {
    case FIRE:
      break;
    case GREEN_RAIN:
    
      if(!(green_rain.isInitialized()))
        {
          green_rain.init();
        }
      else
        {
          green_rain.loopLogic(leds);
        }
      
      break;
    case RAINBOW_CYCLE:
      break;
    case RAINBOW_RAIN:
      break;
    case TWINKLE:
      break;
  }
  
}
