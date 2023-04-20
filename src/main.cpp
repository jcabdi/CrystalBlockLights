#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(3, 4);

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN             2
#define NUMPIXELS       64
#define MAX_BRIGHTNESS  100
#define DELAYVAL        50

struct rgb {
    int r;
    int g;
    int b;
};



Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void show_palette(int r, int g, int b) {
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
    delay(DELAYVAL);
  }
}

rgb set_palette(char _data_read) {
  Serial.print("user entered ");
  Serial.println(_data_read);
  switch (_data_read) {
    case 'r': //red
    return {255, 0, 0};
    break;
    case 'g': //green
    return {0, 255, 0};
    break;
    case 'b': //blue
    return {0, 0, 255};
    break;
    case 'y': //yellow
    return {255, 255, 0};
    break;
    case 'o': //orange
    return {255, 165, 0};
    break;
    case 'c': //cyan
    return {0, 255, 255};
    break;
    case 'm': //magenta
    return {255, 0, 255};
    break;
    case 'w': //magenta
    return {255, 255, 255};
    break;
    default:
    return {0, 0, 0};
    break;
    }
}

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(9600);
  Serial.println("Starting up");
  delay(500);
  BT.begin(9600);
  BT.println("Enter data...");
  pixels.begin();
  pixels.clear();
  pixels.show();
  pixels.setBrightness(MAX_BRIGHTNESS);
}

void loop() {
  if (BT.available()) {
    char EnteredData = BT.read();
    struct rgb asColors;
    asColors = set_palette(EnteredData);
  show_palette(asColors.r, asColors.g, asColors.b);
  }
}
