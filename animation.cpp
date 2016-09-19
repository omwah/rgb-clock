/*
 * Animations to use with the clock
 */

#include "neopixel.h"
#include "animation.h"

Breathe::Breathe(uint32_t inp_color_min, uint32_t inp_color_max, uint8_t delay)
{
    last_change_time = millis();
    wait_time = delay;

    color_min = inp_color_min;
    color_max = inp_color_max;

    color_value = color_max;

    uint8_t max_r = (uint8_t)(color_max >> 16);
    uint8_t max_g = (uint8_t)(color_max >> 8);
    uint8_t max_b = (uint8_t)(color_max);

    color_index = max(max_r, max(max_g, max_b));
    direction = -1;
}

uint32_t Breathe::color()
{
    if (millis() - last_change_time > wait_time) {
        uint8_t max_r = (uint8_t)(color_max >> 16);
        uint8_t max_g = (uint8_t)(color_max >> 8);
        uint8_t max_b = (uint8_t)(color_max);

        uint8_t min_r = (uint8_t)(color_min >> 16);
        uint8_t min_g = (uint8_t)(color_min >> 8);
        uint8_t min_b = (uint8_t)(color_min);

        color_index += direction;

        uint8_t max_index = max(max_r, max(max_g, max_b));
        uint8_t min_index = min(min_r, min(min_g, min_b));

        // Make sure to go the other way next time
        if (color_index >= max_index) {
            direction = -1;
        } else if(color_index <= min_index) {
            direction = 1;
        }
 
        color_value = 
            ((uint32_t) max(min(color_index, max_r), min_r) << 16) |
            ((uint32_t) max(min(color_index, max_g), min_g) <<  8) |
            max(min(color_index, max_b), min_b);

        last_change_time = millis();
    }
    return color_value;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Animation::Wheel(byte WheelPos)
{
    if(WheelPos < 85) {
        return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if(WheelPos < 170) {
        WheelPos -= 85;
        return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

// Set all pixels in the strip to a solid color,
// Does not issue a show
void Animation::set_all(uint32_t c)
{
    uint16_t i;

    for(i = 0; i < strip->numPixels(); i++) {
        strip->setPixelColor(i, c);
    }
}

uint32_t Animation::rainbow_color(uint16_t offset, uint16_t index)
{
    return Wheel(((index + offset) * 256 / strip->numPixels()) % 256);
}

void Animation::rainbow_wipe(uint8_t offset, uint8_t wait)
{
    for(uint16_t i = 0; i < strip->numPixels(); i++) {
        strip->setPixelColor(i, rainbow_color(offset, i));
        strip->show();
        delay(wait);
        strip->setPixelColor(i, 0);
    }
}

// Demo style animations

void Animation::rainbow(uint8_t wait)
{
    uint16_t i, j;

    for(j = 0; j < 256; j++) {
        for(i = 0; i < strip->numPixels(); i++) {
            strip->setPixelColor(i, Wheel((i + j) & 255));
        }

        strip->show();
        delay(wait);
    }
}

// Slightly different, this makes the rainbow equally distributed throughout, then wait (ms)
void Animation::rainbow_cycle(uint8_t wait)
{
    uint16_t i, j;

    for(j = 0; j < 256; j++) { // 1 cycle of all colors on wheel
        for(i = 0; i < strip->numPixels(); i++) {
            strip->setPixelColor(i, Wheel(((i * 256 / strip->numPixels()) + j) & 255));
        }

        strip->show();
        delay(wait);
    }
}


