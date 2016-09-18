#ifndef RGB_ANIMATION_H
#define RGB_ANIMATION_H

class Animation {
public:
    Animation(Adafruit_NeoPixel *Strip) : strip(Strip) {};
    void colorAll(uint32_t c, uint8_t wait);
    void colorWipe(uint32_t c, uint8_t wait);
    void rainbow(uint8_t wait);
    void rainbowCycle(uint8_t wait);
    uint32_t Wheel(byte WheelPos);
private:
    Adafruit_NeoPixel *strip;
};

#endif
