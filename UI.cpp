//LED Table UI logic

#include "UI.h"

UI::UI(int pot1pin, int pot2pin, int rot1ButtonPin, int rot1Apin, int rot1Bpin, int rot2ButtonPin, int rot2Apin, int rot2Bpin, int button3Pin, int button4Pin) 
{
  this->pot1_pin = pot1pin;
  this->pot2_pin = pot2pin;
  this->rot1_button_pin = rot1ButtonPin;
  this->rot1_A_pin = rot1_A_pin;
  this->rot1_B_pin = rot1_B_pin;
  this->rot2_button_pin = rot2ButtonPin;
  this->rot2_A_pin = rot2_A_pin;
  this->rot2_B_pin = rot2_B_pin;
  this->button_3_pin = button3Pin;
  this->button_4_pin = button4Pin;
  
}

void UI::init() 
{
  //configure digital pins. analog pins do not require setup
  pinMode(rot1_button_pin, INPUT_PULLUP);
  pinMode(rot2_button_pin, INPUT_PULLUP);
  pinMode(button_3_pin, INPUT_PULLUP);
  pinMode(button_4_pin, INPUT_PULLUP);

  pot1Val = 0;
  pot2Val = 0;

  enc1PreviousHigh = digitalRead(rot1_A_pin);
  enc2PreviousHigh = digitalRead(rot2_A_pin);
  enc1High = false;
  enc2High = false;

  enc1State = UNMOVED;
  enc2State = UNMOVED;
  
  //get initial state
  readState();

  //compensate for unitialized previousVal variable
  pot1moved = false;
  pot2moved = false;
}


void UI::readState() 
{

  pot1PreviousVal = pot1Val;
  pot2PreviousVal = pot2Val;

  
  pot1Val = analogRead(pot1_pin); //0 to 1024
  pot2Val = analogRead(pot2_pin); //0 to 1024

  if(abs(pot1Val- pot1PreviousVal) > ALLOWABLE_ADC_ERROR_WHEN_UNMOVED)
  {
    pot1moved = true;
  }

  if(abs(pot2Val- pot2PreviousVal) > ALLOWABLE_ADC_ERROR_WHEN_UNMOVED)
  {
    pot2moved = true;
  }


  //read buttons
  //these are inverted because of the pullup configuration in HW
  //being cute here to save space but i think Arduino has defined LOW == false
  rot1ButtonPressed = !(digitalRead(rot1_button_pin));
  rot2ButtonPressed = !(digitalRead(rot2_button_pin));
  button3Pressed = !(digitalRead(button_3_pin));
  button4Pressed = !(digitalRead(button_4_pin));
 
  
  //scan encoders
  enc1State = UNMOVED;
  enc1High = digitalRead(rot1_A_pin);

  if (enc1High != enc1PreviousHigh)
  {
    if (digitalRead(rot1_B_pin) != enc1High)
    {
      enc1State = FORWARD;
    }
    else
    {
      enc1State = BACKWARD;
    }
  }
  
  enc2PreviousHigh = enc2High;
  
   enc2State = UNMOVED;
  enc2High = digitalRead(rot2_A_pin);

  if (enc2High != enc2PreviousHigh)
  {
    if (digitalRead(rot2_B_pin) != enc2High)
    {
      enc2State = FORWARD;
    }
    else
    {
      enc2State = BACKWARD;
    }
  }
  
  enc2PreviousHigh = enc2High;
  
}

void UI::resetMoved() 
{
  pot1moved = false;
  pot2moved = false;
  
}
