#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LCD_I2C.h>
#include "driver.h"
#include <QMC5883LCompass.h>

/*REFERENCES
 * https://github.com/mprograms/QMC5883LCompass/blob/master/examples/bearing/bearing.ino
 * https://github.com/mprograms/QMC5883LCompass/blob/master/examples/calibration/calibration.ino
 */

// Motor config
int leftForward = 2, leftBackward = 3, rightForward = 9, rightBackward = 10;

// Object initialisations
LCD_I2C lcd(0x27); // set the LCD address to 0x27 (39)
TinyGPSPlus gps;
SoftwareSerial ss(4, 5); // RX, TX
driver driver(leftForward, leftBackward, rightForward, rightBackward);
QMC5883LCompass compass;

void setup()
{
    // Initialisations

    Serial.begin(115200); // To allow the GPS buffer to be cleared faster than it is refresh

    ss.begin(9600); // GPS

    lcd.begin(); // initialize the lcd
    lcd.backlight();
    lcd.print("Hello, world!");

    compass.init();
}

char getMagnetomiter()
{
    byte az = compass.getAzimuth();
    byte be = compass.getBearing(az);
    return be;
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
    awaitGPS(); // In a perfect world, this would be ran in a separate threaddueto the time factor, but most Arduino boards don't support multithreading.
}