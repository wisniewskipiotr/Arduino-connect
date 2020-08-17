/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>


#ifndef STASSID
#define STASSID "dlink"
#define STAPSK  ""
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.0.100";
const uint16_t port = 8090;

byte mac[6];


ESP8266WiFiMulti WiFiMulti;

WiFiClient client;

void test(WiFiClient c)
{
  WiFi.macAddress(mac);
  int table_name = (mac[5],DEC);
  
  const size_t capacity = JSON_OBJECT_SIZE(5);
  Serial.println(capacity);
  StaticJsonDocument<capacity> root1;
        root1["name"] = "Setup321";
        root1["work voltage[V]"] = "132";
        root1["resistor value"] = "4500";
        root1["dew_point"] = "55";
        root1["table_name"] = table_name;

        serializeJson(root1, c);
        
        
}
void test_loop(WiFiClient c){
  WiFi.macAddress(mac);
  int table_name = (mac[5],HEX);

  const size_t capacity2 = JSON_OBJECT_SIZE(10);
  StaticJsonDocument<capacity2> root2; 
    Serial.println(capacity2);
  
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

String dupa(){
 WiFi.macAddress(mac);
 int table_name = (mac[5],HEX);
 const size_t capacity2 = JSON_OBJECT_SIZE(10);
  StaticJsonDocument<capacity2> root2; 
    Serial.println(capacity2);
  
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
    String output;
    serializeJson(root2, output);
    
  
  return output; 
  }


void setup() {

  Serial.begin(115200);
  WiFiClient client;
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.println("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }


  

  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.macAddress(mac);
  int table_name = (mac[5],HEX);  
  Serial.println("Mac address: ");
  Serial.println(String(table_name));
 
  
  test(client);
  delay(500);
}


void loop() {
 
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }
  
  // This will send the request to the server
  //client.println("hello from ESP8266");

    client.println(dupa());
  //test_loop(client);


  //read back one line from server
  Serial.println("receiving from remote server");
  String line = client.readStringUntil('\r');
  Serial.println(line);

  Serial.println("closing connection");
  client.stop();

  Serial.println("wait 5 sec...");
  delay(5000);
}
