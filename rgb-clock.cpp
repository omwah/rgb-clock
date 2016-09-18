/*
 */

#include "application.h"
#include "neopixel.h"
#include "animation.h"

SYSTEM_MODE(AUTOMATIC);
Adafruit_NeoPixel *strip
// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

#define TIME_ZONE -7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
Animation animation = Animation(&strip);

// Define colors for time telling
uint32_t off = strip.Color(0, 0, 0);
uint32_t hour_color = strip.Color(255, 0, 0);
uint32_t minute_color = strip.Color(0, 255, 0);
uint32_t second_color = strip.Color(255, 0, 255);

// Last indexes so we can turn off the old pixel
int last_hour_idx = 0;
int last_minute_idx = 0;
int last_second_idx = 0;

void setup() {
    Time.zone(TIME_ZONE);
    
    strip.begin();
    strip.setBrightness(64);
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    int curr_hour_idx = Time.hourFormat12() * 5 % 60;
    strip.setPixelColor(last_hour_idx, off);
    strip.setPixelColor(curr_hour_idx, hour_color);
    last_hour_idx = curr_hour_idx;

    int curr_minute_idx = Time.minute();
    strip.setPixelColor(last_minute_idx, off);
    strip.setPixelColor(curr_minute_idx, minute_color);
    last_minute_idx = curr_minute_idx;

    int curr_second_idx = Time.second();
    strip.setPixelColor(last_second_idx, off);
    strip.setPixelColor(curr_second_idx, second_color);
    last_second_idx = curr_second_idx;
    
    strip.show();
}



