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
byte ip[] = {192,168,0,101};
EthernetClient client;
int table_name = int(mac[5]); 

//funkcja do zamienienia z tą z biblioteki

void test(EthernetClient c)
{
  const size_t capacity =  JSON_OBJECT_SIZE(5);
  StaticJsonDocument<capacity> root1;
        root1["name"] = "Setup321";
        root1["work voltage[V]"] = "132";
        root1["resistor value"] = "4500";
        root1["dew_point"] = "55";
        root1["table_name"] = table_name;

        serializeJson(root1, c);

}
void test_loop(EthernetClient c){

  const size_t capacity2 = JSON_OBJECT_SIZE(10);
  StaticJsonDocument<capacity2> root2; 
  
    root2["sensor_p1"] = random(5,10);
    root2["sensor_p2"] = random(5,10);
    root2["sensor_p3"] = random(5,10);
    root2["ez1"] = "1";
    root2["ez2"] = "0";
    root2["ez3"] = "0";
    root2["pressure"] = random(1000,1075);
    root2["dew_point"] = random(50,75);
    root2["current time"] = " ";
    root2["table_name"]= table_name;

    
    serializeJson(root2, c);
    Serial.println(c);
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
