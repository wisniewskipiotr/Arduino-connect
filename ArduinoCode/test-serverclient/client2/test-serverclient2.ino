//json
#include <WString.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Wire.h>
#if ARDUINO >= 100
  #include <Arduino.h> 
#else
  #include <WProgram.h> 
#endif

// client
#include <UIPEthernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192,168,0,103};
EthernetClient client;

//funkcja do zamienienia z tą z biblioteki

void test(EthernetClient c)
{
  const size_t capacity =  JSON_OBJECT_SIZE(4);
  StaticJsonDocument<capacity> root1;
        root1["name"] = "111111";
        root1["work voltage[V]"] = "50";
        root1["resistor value"] = "2000";
        root1["current time"] = "302d:302d:302d 302d.302d.304d";

        serializeJson(root1, c);

}
void test_loop(EthernetClient c){

  const size_t capacity2 = JSON_OBJECT_SIZE(8);
  StaticJsonDocument<capacity2> root2; 
  
    root2["sensor_p1"] = "3";
    root2["sensor_p2"] = "4";
    root2["sensor_p3"] = "5";
    root2["sensor_4"] = 33;
    root2["sensor_5"] = "3";
    root2["current time"] = "302d:302d:302d.302d.302d.304d";
    root2["solenoid value"] = "2";
    root2["module"] = "true";
    
    serializeJson(root2, c);
}

void setup()
    {
      
        Ethernet.begin(mac);                            //  connect to router and DHCP give the dynamic IP
        Serial.begin(115200);  
        Serial.print("wysylam-Setup ");  
        //  start the serial "monitor portu szeregowego"
        while(!client.connect(ip, 8090))
        {
          Serial.print("Nie polaczono-> szukam ");
        };             //  while not connected - try to connect 
        
        //tutaj zamiast tego kodu będzie funkcja z biblioteki do której wkładamy pobrane pomiary i wysyłamy na server
        test(client);    
        delay(650);  
        client.stop();
                       
        
    }
void loop()
{
    Serial.print("Prz  ");
    client.connect(ip,8090);
    test_loop(client);
    //  client.print("TEST2");
      Serial.print("Wysylam z loop ");
    delay(125);
client.stop();
}
