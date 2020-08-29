
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
#include "Twinkle.h"
//---------------------------------------------------

//----------- Fast LED Variables --------------------
//CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;
//--------------------------------------------------


//----------- Application Variables -----------------
enum ANIMATION_STATE animation_state = GREEN_RAIN;
boolean pauseAnimation = false;
unsigned long startTime;
 
UI ui(POTENTIOMETER_1_PIN,
      POTENTIOMETER_2_PIN,
      ENCODER_1_BUTTON_PIN,
      ENCODER_1_A_PIN,
      ENCODER_1_B_PIN,
      ENCODER_2_BUTTON_PIN,
      ENCODER_2_A_PIN,
      ENCODER_2_B_PIN,
      BUTTON_3_PIN, 
      BUTTON_4_PIN);
      
Green_Rain green_rain;
Twinkle twinkle;
//--------------------------------------------------


void setup()
{
  delay(3000); //arbitrary

#ifdef DEBUG_MODE
  Serial.begin(57600);
#endif
  
  ui.init();
  
  LEDS.addLeds<LED_TYPE, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  startTime = millis();
}

void loop()
{
  //Read UI
  ui.readState();
  
  //temporary, for testing:
  if(ui.button3Pressed)
  {
    animation_state = GREEN_RAIN;
  }
  else
  {
    animation_state = TWINKLE;
  }

  if(((millis()-startTime) > 3000) && (ui.button4Pressed))
  {
    pauseAnimation = true;
  }
  else
  {
    pauseAnimation = false;
  }

  if(!pauseAnimation)
  {
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
            if((ui.pot1moved) || (ui.pot2moved))
            {
              green_rain.modifyAnimationParameters(ui.pot1Val, ui.pot2Val);
            }
            green_rain.loopLogic(leds);
          }
        break;
        
      case RAINBOW_CYCLE:
        break;
      case RAINBOW_RAIN:
        break;
      case TWINKLE:
        
        if(!(twinkle.isInitialized()))
          {
            twinkle.init();
          }
        else
          {
            if((ui.pot1moved) || (ui.pot2moved))
            {
              twinkle.modifyAnimationParameters(ui.pot1Val, ui.pot2Val);
            }
            twinkle.loopLogic(leds);
          }
        break;
        
    }
  }
}
