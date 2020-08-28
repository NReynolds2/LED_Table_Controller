#ifndef UI_H
#define UI_H

//----------- Includes ------------------------------
#include <Arduino.h>
//---------------------------------------------------


//----------- UI Defines ----------------------------
#define ALLOWABLE_ADC_ERROR_WHEN_UNMOVED        3 //ADC Counts

//---------------------------------------------------

//---------- Classes --------------------------------
class UI{
  
  private:
    //pins
    int pot1_pin;
    int pot2_pin;
    int rot1_button_pin;
    int rot1_A_pin;
    int rot1_B_pin;
    int rot2_button_pin;
    int rot2_A_pin;
    int rot2_B_pin;
    int button_3_pin;
    int button_4_pin;
    
    //vars
    int pot1PreviousVal;
    int pot2PreviousVal;
    
  public:
    UI(int pot1pin,
       int pot2pin,
       int rot1ButtonPin,
       int rot1Apin,
       int rot1Bpin,
       int rot2ButtonPin,
       int rot2Apin,
       int rot2Bpin,
       int button3Pin,
       int button4Pin);
    void init();
    void readState();
    void resetMoved();
    
    int pot1Val; //"Brightness"
    int pot2Val; //"Speed"

    bool pot1moved;
    bool pot2moved;

    bool rot1ButtonPressed;
    bool rot2ButtonPressed;
    bool button3Pressed;
    bool button4Pressed;
    
};
//---------------------------------------------------
#endif
