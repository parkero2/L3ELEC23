#include <LCD_I2C.h>

bool julian() {
    if (analogRead(A0) > 1000) {
        return true;
    }
    return false;
}

Serial.println(julian());