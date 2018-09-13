#include <Wire.h>
#include "RTClib.h"

#define RTC_OFFSET 20
#define UTC_OFFSET -4   // EDT
//#define UTC_OFFSET -5   // EST

// the digital pins that connect to the LEDs
#define redLEDpin 3
#define greenLEDpin 2

#define PCF8523_ADDRESS       0x68

// Method added 10-Sep-18 by B. Morgan
uint8_t RTC_PCF8523_readOffset() {
  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire.write((byte) 0x0E);
  Wire.endTransmission();

  Wire.requestFrom(PCF8523_ADDRESS, 1);
  uint8_t offset = Wire.read();

  return offset;
}

// Method added 10-Sep-18 by B. Morgan
void RTC_PCF8523_writeOffset(uint8_t mode, int8_t offset) {
  Wire.beginTransmission(PCF8523_ADDRESS);
  Wire.write((byte) 0x0E);
  Wire.write((byte)((mode & 1) << 7 | (offset & 0x7F)));
  Wire.endTransmission();
}

// Create the PCF8523 real-time clock object
RTC_PCF8523 rtc;

void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);

  while(1);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // use debugging LEDs
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);

  if (!rtc.begin()) {
    error("Couldn't find RTC");
  }

  //following line sets the RTC to the date & time this sketch was compiled
  DateTime localTime(F(__DATE__), F(__TIME__));
  TimeSpan utcOffset((int32_t)UTC_OFFSET*3600);
  TimeSpan compileAndUploadDelay((int32_t)5);
  rtc.adjust(localTime - utcOffset + compileAndUploadDelay);
  RTC_PCF8523_writeOffset(0, RTC_OFFSET);

  digitalWrite(greenLEDpin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  DateTime now;
  now = rtc.now();

  Serial.print('"');
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print('"');
  Serial.print(",");
  Serial.print(now.unixtime(), DEC);
  Serial.print(",");
  Serial.print(RTC_PCF8523_readOffset(), HEX);
  Serial.println();

  delay(1000);
}

