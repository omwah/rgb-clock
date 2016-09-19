/*
 */

#include "application.h"
#include "neopixel.h"
#include "animation.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

#define TIME_ZONE -7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
Animation animation = Animation(&strip);

// Define colors for time telling
uint32_t off = strip.Color(0, 0, 0);

// Make hour and minute colors "breathe"
Breathe hour_breath = Breathe(off, strip.Color(255, 0, 0), 43);
Breathe minute_breath = Breathe(off, strip.Color(0, 255, 0), 4.3);
Breathe second_breath = Breathe(off, strip.Color(0, 0, 255), 10);

// Last indexes so we can turn off the old pixel
int last_hour_idx = 0;
int last_minute_idx = 0;
int last_second_idx = 0;

// Signatures
void display_clock();

void setup()
{
    Time.zone(TIME_ZONE);
    
    strip.begin();
    //strip.setBrightness(64);
    strip.show(); // Initialize all pixels to 'off'

    animation.rainbow_cycle(10);
}

void loop()
{
    display_clock();
}

void display_clock()
{
    // Get the current time, broken out into parts
    int curr_hour_idx = Time.hourFormat12() * 5 % 60;
    int curr_minute_idx = Time.minute();
    int curr_second_idx = Time.second();

    // Produce a little animation when minutes advance
    if (curr_minute_idx != last_minute_idx && curr_minute_idx == 0) {
        animation.rainbow_cycle(10);
    } else if (curr_second_idx != last_second_idx && curr_second_idx == 0) {
        strip.setPixelColor(last_second_idx, off);
        animation.rainbow_wipe(curr_minute_idx, 20);
        delay(20);
        animation.set_all(off);
    }

    // Clear the display
    animation.set_all(off);

    // Set hand colors
    strip.setPixelColor(curr_minute_idx, minute_breath.color());
    strip.setPixelColor(curr_hour_idx, hour_breath.color());
    strip.setPixelColor(curr_second_idx, second_breath.color());

    strip.show();

    // Update indexes
    last_minute_idx = curr_minute_idx;
    last_hour_idx = curr_hour_idx;
    last_second_idx = curr_second_idx;
 
}
