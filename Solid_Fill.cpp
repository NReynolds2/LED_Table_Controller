//Green Rain Matrix Animation 
//adapted from https://pastebin.com/tTuRDBYw 

#include "Green_Rain.h"

Solid_Fill::Solid_Fill()
{
  
}

void Solid_Fill::init(CRGB leds[]) 
{
  initialized = false;
  
  brightness = 255; //default to max until pot is touched
  color = CYAN;
  r = 0;
  g = 255;
  b = 255;
    
  initialized = true;
  
  //light table
  fill(leds);
  
}

void Solid_Fill::loop(CRGB leds[])
{
  //This function does not animate
  fastLED.show();
}

void Solid_Fill::fill(CRGB leds[])
{
  if(!initialized){return;}
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(r,g,b);
  }
}//end fill

bool SOLID_FILL::isInitialized()
{
    return(initialized);
  
}


//using brightness potentiometer and color-pallette encoder
void Solid_Fill::changeColor(int pot, bool forward)
{
    //scale brightness from potentiometer range
    brightness = map(pot, 0, 1023, 0, 255);

    
    //choose color from basic set, so brightness can scale at 255
    if(forward)
    {
      color++;
      if(color > NUM_BASIC_COLORS-1)
      {
        color = 1;
      }
    }else
    {
      color--;
      if(color < 0)
      {
        color = NUM_BASIC_COLORS-1;
      }
    }
    
    switch (color)
    {
      case OFF:
        r = 0;
        g = 0;
        b = 0;
        break;
      case RED:
        r = brightness;
        g = 0;
        b = 0;
        break;
      case GREEN:
        r = 0;
        g = brightness;
        b = 0;
        break;
      case YELLOW:
        r = brightness;
        g = brightness;
        b = 0;
        break;
      case BLUE:
        r = 0;
        g = 0;
        b = brightness;
        break;
      case MAGENTA:
        r = brightness;
        g = 0;
        b = brightness;
        break;
      case CYAN:
        r = 0;
        g = brightness;
        b = brightness;
        break;
      case WHITE:
        r = brightness;
        g = brightness;
        b = brightness;
        break;
    }
    
    //push new color to the LEDs
    fill(leds);
    
#ifdef DEBUG
    Serial.println("color: " + color);
    Serial.println("brightness: " + brightness);
#endif

}
