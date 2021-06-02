
#include <FastLED.h>


#define NUM_LEDS 12
#define DATA_PIN 26

CRGBArray<NUM_LEDS> leds;

void setupLeds()
{
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void fire(uint8_t hue, uint8_t brightness)
{
    for (int i = 0; i < NUM_LEDS / 2; i++)
    {
        leds.fadeToBlackBy(40);

        leds[i] = CHSV(hue, 255, brightness);

        leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
        FastLED.delay(33);
    }
}