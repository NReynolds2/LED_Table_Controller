#ifndef UI_H
#define UI_H

//----------- Includes ------------------------------
#include <Arduino.h>
//---------------------------------------------------



//---------- Classes --------------------------------
class UI{
  
  private:
    int pot1_pin;
    int pot2_pin;
    int rot1_button_pin;
    int rot2_button_pin;
    int button_3_pin;
    int button_4_pin;
    
  public:
    UI(int pot1pin,
       int pot2pin,
       int rot1ButtonPin,
       int rot2ButtonPin,
       int button3Pin,
       int button4Pin);
    void init();
    void readState();
    
    int pot1Val; //"Brightness"
    int pot2Val; //"Speed"
    int pot1PreviousVal;
    int pot2PreviousVal;
    
};
//---------------------------------------------------
#endif
