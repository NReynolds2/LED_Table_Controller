//LED Table UI logic

#include "UI.h"

UI::UI(int pot1pin, int pot2pin, int rot1ButtonPin, int rot1Apin, int rot1Bpin, int rot2ButtonPin, int rot2Apin, int rot2Bpin, int button3Pin, int button4Pin) 
{
  this->pot1_pin = pot1pin;
  this->pot2_pin = pot2pin;
  this->rot1_button_pin = rot1ButtonPin;
  this->rot1_A_pin = rot1Apin;
  this->rot1_B_pin = rot1Bpin;
  this->rot2_button_pin = rot2ButtonPin;
  this->rot2_A_pin = rot2Apin;
  this->rot2_B_pin = rot2Bpin;
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

  pinMode(rot2_A_pin, INPUT);
  pinMode(rot2_B_pin, INPUT);

  pinMode(rot1_A_pin, INPUT);
  pinMode(rot1_B_pin, INPUT);

  pot1Val = 0;
  pot2Val = 0;

  enc1APreviousVal = digitalRead(rot1_A_pin);
  enc1State = UNMOVED;
  
  enc2APreviousVal = digitalRead(rot2_A_pin);
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

  //first encoder
  enc1State = UNMOVED;
  enc1AVal = digitalRead(rot1_A_pin);

  if (enc1AVal != enc1APreviousVal)
  {
    enc1BVal = digitalRead(rot1_B_pin);
    
    if ( enc1BVal != enc1AVal)
    {
      enc1State = FORWARD;
    }
    else
    {
      enc1State = BACKWARD;
    }
  }
  
  enc1APreviousVal = enc1AVal;


  //second encoder
  enc2State = UNMOVED;
  enc2AVal = digitalRead(rot2_A_pin);

  if (enc2AVal != enc2APreviousVal)
  {
    enc2BVal = digitalRead(rot2_B_pin);
    
    if ( enc2BVal != enc2AVal)
    {
      enc2State = FORWARD;
    }
    else
    {
      enc2State = BACKWARD;
    }
  }
  
  enc2APreviousVal = enc2AVal;

  
//#ifdef UI_DEBUG
  if((millis() - debugCounter) >= DEBUG_UPDATE_RATE)
  {
    /*
    Serial.print("\n\n\n\n\n");
    Serial.print("\npot1Val: " + pot1Val);
    Serial.print(pot1Val, DEC);
    Serial.print("\npot2Val: " + pot2Val);
    Serial.print(pot2Val, DEC);
  
    Serial.print("\npot1moved: ");
    Serial.print(pot1moved, DEC);
    Serial.print("\npot2moved: ");
    Serial.print(pot2moved, DEC);
    
    Serial.print("\nButton1Pressed: ");
    Serial.print(rot1ButtonPressed, DEC);
    Serial.print("\nButton2Pressed: ");
    Serial.print(rot2ButtonPressed, DEC);
    Serial.print("\nButton3Pressed: ");
    Serial.print(button3Pressed, DEC);
    Serial.print("\nbutton4Pressed: ");
    Serial.print(button4Pressed, DEC);
*/
    Serial.print("\n\nenc1AVal: " + enc1AVal);
    Serial.print("\nenc1BVal: " + enc1BVal);
    Serial.print("\nenc1State: ");
    Serial.print(enc1State, DEC);
    
    Serial.print("\n\nenc2AVal: " + enc2AVal);
    Serial.print("\nenc2BVal: " + enc2BVal);
    Serial.print("\nenc2State: ");
    Serial.print(enc2State, DEC);

    debugCounter = millis();
 }
//#endif

  
}

void UI::resetMoved() 
{
  pot1moved = false;
  pot2moved = false;
  
}
