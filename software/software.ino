#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


/////////////////////////Number of pixels in your strip
const byte numpixels = 152; 

const byte clipping = 2;
const byte button = 3;        //button pin
const byte pin = 6;           //Neopixel pin

boolean buttonState;          //current state of button
boolean lastButtonState;      //previous state of button

byte red;                     //red pixel value
byte green;                   //green...
int blue;                    //etc
byte programme;               //current programme type (0 = block, 1 = chasing lights)

byte pixelarray[numpixels][3];    //2D Array to hold status of every pixel

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numpixels, pin, NEO_RGB + NEO_KHZ800);		//set up strip


//Table for gamma correction, this adjusts brightness values for more visual contrast
const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void setup() {
  Serial.begin(9600);
  pinMode(button,INPUT);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() 
{

  //change programme type on button press (rising edge trigger only)
  buttonState = digitalRead(button);
  if (buttonState != lastButtonState) 
  {
    if (buttonState == HIGH) 
    {
      programme++;
      if(programme > 4) //Set highest programme number here
      {
        programme = 0;
      }
    }
    delay(50);
  }
  lastButtonState = buttonState;

  //Saves current RGB values to memory for use by routines
  red = pgm_read_byte(&gamma8[analogRead(0)/4]);    //Red is A0/4 (0-255 output, 0-1023 input)
  green = pgm_read_byte(&gamma8[analogRead(1)/4]);   //Green is A1/4
  blue = pgm_read_byte(&gamma8[analogRead(2)/4]);   //Green is A1/4

//  Serial.println(red);
//  Serial.println(green);
//  Serial.println(blue);
//  Serial.println(" ");
  
  if((red || green || blue) > 250)
  {
    digitalWrite(clipping,HIGH);
  }
  else
  {
    digitalWrite(clipping,LOW);
  }

  if(programme == 0) //dimming chasing lights
    {
      //First pixel in the chain is set to our latest colours
      pixelarray[0][0] = red;
      pixelarray[0][1] = green;
      pixelarray[0][2] = blue;
      
     //Goes through our bigass array and assigns values to every pixel as per the contents of the array
     for(byte i=0;i<numpixels;i++)
      {
        pixels.setPixelColor(i, pixels.Color(pixelarray[i][0],pixelarray[i][1],pixelarray[i][2]));
      }
      
      pixels.show(); // This sends the updated pixel color to the hardware.
    
      //shifts values in array up by one, leaving space for new values at start of strip. This gives our "chasing" effect
      for(byte i=0;i<3;i++)
      {
        for(byte j = numpixels-1; j>0; j--)
        {
          if((pixelarray[j-1][i]) > 15)
          {
            pixelarray[j][i] = pixelarray[j-1][i] -15;
          }
          else if((pixelarray[j-1][i]) > 2)
          {
            pixelarray[j][i] = pixelarray[j-1][i] -2;
          }
          else
          {
            pixelarray[j][i] = pixelarray[j-1][i];
          }
        }
      }
    
    delay(10);  //Delay some time, otherwise things happen too fast to see
  }

  if(programme == 1) //chasing lights
  {
    //First pixel in the chain is set to our latest colours
    pixelarray[0][0] = red;
    pixelarray[0][1] = green;
    pixelarray[0][2] = blue;
    
   //Goes through our bigass array and assigns values to every pixel as per the contents of the array
   for(byte i=0;i<numpixels;i++)
    {
      pixels.setPixelColor(i, pixels.Color(pixelarray[i][0],pixelarray[i][1],pixelarray[i][2]));
    }
    
    pixels.show(); // This sends the updated pixel color to the hardware.
  
    //shifts values in array up by one, leaving space for new values at start of strip. This gives our "chasing" effect
    for(byte i=0;i<3;i++)
    {
      for(byte j = numpixels-1; j>0; j--)
      {
        pixelarray[j][i] = pixelarray[j-1][i];
      }
    }
    
    delay(10);  //Delay some time, otherwise things happen too fast to see
  }

  if(programme == 2) //block update
  {
    
    //Assigns every pixel value to our RGB values
    for(byte i=0; i<numpixels; i++)
    {
      pixels.setPixelColor(i, pixels.Color(red,green,blue));
    }

    pixels.show(); // This sends the updated pixel color to the hardware.
  }

  if(programme == 3) //random dimming chase (no audio control)
  {
      //First pixel in the chain is set to our latest colours
      pixelarray[0][0] = random(255);
      pixelarray[0][1] = random(255);
      pixelarray[0][2] = random(255);
      
     //Goes through our bigass array and assigns values to every pixel as per the contents of the array
     for(byte i=0;i<numpixels;i++)
      {
        pixels.setPixelColor(i, pixels.Color(pixelarray[i][0],pixelarray[i][1],pixelarray[i][2]));
      }
      
      pixels.show(); // This sends the updated pixel color to the hardware.
    
      //shifts values in array up by one, leaving space for new values at start of strip. This gives our "chasing" effect
      for(byte i=0;i<3;i++)
      {
        for(byte j = numpixels-1; j>0; j--)
        {
          if((pixelarray[j-1][i]) > 5)          //reduce intensity 5 after every shift
          {
            pixelarray[j][i] = pixelarray[j-1][i] -5;
          }
          else
          {
            pixelarray[j][i] = pixelarray[j-1][i];
          }
        }
      }
      delay(100);  //Delay some time, otherwise things happen too fast to see
    }

  if(programme == 4)
  {
    
    //Assigns every pixel value to our RGB values
    for(byte i=0; i<numpixels; i++)
    {
      pixels.setPixelColor(i, pixels.Color(random(255),random(255),random(255)));
    }

    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(100);
  }
    
}
