#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

#define PIN        6  // Which pin on the Arduino is connected to the NeoPixels?
#define RECV_PIN 11  // define IR input pin on Arduino 
#define NUMPIXELS 12 // How many NeoPixels are attached to the Arduino? // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(RECV_PIN); 
decode_results results; // decode_results class is defined in IRremote.h

long FirelastTime = 0;
long IRlastTime = 0;
long TimerlastTime = 0;
int interval;
long IRCode = 0;
long OLDIRCode = 0;
bool FireON = false;
bool FireOFF = false;
byte FireSequence = 0;

void setup() 
  {  
  Serial.begin(115200);
  while (!Serial);   //wait until Serial is established - required on some Platforms  
  irrecv.enableIRIn(); // Start the receiver 
  pixels.begin(); // INITIALIZE NeoPixels
  pixels.show(); // Initialize all pixels to 'off'    
  interval = 300;
  randomSeed(analogRead(0));
  }

void SimulateFire (bool On, byte FireSq)
  {
  byte LightValue[NUMPIXELS* 3];  

  if (millis()-FirelastTime>=interval)
  {   
  if (On)
    {
    FireOFF = false;
    FirelastTime=millis();
    interval = 200;    
    if (FireSq == 1)
      {
       for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel...
        LightValue[i*3] = random(200,255); // 250
        LightValue[i*3+1] = random(30,70); // 50
        LightValue[i*3+2] = 0;
        }
       for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel... 
        pixels.setPixelColor(i, LightValue[i*3], LightValue[i*3+1], LightValue[i*3+2]); 
        } 
       noInterrupts();   
       pixels.show();   // Send the updated pixel colors to the hardware. 
       interrupts();        
      }
    if (FireSq == 2)
      {
       for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel... 
        pixels.setPixelColor(i, 250, 50,0); 
        } 
       noInterrupts();   
       pixels.show();   // Send the updated pixel colors to the hardware. 
       interrupts();           
      }
    if (FireSq == 3)
      {
     interval = random(50,100);        
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel...
        LightValue[i*3] = random(240,255); // 250
        LightValue[i*3+1] = random(30,60); // 50
        LightValue[i*3+2] = 0;
        }
      // Switch some lights out
      byte LightsOff  = random(0,6); 
      for(int i=0; i<LightsOff; i++) 
        { 
        byte Selected = random(NUMPIXELS);
        LightValue[Selected*3] = 0;
        LightValue[Selected*3+1] = 0;
        LightValue[Selected*3+2] = 0; 
        }     
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel... 
       pixels.setPixelColor(i, LightValue[i*3], LightValue[i*3+1], LightValue[i*3+2]); 
        }
      noInterrupts();   
      pixels.show();   // Send the updated pixel colors to the hardware.
      interrupts();
      }
    if (FireSq == 4)
      {
     interval = random(80);        
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel...
        LightValue[i*3] = 250;  //random(240,255); // 250
        LightValue[i*3+1] =  50;//random(30,60); // 50
        LightValue[i*3+2] = 0;
        }
      // Switch some lights out if Chance Hit

      byte ChanceforLightsOff  = random(0,40);
      if (ChanceforLightsOff > 35)
        {
        byte LightsOff  = random(5); 
        for(int i=0; i<LightsOff; i++) 
          { 
          byte Selected = random(NUMPIXELS);
          LightValue[Selected*3] = 0;
          LightValue[Selected*3+1] = 0;
          LightValue[Selected*3+2] = 0; 
          }
        }            
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel... 
       pixels.setPixelColor(i, LightValue[i*3], LightValue[i*3+1], LightValue[i*3+2]); 
        }
      noInterrupts();   
      pixels.show();   // Send the updated pixel colors to the hardware.
      interrupts();
      }    
    if (FireSq == 5)
      {
     interval = random(150,200);        
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
       pixels.setPixelColor(i, LightValue[i*3], LightValue[i*3+1], LightValue[i*3+2]); 
        }
      noInterrupts();   
      pixels.show();   // Send the updated pixel colors to the hardware.
      interrupts();
      }
    if (FireSq == 6)
      {
     interval = random(80);        
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel...
        LightValue[i*3] = random(240,255); // 250
        LightValue[i*3+1] = random(40,60); // 50
        LightValue[i*3+2] = 0;
        }
      // Switch some lights out if Chance Hit
      byte ChanceforLightsOff  = random(0,40);
      if (ChanceforLightsOff > 35)
        {
        byte LightsOff  = random(5); 
        for(int i=0; i<LightsOff; i++) 
          { 
          byte Selected = random(NUMPIXELS);
          LightValue[Selected*3] = 0;
          LightValue[Selected*3+1] = 0;
          LightValue[Selected*3+2] = 0; 
          }
        }            
      for(int i=0; i<NUMPIXELS; i++) 
        { // For each pixel... 
       pixels.setPixelColor(i, LightValue[i*3], LightValue[i*3+1], LightValue[i*3+2]); 
        }
      noInterrupts();   
      pixels.show();   // Send the updated pixel colors to the hardware.
      interrupts();
      }         
    }
  else
    {
    if (!(FireOFF))
      { 
      pixels.clear();
      noInterrupts();
      pixels.show();   // Send the updated pixel colors to the hardware.
      interrupts();
      FireOFF = true;
      }
    }   
  }
 }

long ReceiveIrCommand ()
{
  long result = 0;
  if (irrecv.decode(&results)) 
    {
    result = results.value;
    irrecv.resume(); // Receive the next value 
    return result;
    }
  return 0 ;    
}

void IRCommandProcessor (long IrCommand)
  { 
   if (IRCode == OLDIRCode) { TimerlastTime=millis();}              //Some stuff about debouncing IR Remote
   if (millis()-TimerlastTime >=300) { OLDIRCode = 0 ;}           //Some stuff about debouncing IR Remote   
   if ((IRCode < -1) & (IRCode != OLDIRCode) & (IRCode > -600000000) & (IRCode < -500000000))  // Valid IR Signal Received
      {
      OLDIRCode = IRCode;                                           //Some stuff about debouncing IR Remote
      switch (IRCode) 
          {
          case -522182433:        // In my case 1  on my TV - Remote
              {
              FireON = !FireON;
              FireSequence = 1;
             }
          break;
          case -522149793:        // In my case 2  on my TV - Remote
              {
              FireON = !FireON;
              FireSequence = 2;
             }
          break;
          case -522166113:        // In my case 3  on my TV - Remote
              {
              FireON = !FireON;
              FireSequence = 3;
             }
          break;
          case -522186513:        // In my case 4  on my TV - Remote
              {
              FireON = !FireON;
              FireSequence = 4;
             }
          break;   
          case -522153873:        // In my case 5  on my TV - Remote
              {
              FireON = !FireON;
              FireSequence = 5;
             }
          break;
          case -522178353:        // In my case 6  on my TV - Remote
              {
              FireON = !FireON;
              FireSequence = 6;
             }
          break;
                   
          default:
          Serial.println(IRCode);
          break;
          }     
      }   
  }

void loop() 
  {
   IRCode = ReceiveIrCommand();
   IRCommandProcessor(IRCode);
   SimulateFire(FireON,FireSequence);   
  }
