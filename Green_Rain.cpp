//Green Rain Matrix Animation 
//adapted from https://pastebin.com/tTuRDBYw 

#include "Green_Rain.h"

Green_Rain::Green_Rain()
{
  
}

void Green_Rain::init() 
{
  initialized = false;
  frequency = 10; //frequency of glitter flashes
  
  initColorArray();
  initialized = true;
}

void Green_Rain::initColorArray() 
{
  //initial bias is arbitary and then normalized to the rainbow size. More bias will make the respective section of the rainbow larger
  int BRsize = 90; //section between 100% blue and 100% red
  int RGsize = 100; //section between 100% red and 100% green
  int GBsize = 80; //section between 100% green and 100% blue
  int biasSum = BRsize + RGsize + GBsize;
  BRsize = size * (float(BRsize) / float(biasSum)); //normalize bias
  RGsize = size * (float(RGsize) / float(biasSum)); //normalize bias
  GBsize = size * (float(GBsize) / float(biasSum)); //normalize bias
  biasSum = BRsize + RGsize + GBsize;

  //makes the sum of the bias the same size as the rainbow, fixes "holes" caused by rounding
  if (biasSum < size) {
    BRsize ++;
    biasSum ++;
    if (biasSum < size) {
      RGsize ++;
      biasSum ++;
      if (biasSum < size) {
        GBsize ++;
        biasSum ++;
      }
    }
  }
  else if (biasSum > size) {
    BRsize --;
    biasSum --;
    if (biasSum > size) {
      RGsize --;
      biasSum --;
      if (biasSum > size) {
        GBsize --;
        biasSum --;
      }
    }
  }

  //generate the rainbow. Uses linear interpolations between points set by the bias
  for (int i = 0; i < BRsize; i++) {
    this->colorsArray[i] = CRGB( int(round(255 * float(i) / float(BRsize))) ,
                           0 ,
                           int(round(255 - 255 * float(i) / (BRsize) )));
  }
  for (int i = 0; i < RGsize; i++) {
    this->colorsArray[i + BRsize] = CRGB(int(round(255 - 255 * float(i) / float(RGsize))) , int(round(255 * (float(i) / float(RGsize)))) , 0 );

  }
  for (int i = 0; i < GBsize; i++) {
    this->colorsArray[i + BRsize + RGsize] = CRGB(0, int(round(255 - 255 * float(i) / float(GBsize))) , int(round(255 * (float(i) / float(GBsize)))));
  }

  //copy first row onto next two rows
  for (int i = 0; i < NUM_LEDS / 3; i++) {
    this->colorsArray[i + NUM_LEDS / 3] = colorsArray[i];
    this->colorsArray[i + 2 * NUM_LEDS / 3] = colorsArray[i];
  }
  
}//end initColorArray

void Green_Rain::loopLogic(CRGB leds[])
{
  //a timer is used to set a maximum fps
  unsigned long start = millis(); //start timer
  FastLED.show();
  Glitter(leds); //randomly lights up LEDs in different colors
  
  unsigned long delta = millis() - start; //end of timer
  if ( 1000 / FRAMES_PER_SECOND > delta) { //adds pause to ensure that fps is at or below the defined fps
    FastLED.delay(1000 / FRAMES_PER_SECOND - delta);
  }
   
}//end loopLogic

void Green_Rain::Glitter(CRGB leds[])
{
  int ledOffset = millis() * rainbowSpeed / FRAMES_PER_SECOND / 100 % NUM_LEDS ; // 0 - NUM_LEDS, calculates how far the generated table should be offset from the starting position for the given cycle count

  int lightToTurnOn[frequency]; //randomly generates which LEDs to turn on
  for (int i = 0; i < frequency; i++) {
    lightToTurnOn[i] = random16(0, NUM_LEDS);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(35);
  }

  for (int i = 0; i < frequency; i++) { //turns on LEDs that were selected
    //leds[lightToTurnOn[i]] = colorsArray[(lightToTurnOn[i] + ledOffset) % NUM_LEDS];
    leds[lightToTurnOn[i]] = CRGB(0,255,0);
  }
   
}//end glitter

bool Green_Rain::isInitialized()
{
    return(initialized);
  
}

void Green_Rain::modifyAnimationParameters()
{
    //return(initialized);
}
