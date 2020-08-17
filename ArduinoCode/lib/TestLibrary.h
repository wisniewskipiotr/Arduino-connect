#ifndef t1
#define t1

#if ARDUINO >= 100
  #include <Arduino.h> 
#else
  #include <WProgram.h> 
#endif

#define length_of_buffer 20

#include <WString.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <ArduinoJson.h>
#include <RTClib.h>
#include <Wire.h>
#include <UIPEthernet.h>


void json_send_setup(EthernetClient c,String name_, int voltage_, int resistor_);
void json_send_loop(EthernetClient c,float val_1,float val_2,float val_3,float val_4,float val_5, int solenoid, boolean module);

RTC_PCF8523 rtc;
char buf[length_of_buffer];
DateTime now;
#endif 
