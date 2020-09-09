
#include "Fire.h"

Fire::Fire()
{
  
}

void Fire::init() 
{
  initialized = false;
  brightness = 200;
  initialized = true;
}

void Fire::loopLogic(CRGBSet& L)
{
  //initialize array with black because animation doesn't
  //update all cells:
  for (int i = 0; i < NUM_LEDS; i++) {
    L[i] = CRGB(0,0,0);
  }
  
  renderAnimation(L);
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
   
}//end loopLogic

void Fire::renderAnimation(CRGBSet& L)
{
  static byte heat[FLAME_HEIGHT];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < FLAME_HEIGHT; i++) 
    {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / FLAME_HEIGHT) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= FLAME_HEIGHT - 1; k >= 2; k--) 
    {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) 
    {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < FLAME_HEIGHT; j++) 
    {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
        pixelnumber = j;
      
      L[pixelnumber] = color;
      L[ROW_OFFSET+ pixelnumber - 1] = color;
      L[(ROW_OFFSET*2) + pixelnumber] = color;

      L[((NUM_LEDS-1) - pixelnumber)] = color;
      L[(NUM_LEDS-1) - (ROW_OFFSET+ pixelnumber) - 1] = color;
      L[(NUM_LEDS-1) - ((ROW_OFFSET*2) + pixelnumber)] = color;

      L[CORNER_OFFSET + pixelnumber] = color;
      L[CORNER_OFFSET + ROW_OFFSET+ pixelnumber - 1] = color;
      L[CORNER_OFFSET + (ROW_OFFSET*2) + pixelnumber] = color;

      //L[CORNER_OFFSET + ((NUM_LEDS-1) - pixelnumber)] = color;
      L[CORNER_OFFSET + (NUM_LEDS-1) - (ROW_OFFSET+ pixelnumber)] = color;
      L[CORNER_OFFSET + (NUM_LEDS-1) - ((ROW_OFFSET*2) + pixelnumber)] = color;
    }
}


bool Fire::isInitialized()
{
    return(initialized);
  
}

void Fire::modifyAnimationParameters(int param1, int param2)
{
    //tbd
    //brightness = map(param1, 0, 1023, 0, MAX_BRIGHTNESS);
    //frequency = map(param2, 0, 1023, 0, MAX_FREQ_FOR_TASTEFULNESS);

#ifdef FIRE_DEBUG
    //Serial.println("frequency: " + frequency);
    //Serial.println("brightness: " + brightness);
#endif

}
