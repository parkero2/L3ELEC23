#ifndef driver_h
#define driver_h

#include <Arduino.h>

class driver
{
private:
    int leftForward, leftBackward, rightForward, rightBackward;
    int lf, lb, rf, rb;
    int lsp, rsp;
    int direction; // 0 = forward, 1 = backward, 2 = left, 3 = right

public:
    driver(int leftForward, int leftBackward, int rightForward, int rightBackward);
    void forward();
    void backward();
    void left();
    void right();
    void stop();
    void setSpeed(int speedl, int speedr);
};

#endif