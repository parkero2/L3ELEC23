#include <SPI.h>
#include <Wire.h>
#include "RF24.h"
#include "printf.h"
RF24 SendRadio(9, 10);

int data[6] = {200, 150, 0, 230};
// lx = 1
// ly = 2
// rx = 3
// ry = 4

void WriteData()
{
    SendRadio.openWritingPipe(0xF0F0F0F066); // Sends data on this 40-bit address
    for (int i = 0; i < sizeof(data); i++)
    {
        SendRadio.write(, sizeof(data[i]));
        Serial.print("WriteData");
        Serial.print(".........");
        Serial.println(data[i]);
        delay(200);
    }
    Serial.print("WriteData");
    Serial.print(".........");
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    printf_begin();
    Serial.println(F("LGT RF-NANO v2.0 Send Test"));
    pinMode(2, INPUT_PULLUP);

    //
    // Setup and configure rf radio
    //
    // Get into standby mode

    SendRadio.begin();
    SendRadio.setAddressWidth(5);
    SendRadio.openWritingPipe(0xF0F0F0F066LL);
    SendRadio.setChannel(115);         // 115 band above WIFI signals
    SendRadio.setPALevel(RF24_PA_MAX); // MIN power low rage
    SendRadio.setDataRate(RF24_1MBPS); // Minimum speed
    SendRadio.stopListening();         // Stop Receiving and start transminitng
    Serial.print("Send Setup Initialized");
    SendRadio.printDetails();
    delay(500);
}

void loop()
{
    WriteData();
    delay(10);
}