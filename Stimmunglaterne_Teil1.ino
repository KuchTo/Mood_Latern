#include <Adafruit_NeoPixel.h>

#define PIN        6  // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 12 // How many NeoPixels are attached to the Arduino? // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

long lastTime;
int interval;

void setup() 
  {
  pixels.begin(); // INITIALIZE NeoPixels
  interval = 150;
  randomSeed(analogRead(0));
  }

void SimulateFire (bool On, int FireSquence)
  {
  if (On)
    {
    long nowmilli=millis();
    if (nowmilli-lastTime>=interval)
      { 
      byte LightValue[NUMPIXELS* 3];  
      byte FireColor = 60;
      interval = random(150,200);    
      lastTime=nowmilli;
      FireColor = 60; //random(0,50);   
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel...
        LightValue[i*3] = random(240,255); // 250
        LightValue[i*3+1] = random(30,60); // 50
        LightValue[i*3+2] = 0;
        }
      // Switch some lights darker
      byte LightsOff  = random(0,4); 
      for(int i=0; i<LightsOff; i++) 
        { 
        byte Selected = random(NUMPIXELS);
        LightValue[Selected*3] = random(50,60);
        LightValue[Selected*3+1] = random(5,10);
        LightValue[Selected*3+2] = 0; 
        }     
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(LightValue[i*3], LightValue[i*3+1], LightValue[i*3+2])); 
        pixels.show();   // Send the updated pixel colors to the hardware.  
        }
      }
    }
  else
    {
    for(int i=0; i<NUMPIXELS; i++) 
      { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.  
      }  
    }    
  }
  

void loop() 
  {

    
    SimulateFire(true,0);

    
  }
