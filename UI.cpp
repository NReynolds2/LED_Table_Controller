//LED Table UI logic

#include "UI.h"

UI::UI(int pot1pin, int pot2pin, int rot1ButtonPin, int rot2ButtonPin, int button3Pin, int button4Pin) 
{
  this->pot1_pin = pot1pin;
  this->pot2_pin = pot2pin;
  this->rot1_button_pin = rot1ButtonPin;
  this->rot2_button_pin = rot2ButtonPin;
  this->button_3_pin = button3Pin;
  this->button_4_pin = button4Pin;
  
  //init();
}

void UI::init() 
{
  //configure digital pins. analog pins do not require setup
  pinMode(rot1_button_pin, INPUT_PULLUP);
  pinMode(rot2_button_pin, INPUT_PULLUP);
  pinMode(button_3_pin, INPUT_PULLUP);
  pinMode(button_4_pin, INPUT_PULLUP);

  //get initial state
  readState();
}


void UI::readState() 
{
  pot1Val = analogRead(pot1_pin); //0 to 1024
  pot2Val = analogRead(pot2_pin); //0 to 1024
  //scan encoders
  //read buttons
}
