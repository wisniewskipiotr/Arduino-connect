#include "TestLibrary.h"

  void json_send_setup(EthernetClient c, String name_, int voltage_, int resistor_){
    
    const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + length_of_buffer;
    StaticJsonDocument<capacity> root1;
   
    Serial.begin(9600);
    Wire.begin();
    
    now = rtc.now();

    // trzeba ustawić prawidłowy czas dodać pare minut !!!

    sprintf(buf, "%02d:%02d:%02d %02d/%02d/%04d",  now.hour(), now.minute(),now.second(), now.day(), now.month(), now.year());  
    
    root1["name"] = name_;
    root1["work voltage[V] "] = voltage_;
    root1["resistor value"] = resistor_;
    root1["current time"] = buf;
    
    serializeJson(root1, c);
  }
  
void json_send_loop(EthernetClient c, float val_1,float val_2,float val_3,float val_4,float val_5,int solenoid, boolean module){
    Serial.print("loop " );

    // mozna dac do .h
    const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(8) + 160;
    StaticJsonDocument<capacity> root2;
    
    now = rtc.now();

    // trzeba ustawić prawidłowy czas dodać pare minut !!!

    sprintf(buf, "%02d:%02d:%02d %02d/%02d/%04d",  now.hour(), now.minute(),now.second(), now.day(), now.month(), now.year());  

    root2["sensor_p1"] = val_1;
    root2["sensor_p2"] = val_2;
    root2["sensor_p3"] = val_3;
    root2["sensor_4"] = val_4;
    root2["sensor_5"] = val_5;
    root2["current time"] = buf;
    root2["solenoid value"] = solenoid;
    root2["module"] = module;

    serializeJson(root2, c);
  }
