#include "driver.h"

driver::driver(int leftForward, int leftBackward, int rightForward, int rightBackward)
{
    lf = leftForward;
    lb = leftBackward;
    rf = rightForward;
    rb = rightBackward;
    pinMode(lf, OUTPUT);
    pinMode(lb, OUTPUT);
    pinMode(rf, OUTPUT);
    pinMode(rb, OUTPUT);
}

void driver::forward()
{
    analogWrite(lf, lsp);
    digitalWrite(lb, LOW);
    analogWrite(rf, rsp);
    digitalWrite(rb, LOW);
    direction = 0;
}

void driver::backward()
{
    digitalWrite(lf, LOW);
    analogWrite(lb, lsp);
    digitalWrite(rf, LOW);
    analogWrite(rb, rsp);
    direction = 1;
}

void driver::left()
{
    analogWrite(lf, lsp);
    digitalWrite(lb, LOW);
    digitalWrite(rf, LOW);
    analogWrite(rb, rsp);
    direction = 2;
}

void driver::right()
{
    digitalWrite(lf, LOW);
    analogWrite(lb, lsp);
    analogWrite(rf, rsp);
    digitalWrite(rb, LOW);
    direction = 3;
}

void driver::stop()
{
    digitalWrite(lf, LOW);
    digitalWrite(lb, LOW);
    digitalWrite(rf, LOW);
    digitalWrite(rb, LOW);
}

void driver::setSpeed(int speedl, int speedr)
{
    lsp = speedl;
    rsp = speedr;
    switch (direction)
    {
    case 0:
        forward();
        break;
    case 1:
        backward();
        break;
    case 2:
        left();
        break;
    case 3:
        right();
        break;
    }
}