//Green Rain Matrix Animation 
//adapted from https://pastebin.com/tTuRDBYw 

#include "Solid_Fill.h"

Solid_Fill::Solid_Fill()
{
  
}

void Solid_Fill::init() 
{
  initialized = false;
  
  brightness = 255; //default to max until pot is touched
  color = CYAN;
  r = 0;
  g = 255;
  b = 255;
    
  initialized = true;
  
  //light table
  //fill(leds);
  
}

void Solid_Fill::loop(CRGB leds[])
{
  //!!! fill with the same color data every cycle, shouldn't hurt anything

  fill(leds);
  FastLED.show();
}

void Solid_Fill::fill(CRGB leds[])
{
  if(!initialized){return;}
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(r,g,b);
  }
}//end fill

bool Solid_Fill::isInitialized()
{
    return(initialized);
  
}



//using brightness potentiometer and color-pallette encoder
void Solid_Fill::changeBrightness(int pot1)
{
  //scale brightness from potentiometer range
  brightness = map(pot1, 0, 1023, 0, 255);
}

void Solid_Fill::changeColor(bool forward)
{   
    //choose color from basic set, so brightness can scale at 255
    if(forward)
    {
      switch (color)
      {
        case OFF:
          color = RED;  
          break;
        case RED:
          color = GREEN;  
          break;
        case GREEN:
          color = YELLOW;
          break;
        case YELLOW:
          color = BLUE;  
          break;
        case BLUE:
          color = MAGENTA;  
          break;
        case MAGENTA:
          color = CYAN;
          break;
        case CYAN:
          color = WHITE;
          break;
        case WHITE:
          color = OFF;
          break;
      }
      
    }else
    {
      switch (color)
      {
        case OFF:
          color = WHITE;  
          break;
        case RED:
          color = OFF;  
          break;
        case GREEN:
          color = RED;
          break;
        case YELLOW:
          color = GREEN;  
          break;
        case BLUE:
          color = YELLOW;  
          break;
        case MAGENTA:
          color = BLUE;
          break;
        case CYAN:
          color = MAGENTA;
          break;
        case WHITE:
          color = CYAN;
          break;
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
    
    
#ifdef DEBUG
    Serial.println("color: " + color);
    Serial.println("brightness: " + brightness);
#endif

}
