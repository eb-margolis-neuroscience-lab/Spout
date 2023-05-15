//SpoutCollect v 0.9.22
//Firmware for rodent cage mounted drinking tracker, capacitative touch detection
//See hardware details at [insert Github link here] 
//Last updated by EBM 5/06/2023

#include <Wire.h>
#include "RTClib.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <time.h>
#include <String.h>

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char monthsOfTheYear[13][12] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

const int TOUCH_RED = A0; //connect breakout pad to pin A0
const int TOUCH_BLACK = A7; //connect breakout pad to pin A7

//GPIO bitmask calculation for sleep functionality
#define BLACK_PIN_BITMASK 0x100000000

float BatteryVoltage = 0;
char filenameSTR[] = "00000000.csv";
const int touch_threshold = 100;

//This device name, used in naming of files
String fname = "Cage1";

//---------------------------------------------------
void setup()
{
  Serial.begin(115200);
  // Initialize SD Card
  if (!SD.begin(33)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  //Check RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
  }
  
  //Get start time and date, name datafile accordingly
  DateTime now = rtc.now();
  char dateTimeString[200] = "";
  sprintf(dateTimeString, "%s, %s %d %04d %02d:%02d:%02d", daysOfTheWeek[now.dayOfTheWeek()], monthsOfTheYear[now.month()], now.day(), now.year(), now.hour(), now.minute(), now.second());
  String timestamp = "Begin data collection at ";
  timestamp += dateTimeString;
  String dataString = "";
  dataString += "Touch value BLACK, ";
  dataString += "Touch value RED, ";
  dataString += "Time (ms)";
//  dataString += ", Battery voltage";
//filenamestring must start with / and include _ between device name and timestamp
  String thisfilename = "/";
char filedate ;
  thisfilename = thisfilename + fname + "_"; 
  sprintf(filedate, "%dMonth%dDay%dHour%dMinute.csv", now.month(), now.day(), now.hour(), now.minute());
  thisfilename = thisfilename + filedate; 
  
  //devicename must be followed by "_" in order for SpoutAnalyze to parse the device name correctly
//  sprintf(filenameSTR, thisfilename);
  File dataFile = SD.open(thisfilename, FILE_WRITE); 
  if (dataFile) {
    dataFile.println(timestamp); //write the time of data collection start
    dataFile.println(dataString); //write column names
    //Serial.println(filenameSTR); //write file name to serial monitor for troubleshooting
  }
  else {
    Serial.println("error creating file in setup");
    Serial.println(filenameSTR);
  }
  dataFile.close();

  //Setup sleep/wake functionality, reading goes low when touched
  esp_sleep_enable_ext1_wakeup(BLACK_PIN_BITMASK, ESP_EXT1_WAKEUP_ALL_LOW); //wake if Black spout touched
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0); //wake if Red spout touched, on Feather HUZZAH ESP32 A0 = GPIO26
}

//---------------------------------------------------
void loop()
{
  //Read value from each touch sensor
  int touch_value_black = analogRead(TOUCH_BLACK);
  int touch_value_red = analogRead(TOUCH_RED);
  //test if touch value(s) are low, write data to the .csv
  //columns are: touch_value_black, touch_value_red, time since start in ms, battery voltage
  if (touch_value_black < touch_threshold) {
    //Read battery value, convert to voltage; pin A13/I35 = Batt pin
    //  BatteryVoltage = (((analogRead(A13)) * 2 * 3.3 * 1.1) / 4095); 
      String dataString = "";
      dataString += touch_value_black;
      dataString += ", ";
      dataString += touch_value_red;
      dataString += ", ";
      dataString += millis();
    //  dataString += ", ";
    //  dataString += BatteryVoltage;
      //write value of each sensor and battery voltage 
      File dataFile = SD.open(filenameSTR, FILE_APPEND);
      dataFile.println(dataString);
    //  Serial.println(dataString); //uncomment this line to use serial monitor
    }
  else if (touch_value_red < touch_threshold) {
    //  BatteryVoltage = (((analogRead(A13)) * 2 * 3.3 * 1.1) / 4095); 
      String dataString = "";
      dataString += touch_value_black;
      dataString += ", ";
      dataString += touch_value_red;
      dataString += ", ";
      dataString += millis();
     // dataString += ", ";
     // dataString += BatteryVoltage;
      File dataFile = SD.open(filenameSTR, FILE_APPEND);
      dataFile.println(dataString);
    //  Serial.println(dataString); //uncomment this line to use serial monitor
    }
  else {
    //  Serial.println("Sleep"); //uncomment this line to use serial monitor
      esp_light_sleep_start(); //will wake on touch 
  }
}
