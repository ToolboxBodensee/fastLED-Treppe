#include <FastLED.h>

#define LED_PIN  6

#define COLOR_ORDER GRB
#define CHIPSET     WS2811

#define BRIGHTNESS 255

// Breite und Höhe
#define kMatrixWidth 11; //----------.Breite
#define kMatrixHeight 17; //----------Höhe

#define NUM_LEDS kMatrixWidth*kMatrixHeight;

//Button Variablen
#define buttonPin1 10;//Switch Oben und Mitte 
#define buttonPin2 11; //Switch unten und Mitte
#define buttonPin3 9; //Rot unten
#define buttonPin4 8; // Rot oben

//Zeit Variablen
#define xTime 10; //---------------------------Intervall 1
#define onewayTime 42; //----------------------Intervall 2

//------------------------------------------------------

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);


//--------------------------------SETUP ------------------------
void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Hello World!");
}


uint16_t XYsafe( const uint8_t x, const uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}


//----------------------------------LOOP -------------------
void loop() 
{ 
  static uint8_t y;
  static uint8_t x;
  static uint8_t gegenstrecke = kMatrixHeight-1;
  
  //Wenn Schalter oben ist, starte Animation.
  if (digitalRead(buttonPin1) == HIGH) {
    //Wenn der Schalter in der mitte ist, aktiviere debugfunktion
    if (digitalRead(buttonPin2) == HIGH) {
      debug(y, x, gegenstrecke);
    }
    animation1(y, x, gegenstrecke);
  } 
  //LEDs ausschalten, wenn der switch unten ist (Pinkontakt 2+3)
  else if ((digitalRead(buttonPin1) == LOW) && (digitalRead(buttonPin2) == HIGH)) {
    powerOff();
  }
}




//-------------------------------Animationsfunktion ------------
void animation1(uint8_t& y, uint8_t& x, uint8_t& gegenstrecke) {
  static uint8_t xA;
  static uint8_t xB;
  static unsigned long xMillis;
  static long onewayMillis;
  static uint8_t hue;
  
  unsigned long currentMillis = millis();
  if (currentMillis - xMillis > xTime) {
    xMillis = currentMillis;
    ++x;
    if (x > 5) {
      x = 0;
      ++y;
      //hue++;
      fadeToBlackBy(leds, NUM_LEDS, 20);
      if (y > kMatrixHeight-1) {
        y = 0;
      }
    }
    xA = 5 - x;
    xB = 5 + x;
  }
  if (currentMillis - onewayMillis > onewayTime) {
    onewayMillis = currentMillis;
    if (gegenstrecke == 0) {
      gegenstrecke = kMatrixHeight-1;
    } else {
      --gegenstrecke;
    }
  }
    
  ++hue;
  leds[ XY(xA, y)] = CHSV( hue, 255, 255 );
  leds[ XY(xB, y)] = CHSV( hue, 255, 255 );
  leds[ XY(5, gegenstrecke)] = CHSV( hue, 255, 255 );
  FastLED.show();
}
//----------------------------- Debug Funktion ----------------
void debug(const uint8_t& y, const uint8_t& x, const uint8_t& gegenstrecke) {
  Serial.print(y);
  Serial.print("   ");
  Serial.print(x);
  Serial.print("   ");
  Serial.print(gegenstrecke);
  Serial.print("   ");
  if ((digitalRead(buttonPin1) == HIGH) && (digitalRead(buttonPin2) == LOW)) {
    Serial.print("Oben ");
  }
  if ((digitalRead(buttonPin1) == HIGH) && (digitalRead(buttonPin2) == HIGH)) {
    Serial.print("Mitte ");
  }
  if ((digitalRead(buttonPin1) == LOW) && (digitalRead(buttonPin2) == HIGH)) {
    Serial.print("Unten ");
  }
  if (digitalRead(buttonPin3) == HIGH) {
    Serial.print("Knopf 3");
  }
  if (digitalRead(buttonPin4) == LOW) {
    Serial.print("Knopf 4");
  }
  Serial.println(" ");
}
//----------------------------------Power Off -------------
void powerOff() {
  FastLED.clear();
  FastLED.show();
}

//------------------------ Matrix definitionen ----------

uint16_t XY(const uint8_t x, const uint8_t y) {
  uint16_t returnValue = y * kMatrixWidth;
  
  if( kMatrixSerpentineLayout && y & 0x01) {
    // Odd rows run backwards
    returnValue += kMatrixWidth - 1 - x;
  } else {
    // Even rows run forwards
    returnValue += x;
  }
  return returnValue;
}

//---------------------Example Code ------------------------
/*
void loop()
{
    uint32_t ms = millis();
    int32_t yHueDelta32 = ((int32_t)cos16( ms * (27/1) ) * (350 / kMatrixWidth));
    int32_t xHueDelta32 = ((int32_t)cos16( ms * (39/1) ) * (310 / kMatrixHeight));
    DrawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
    if( ms < 5000 ) {
      FastLED.setBrightness( scale8( BRIGHTNESS, (ms * 256) / 5000));
    } else {
      FastLED.setBrightness(BRIGHTNESS);
    }
    FastLED.show();
}

void DrawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
{
  byte lineStartHue = startHue8;
  for( byte y = 0; y < kMatrixHeight; y++) {
    lineStartHue += yHueDelta8;
    byte pixelHue = lineStartHue;      
    for( byte x = 0; x < kMatrixWidth; x++) {
      pixelHue += xHueDelta8;
      leds[ XY(x, y)]  = CHSV( pixelHue, 255, 255);
    }
  }
}
*/
