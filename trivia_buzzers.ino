#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define LED_COUNT 60
#define SOUND 13

#define L_P1  3
#define L_P2  4
#define L_P3  5
#define L_P4  6
#define R_P1  7
#define R_P2  8
#define R_P3  9
#define R_P4  10
#define CTRL  11

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const uint32_t  P1_COLOR = strip.Color(255,0,0);
const uint32_t  P2_COLOR = strip.Color(0,255,0);
const uint32_t  P3_COLOR = strip.Color(0,0,255);
const uint32_t  P4_COLOR = strip.Color(255,255,255);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP

  pinMode(L_P1,INPUT_PULLUP);
  pinMode(L_P2,INPUT_PULLUP);
  pinMode(L_P3,INPUT_PULLUP);
  pinMode(L_P4,INPUT_PULLUP);
  pinMode(R_P1,INPUT_PULLUP);
  pinMode(R_P2,INPUT_PULLUP);
  pinMode(R_P3,INPUT_PULLUP);
  pinMode(R_P4,INPUT_PULLUP);
  pinMode(CTRL,INPUT_PULLUP);
}

void loop() {
  int player = idleAnimation(30);
  showColor(player);
}

int idleAnimation(int wait){
  int pressed = CTRL;
  strip.setBrightness(100);
  while (pressed == CTRL){
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i<strip.numPixels(); i++) {
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show(); // Update strip with new contents
    
      for(int i=0; i<wait; i++){
        if( digitalRead(L_P1) == LOW ){
          pressed = L_P1;
          goto end;
        } else if ( digitalRead(L_P2)== LOW ){
          pressed = L_P2;
          goto end;
        } else if ( digitalRead(L_P3)== LOW ){
          pressed = L_P3;
          goto end;
        } else if ( digitalRead(L_P4)== LOW ){
          pressed = L_P4;
          goto end;
        } else if ( digitalRead(R_P1)== LOW ){
          pressed = R_P1;
          goto end;
        } else if ( digitalRead(R_P2)== LOW ){
          pressed = R_P2;
          goto end;
        } else if ( digitalRead(R_P3)== LOW ){
          pressed = R_P3;
          goto end;
        } else if ( digitalRead(R_P4)== LOW ){
          pressed = R_P4;
          goto end;
        } else delay(1);
      }
    }
  }
  end: return pressed;
}

void showColor(int player){
  uint32_t color;
  int first;
  switch(player){
    case L_P1:
      color = P1_COLOR;
      first = 0;
      break;
    case L_P2:
      color = P2_COLOR;
      first = 0;
      break;
    case L_P3:
      color = P3_COLOR;
      first = 0;
      break;
    case L_P4:
      color = P4_COLOR;
      first = 0;
      break;
    case R_P1:
      color = P1_COLOR;
      first = strip.numPixels()/2;
      break;
    case R_P2:
      color = P2_COLOR;
      first = strip.numPixels()/2;
      break;
    case R_P3:
      color = P3_COLOR;
      first = strip.numPixels()/2;
      break;
    case R_P4:
      color = P4_COLOR;
      first = strip.numPixels()/2;
      break;
  }

  strip.clear();
  strip.setBrightness(255);
  strip.show();
  delay(100);
  tone(SOUND, 880, 100);
  strip.fill(color,first,strip.numPixels()/2);
  strip.show();
  delay(100);
  strip.clear();
  strip.show();
  delay(100);
  tone(SOUND, 880, 100);
  strip.fill(color,first,strip.numPixels()/2);
  strip.show();
  delay(100);
  strip.clear();
  strip.show();
  delay(100);
  tone(SOUND, 880, 100);
  strip.fill(color,first,strip.numPixels()/2);
  strip.show();

  while( digitalRead(CTRL) == HIGH )
    delay(5);
}
