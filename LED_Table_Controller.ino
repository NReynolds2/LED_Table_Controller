
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
boolean pauseAnimation = false;
unsigned long startTime;
int activeAnimationNumber;

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

Animation *animation[NUM_ANIMATIONS] = {
  &green_rain,
  &twinkle
  };
  
//--------------------------------------------------


void setup()
{
  delay(3000); //arbitrary

#ifdef DEBUG_MODE
  Serial.begin(57600);
  Serial.println("Serial Test Data:\n\n");
#endif
   
  ui.init();
  
  LEDS.addLeds<LED_TYPE, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  startTime = millis();
  activeAnimationNumber = 0;
}

void loop()
{
  //Read UI
  ui.readState();


  //if enocder has moved, modifying what animation to show:
  if(ui.enc1State == FORWARD)
  {
    activeAnimationNumber++;

    if(activeAnimationNumber > (NUM_ANIMATIONS - 1))
    {
      activeAnimationNumber = 0;
    }
  }
  else if(ui.enc1State == BACKWARD)
  {
    if(activeAnimationNumber == 0)
    {
      activeAnimationNumber = (NUM_ANIMATIONS - 1);
    }
    else if(activeAnimationNumber > 0)
    {
      activeAnimationNumber--;
    }
  }
  
  
  //modifying pause if button pressed:
  if(((millis()-startTime) > 3000) && (ui.button4Pressed))
  {
    pauseAnimation = true;
  }
  else
  {
    pauseAnimation = false;
  }

  //initialize animaiton if needed, run loop animaition:
  if(!pauseAnimation)
  {
    
    if(!(animation[activeAnimationNumber]->isInitialized()))
      {
        animation[activeAnimationNumber]->init();
      }
    else
      {
        if((ui.pot1moved) || (ui.pot2moved))
        {
          animation[activeAnimationNumber]->modifyAnimationParameters(ui.pot1Val, ui.pot2Val);
        }
        
        animation[activeAnimationNumber]->loopLogic(leds);
      }
  }
}
