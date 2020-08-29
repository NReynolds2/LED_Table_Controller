#ifndef DEFINES_H
#define DEFINES_H

//----------- Output Serial Debug Info --------------

//#define UI_DEBUG
//#define GREEN_RAIN_DEBUG


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
#define ENCODER_1_BUTTON_PIN      3 
#define ENCODER_1_A_PIN           7
#define ENCODER_1_B_PIN           6
#define ENCODER_2_BUTTON_PIN      2
#define ENCODER_2_A_PIN           4
#define ENCODER_2_B_PIN           10 //fix
#define BUTTON_3_PIN              51
#define BUTTON_4_PIN              52

enum ANIMATION_STATE { FIRE, GREEN_RAIN, RAINBOW_CYCLE, RAINBOW_RAIN, TWINKLE };
//--------------------------------------------------

//------------------ MACROS ------------------------

#define SCALE(value,newScaleMax)                ( ((value)*(newScaleMax)) / 1024)
//--------------------------------------------------


#endif
