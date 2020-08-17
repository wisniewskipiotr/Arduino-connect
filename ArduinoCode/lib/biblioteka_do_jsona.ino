#include "TestLibrary.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };     // device (client) mac address 
byte ip[] = {192,168,1,87};                              // server ip
int port = 8080;                                         // server port
EthernetClient client;                                   // client 
void setup() {
   // connect 
  Ethernet.begin(mac);                            //  connect to router and DHCP give the dynamic IP
  Serial.begin(9600);                             //  start the serial "monitor portu szeregowego"
  while(!client.connect(ip,port)){};              //  while not connected - try to connect to server
  
  json_send_setup(client,"nazwa1",5,200);         //  send json data to server
  delay(1000);
}
int i=1; // temporary data 
void loop() {

  json_send_loop(client,20,19,21,15,10,i,false);        //  send json data to server
  delay(100);
  i++;
}
