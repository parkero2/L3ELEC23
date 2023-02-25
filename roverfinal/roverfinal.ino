#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LCD_I2C.h>
#include "driver.h"

// Motor config
int leftForward = 2, leftBackward = 3, rightForward = 9, rightBackward = 10;

// Object initialisations
LCD_I2C lcd(0x27); // set the LCD address to 0x27 (39)
TinyGPSPlus gps;
SoftwareSerial ss(4, 5); // RX, TX

void setup()
{
    pinMode(leftForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(rightBackward, OUTPUT);

    // Initialisations

    Serial.begin(115200); // To allow the GPS buffer to be cleared faster than it is refresh

    ss.begin(9600); // GPS

    lcd.begin(); // initialize the lcd
    lcd.backlight();
    lcd.print("Hello, world!");
}

void awaitGPS()
{
    while (ss.available() > 0)
    {
        if (gps.encode(ss.read()))
        {
            break;
        }
    }
}

void loop()
{
    // Update GPS location
    awaitGPS();
}