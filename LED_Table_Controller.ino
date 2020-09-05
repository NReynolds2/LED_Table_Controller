
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
Animation *animation[2];
//--------------------------------------------------


void setup()
{
  delay(3000); //arbitrary

  animation[0] = &green_rain;
  animation[1] = &twinkle;
  
#ifdef DEBUG_MODE
  Serial.begin(57600);
  Serial.println("Serial Test Data:\n\n");
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
  

  if(ui.enc1State == FORWARD)
  {
    animation_state = (ANIMATION_STATE)(animation_state + 1);

    if(animation_state > (NUM_ANIMATIONS - 1))
    {
      animation_state = (ANIMATION_STATE)0;
    }
  }
  else if(ui.enc1State == BACKWARD)
  {
    if(animation_state == 0)
    {
      animation_state = (ANIMATION_STATE)(NUM_ANIMATIONS - 1);
    }
    
    if(animation_state > 0)
    {
    animation_state = (ANIMATION_STATE)(animation_state - 1);
    }
    
  }
  
  //animation_state = GREEN_RAIN;
  

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
      //case FIRE:
      //  break;
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
        
      //case RAINBOW_CYCLE:
      //  break;
      //case RAINBOW_RAIN:
      //  break;
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
