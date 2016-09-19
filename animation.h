#ifndef RGB_ANIMATION_H
#define RGB_ANIMATION_H

class Breathe {
public:
    Breathe(uint32_t inp_color_min, uint32_t inp_color_max, uint8_t delay);
    uint32_t color();
private:
    unsigned long last_change_time;
    uint8_t wait_time;
    uint32_t color_value;
    uint32_t color_min;
    uint32_t color_max;
    uint8_t color_index;
    uint8_t direction;
};

class Animation {
public:
    Animation(Adafruit_NeoPixel *Strip) : strip(Strip) {};

    uint32_t Wheel(byte WheelPos);
    void set_all(uint32_t c);
    uint32_t rainbow_color(uint16_t offset, uint16_t index);
    void rainbow_wipe(uint8_t offet, uint8_t wait);

    void rainbow(uint8_t wait);
    void rainbow_cycle(uint8_t wait);
private:
    Adafruit_NeoPixel *strip;
};

#endif
