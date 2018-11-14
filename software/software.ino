#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const byte pin = 2;					//Neopixel pin
const byte numpixels = 152;			//Number of pixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numpixels, pin, NEO_RGB + NEO_KHZ800);		//set up strip

byte pixelarray[numpixels][3];		//Array to hold status of every pixel


void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() 
{

  //Sets first pixel to current RGB values
  pixelarray[0][0] = analogRead(0)/4;		//Red is A0/4 (0-255 output, 0-1023 input)
  pixelarray[0][1] = analogRead(1)/4;		//Green is A1/4
  pixelarray[0][2] = analogRead(2)/4;		//Blue is A2/4
  
 //Goes through our bigass array and assigns values to every pixel as per array
 for(byte i=0;i<numpixels;i++)
  {
    pixels.setPixelColor(i, pixels.Color(pixelarray[i][0],pixelarray[i][1],pixelarray[i][2]));
  }
  
  pixels.show(); // This sends the updated pixel color to the hardware.

  //shifts values in array up by one, leaving space for new values at start of strip
  for(byte i=0;i<3;i++)
  {
    for(byte j = numpixels-1; j>0; j--)
    {
      pixelarray[j][i] = pixelarray[j-1][i];
    }
  }
  
  delay(10);	//Delay some time, otherwise things happen too fast to see
}
