#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_MCP9808.h"

// how many milliseconds between grabbing data and logging it. 1000 ms is once a second
#define LOG_INTERVAL  25000 // mills between entries (reduce to take more/faster data)

// how many milliseconds before writing the logged data permanently to disk
// set it to the LOG_INTERVAL to write each time (safest)
// set it to 10*LOG_INTERVAL to write all data every 10 datareads, you could lose up to 
// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 25000 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

#define ECHO_TO_SERIAL   0 // echo data to serial port
#define WAIT_TO_START    0 // Wait for serial input in setup()

// the digital pins that connect to the LEDs
#define redLEDpin 3
#define greenLEDpin 2

// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

// the logging file
File logfile;

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

// Create the PCF8523 real-time clock object
RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);

  while(1);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  // use debugging LEDs
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);

#if WAIT_TO_START
  Serial.println("Type any character to start");
  while (!Serial.available());
#endif //WAIT_TO_START

  // initialize the SD card
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    error("Card failed, or not present");
  }
  Serial.println("card initialized.");
  
  // create a new file
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    }
  }
  
  if (! logfile) {
    error("couldnt create file");
  }
  
  Serial.print("Logging to: ");
  Serial.println(filename);

  if (!tempsensor.begin(0x18)) {
    error("Couldn't find MCP9808!");
  }

  if (!rtc.begin()) {
    error("Couldn't find RTC");
  }

  if (!rtc.initialized()) {
    error("RTC is NOT running!");
  }

  logfile.println("unixtime,utc,temp");    
#if ECHO_TO_SERIAL
  Serial.println("unixtime,utc,temp");
#endif //ECHO_TO_SERIAL
}

void loop() {
  DateTime now;

  // delay for the amount of time we want between readings
  delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));

  digitalWrite(greenLEDpin, HIGH);

#if ECHO_TO_SERIAL
  Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere
  tempsensor.shutdown_wake(0);
#endif // ECHO_TO_SERIAL

  // fetch the time
  now = rtc.now();

  // log unixtime
  logfile.print(now.unixtime(), DEC);
#if ECHO_TO_SERIAL
  Serial.print(now.unixtime(), DEC);
#endif //ECHO_TO_SERIAL

  // log utc
  logfile.print(",");
  logfile.print('"');
  logfile.print(now.year(), DEC);
  logfile.print("/");
  logfile.print(now.month(), DEC);
  logfile.print("/");
  logfile.print(now.day(), DEC);
  logfile.print(" ");
  logfile.print(now.hour(), DEC);
  logfile.print(":");
  logfile.print(now.minute(), DEC);
  logfile.print(":");
  logfile.print(now.second(), DEC);
  logfile.print('"');
#if ECHO_TO_SERIAL
  Serial.print(",");
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
#endif //ECHO_TO_SERIAL

  // Read and print out the temperature, then convert to *F
  float temperatureC = tempsensor.readTempC();
  float temperatureF = temperatureC * 9.0 / 5.0 + 32;

  // log temperature
  logfile.print(",");
  logfile.print(temperatureF);
#if ECHO_TO_SERIAL
  Serial.print(",");
  Serial.print(temperatureF);
#endif //ECHO_TO_SERIAL

  logfile.println();
#if ECHO_TO_SERIAL
  Serial.println();
#endif // ECHO_TO_SERIAL

#if ECHO_TO_SERIAL
  Serial.println("Shutdown MCP9808.... ");
  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere
#endif //ECHO_TO_SERIAL

  digitalWrite(greenLEDpin, LOW);

  // Now we write data to disk! Don't sync too often - requires 2048 bytes of I/O to SD card
  // which uses a bunch of power and takes time
  if ((millis() - syncTime) < SYNC_INTERVAL) return;
  syncTime = millis();
  
#if ECHO_TO_SERIAL
  Serial.println("Syncing");
#endif // ECHO_TO_SERIAL

  // blink LED to show we are syncing data to the card & updating FAT!
  digitalWrite(redLEDpin, HIGH);
  logfile.flush();
  digitalWrite(redLEDpin, LOW);
}

