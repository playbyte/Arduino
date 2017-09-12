
/* ##################   TiraLED_WS2812B  ####################
*  Filename:    LED_Ej1_lightsaber.ino
*  Descripción: Efecto Sable Laser ON-OFF
*  Autor:       Jose Mª Morales
*  Revisión:    05-01-2017
*  Probado:     ARDUINO UNO r3 - IDE 1.6.13 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
*/
#include "FastLED.h"

#define DATA_PIN 6      // usamos este pin del ARDUINO
#define NUM_LEDS 60     // Tira de LEDs de 1m con 60leds/m
#define LED_TYPE  WS2812B
#define COLOR_ORDER GRB // Depende del fabricante
#define BRIGHTNESS  128
CRGB leds[NUM_LEDS];    // array con el estado de los LED

#define COLOR_LIGHT Magenta


void setup() {
  delay(2000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );

pwrOn();    // Enciende 
}

void loop() {

  latido();
fill_solid(leds, NUM_LEDS, CRGB::White);
      FastLED.show();
   delay(10);   
fill_solid(leds, NUM_LEDS, CRGB::COLOR_LIGHT);
      FastLED.show();
//pwrOff();
//     delay(3000);      
}


void pwrOn() {
   for(int i = 0; i < NUM_LEDS; i++) {
      // Turn our current led on to white, then show the leds
      leds[i] = CRGB::COLOR_LIGHT;
 delay(5);
      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

   }
  
}


void pwrOff() {
   for(int whiteLed = NUM_LEDS; whiteLed >=0 ; whiteLed = whiteLed - 1) {

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;      // Show the leds (only one of which is set to white, from above)
       delay(6);
      FastLED.show();

   }
  
}

void latido() {

      for(int brillo = 128; brillo <=255 ; brillo=brillo+2) {
   FastLED.setBrightness(brillo);
      delay(10);
        FastLED.show(); 
      }

      for(int brillo = 255; brillo >=128 ; brillo=brillo-2) {
   FastLED.setBrightness(brillo);
      delay(10);
        FastLED.show(); 
      }

}
