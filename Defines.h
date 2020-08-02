#ifndef DEFINES_H
#define DEFINES_H



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
#define ENCODER_1_BUTTON_PIN      5
#define ENCODER_2_BUTTON_PIN      2
#define BUTTON_3_PIN              8
#define BUTTON_4_PIN              9

enum ANIMATION_STATE { FIRE, GREEN_RAIN, RAINBOW_CYCLE, RAINBOW_RAIN, TWINKLE };
//--------------------------------------------------

#endif
