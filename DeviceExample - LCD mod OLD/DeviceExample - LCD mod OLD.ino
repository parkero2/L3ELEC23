#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <LCD_I2C.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

LCD_I2C lcd(0x27, 16, 4);
// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

//Buffer vals
uint8_t hr;
uint8_t mn;
uint8_t sc;
double lon;
double lat;
    
//Real vals
uint8_t rhr;
uint8_t rmn;
uint8_t rsc;
double rlon;
double rlat;
    
byte refresh[] = {
  0x04,
  0x1E,
  0x15,
  0x11,
  0x11,
  0x15,
  0x0F,
  0x04
};

byte locationn[] = {
  0x00,
  0x0E,
  0x11,
  0x15,
  0x11,
  0x0A,
  0x04,
  0x00
};

byte timee[] = {
  0x0E,
  0x11,
  0x15,
  0x15,
  0x17,
  0x11,
  0x11,
  0x0E
};

byte datee[] = {
  0x00,
  0x00,
  0x1F,
  0x1F,
  0x11,
  0x11,
  0x1F,
  0x00
};

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
  Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();

  lcd.createChar(0, refresh);
  lcd.createChar(1, datee);
  lcd.createChar(2, timee);
  lcd.createChar(3, locationn);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    lcd.setCursor(16, 0);
    lcd.print("!");
    delay(500);
  }
}

void displayInfo()
{
  lcd.clear();

    lcd.setCursor(0,1);
    lcd.write(3);
    lcd.print(" ");
  lcd.setCursor(0,0);
    lcd.write(3);
    lcd.print(" ");
  Serial.print(F("Location: ")); 
  //lcd.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    rlon = gps.location.lng();
    rlat = gps.location.lat();

    Serial.print(rlon, 6);
    Serial.print(F(","));
    Serial.print(rlat, 6);
    
    lcd.print(rlat, 6);
  if (!rlat == lat) {        
    lcd.setCursor(15, 0);
    lcd.write(0);
  }    
    lcd.setCursor(0,1);
    lcd.write(3);
    lcd.print(" ");
    lcd.print(rlon, 6);    
  if (!rlon == lon) {        
    lcd.setCursor(15, 1);
    lcd.write(0);
  }  
    lon = rlon;
    lat = rlat;
  }
  else
  {
    Serial.print(F("PENDING"));
    lcd.print(F("PENDING"));
  }

  //Date and time
  Serial.print(F("  Date/Time: "));

    lcd.setCursor(0,2);
    lcd.write(1);
    lcd.print(" ");
  if (gps.date.isValid())
  {    
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
    lcd.print(gps.date.month());
    lcd.print(F("/"));
    lcd.print(gps.date.day());
    lcd.print(F("/"));
    lcd.print(gps.date.year());    
  }
  else
  {
    Serial.print(F("PENDING"));
    lcd.print(F("PENDING"));
  }
  lcd.setCursor(0, 3);
  Serial.print(F(" "));

  //Time
  if (gps.time.isValid())
  {
    rhr = gps.time.hour(); 
    rmn = gps.time.minute();
    rsc = gps.time.second();
    
    lcd.write(2);
    lcd.print(" ");    

    if (rhr < 10) Serial.print(F("0"));
    Serial.print(rhr);
    Serial.print(F(":"));
    lcd.print(rhr);
    lcd.print(F(":"));
    
    if (rmn < 10) Serial.print(F("0"));
    Serial.print(rmn);
    Serial.print(F(":"));
    lcd.print(rmn);
    lcd.print(F(":"));
    
    if (rsc < 10) Serial.print(F("0"));
    Serial.print(rsc);
    Serial.print(F("."));
    lcd.print(rsc);
    lcd.print(F("."));
    
    //Refresh detection
    if ((hr != rhr) || (mn != rmn) || (sc != rsc)) {
      lcd.setCursor(15, 3);
      lcd.write(0);  
    }
    
    /**if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());*/
    hr = rhr;
    mn = rmn;
    sc = rsc;
  }
  else
  {
    Serial.print(F("PENDING"));
    lcd.print(F("PENDING"));
  }

  Serial.println();
  delay(500);
}
