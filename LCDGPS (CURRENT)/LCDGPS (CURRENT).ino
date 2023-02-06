//Libary includes
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <LCD_I2C.h>

/**
*Depending on your use case, you will need to change the following declarations to suit your hardware
* RXPin
* TXPin
* GPSBaud
* LCD address
*/

//RX and TX declarations
//RX = 3 TX = 4
static const int RXPin = 3, TXPin = 4;

//Instance declarations
LCD_I2C lcd(0x27, 16, 4);
TinyGPSPlus gps; //Delcare a new instance of a TinyGPSPlus object
SoftwareSerial ss(RXPin, TXPin); //Pins the GPS will be communicating on.

const uint32_t GPSBaud = 9600; //The baud rate at which the GPS module and microcontroller communicates

//Custom character declarations
//Given _mark suffixes to avoid possible conflicts with existing keywords
byte refresh[] = {0x04, 0x1E, 0x15, 0x11, 0x11, 0x15, 0x0F, 0x04};
byte loc_mark[] = {0x00, 0x0E, 0x11, 0x15, 0x11, 0x0A, 0x04, 0x00};
byte clock_mark[] = {0x0E, 0x11, 0x15, 0x15, 0x17, 0x11, 0x11, 0x0E};
byte date_mark[] = {0x00, 0x00, 0x1F, 0x1F, 0x11, 0x11, 0x1F, 0x00};
byte warning[] = {0x00, 0x0A, 0x0A, 0x0A, 0x0A, 0x00, 0x0A, 0x00};

//Buffer values used for retaining older data, to be compared with what is being read most currently 
uint8_t hr, mn, sc, dy, mnth, yr;
double lon, lat;

//A 'print to serial flag' (for debugging)
const bool SerialDebug = true;

char linesToWrite[4];
int symbToWrite[4];

int sybForLines[4] = {1, 1, 3, 2};

void displayRefresh () {
    //Fancy display refresh stuff
    for (int line = 0; line < sizeof(linesToWrite); line++){
        lcd.clear();
        lcd.setCursor(0, line);
        lcd.write(sybForLines[line]);
        lcd.print(" " + linesToWrite[line]);
        lcd.setCursor(18, line);
        lcd.write(symbToWrite[line]);
    }
}

void setup() {
  if (SerialDebug) Serial.begin(9600); Serial.println("GPS thing");
  
  ss.begin(GPSBaud); //Software serial
  lcd.backlight();
  lcd.begin();

  //LCD character creation
  lcd.createChar(0, refresh);
  lcd.createChar(1, loc_mark);
  lcd.createChar(2, date_mark);
  lcd.createChar(3, clock_mark);
  lcd.createChar(4, warning);
}

void loop() {
  //displayRefresh();
  while (ss.available() > 0) {
    if (gps.encode(ss.read())){
      //Location
      if (gps.location.isValid()) {
        lon = gps.location.lng(), lat = gps.location.lng();
        //Check if location updated
        symbToWrite[0] = linesToWrite[0] == lon ? 0 : NULL;
        symbToWrite[1] = linesToWrite[1] == lat ? 0 : NULL;

        linesToWrite[0] = lon, linesToWrite[1] = lat;
      }
      //Date
      if (gps.date.isValid()) {
        dy = gps.date.day(), mnth = gps.date.month(), yr = gps.date.year();
      
        //Compiler (or me) is being special 
        char concat1 = dy + "/" + mnth;
        char concat2 = "/" + yr;
        //Check if location updated
        symbToWrite[3] = linesToWrite[3] == (concat1 + concat2) ? 0 : NULL;
        linesToWrite[3] = (concat1 + concat2);
      }        
      //time
      if (gps.time.isValid()) {
        hr = gps.time.hour(), mn = gps.time.minute(), sc = gps.time.second();
      
        //Compiler (or me) being special
        char concat1 =  hr + ":" + mn;
        char concat2 = ":" + sc;
        //Check if location updated
        symbToWrite[2] = linesToWrite[2] == (concat1 + concat2) ? 0 : NULL;
        linesToWrite[2] = (concat1 + concat2);
      }      
    }
    for (int i = 0; i < sizeof(symbToWrite); i++) {
      if (symbToWrite[i] == NULL) return; //if there is a refresh symbol,this is false so will not ignore the rest of the loop
      displayRefresh();
      break; //If the display is being refreshed, there is no point in checking new data.
    }
  }  
}
