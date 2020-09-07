#ifndef DEFINES_H
#define DEFINES_H

//----------- Output Serial Debug Info --------------

#define UI_DEBUG
//#define GREEN_RAIN_DEBUG

#if defined(UI_DEBUG) || (GREEN_RAIN_DEBUG)
#define DEBUG_MODE
#warning "Debug Mode is ON"
#endif

//---------------------------------------------------


//----------- FastLED Defines -----------------------
#define LED_DATA_PIN              5
#define NUM_LEDS                  632
#define NUM_ROWS                  3
#define BRIGHTNESS                255
#define LED_TYPE                  WS2812
#define COLOR_ORDER               GRB

#define MAX_BRIGHTNESS 255      //only a concern if power consumption is an issue
//---------------------------------------------------



//----------- Application ENUM and Defines ---------
#define POTENTIOMETER_1_PIN       A1
#define POTENTIOMETER_2_PIN       A3
#define ENCODER_1_BUTTON_PIN      22 
#define ENCODER_1_A_PIN           39
#define ENCODER_1_B_PIN           35
#define ENCODER_2_BUTTON_PIN      2
#define ENCODER_2_A_PIN           31
#define ENCODER_2_B_PIN           27
#define BUTTON_3_PIN              51
#define BUTTON_4_PIN              52


#define NUM_ANIMATIONS 3
//--------------------------------------------------

//-------------------- Classes ---------------------

class Animation {
   protected:
      
   public:
    //animation();
    virtual void init() = 0;
    virtual void loopLogic(CRGBSet& L) = 0;
    virtual bool isInitialized() = 0;
    virtual void modifyAnimationParameters(int param1, int param2) = 0;
};

//--------------------------------------------------


#endif
