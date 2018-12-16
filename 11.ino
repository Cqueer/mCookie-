//#define INTERVAL_SENSOR   17000
//#include <Microduino_SHT2x.h>
//#define IDLE_TIMEOUT_MS  3000 
//#define INTERVAL_sensor 2000
//unsigned long sensorlastTime = millis();
//float sensor_tem, sensor_hum;
//unsigned long sensor_time = millis();
//Tem_Hum_S2 TempMonitor;
//#include "OurSpark.h"
//ColorLEDController LEDController1(3, 6);
//unsigned long timer_draw,timer;


String jsonToSend;
#include <ESP8266.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
#define EspSerial mySerial
#define UARTSPEED  9600
#define SSID "L0V3Jenny"
#define PASSWORD "sam83315795"
#define HOST_NAME "api.heclouds.com"
#define HOST_PORT (80)
ESP8266 wifi(&EspSerial);
short st=49;
#define EspSerial mySerial
#include "Wire.h"
void setup(void) {
  Wire.begin();
  Serial.begin(115200);
  Serial.print(F("setup begin\r\n"));
  delay(100);
  WifiInit(EspSerial,UARTSPEED);
  Serial.print(F("FW Version:"));
  Serial.println(wifi.getVersion().c_str());
  if (wifi.setOprToStationSoftAP()) {
     Serial.print(F("to station + softap ok\r\n"));
   } else {
     Serial.print(F("to station + softap err\r\n"));
   }
    if(wifi.joinAP(SSID,PASSWORD)){
      Serial.print(F("Join AP success\r\n"));
     Serial.print(F("IP:"));
     Serial.println( wifi.getLocalIP().c_str());
   } else {
     Serial.print(F("Join AP failure\r\n"));
   }
  if(wifi.disableMUX()){
    Serial.print(F("single ok\r\n"));
  }else {
    Serial.print(F("single err\r\n"));
  }
    Serial.print(F("setup end\r\n"));
}
//void LEDControl()
//{
//  if(st==49)LEDController1.ShowColor(0,0,0,0);
//  if(st==50)LEDController1.ShowColor(0,255,255,255);
//  if(st==51)LEDController1.ShowColor(0,170,170,170);
//  if(st==52)LEDController1.ShowColor(0,65,65,65);
//  if(st==53)
//  {
//  LEDController1.ShowColor(0,255,0,0);
//  delay(50);
//  LEDController1.ShowColor(0,0,255,0);
//  delay(50);
//  LEDController1.ShowColor(0,0,0,255);
//  delay(50);
//  LEDController1.ShowColor(0,127,127,255);
//  delay(50);
//  LEDController1.ShowColor(0,127,255,127);
//  delay(50);
//  LEDController1.ShowColor(0,255,127,127);
//  delay(50);
//  LEDController1.ShowColor(0,255,255,255);
//  delay(50);
//  }
//  if(st==54)LEDController1.ShowColor(0,170,170,170);
//}
void online()
{
 if(wifi.createTCP(HOST_NAME,HOST_PORT)){
  Serial.print("create tcp ok\r\n");
 }else{
  Serial.print("create tcp err\r\n");
 }
 uint8_t buffer[300] = {0};
 String Poststring="GET /devices/504382102/datapoints?datastream_id=st&limit=1 HTTP/1.1\r\napi-key:iu=bBuQYARztziUBERYE7Jp38kY=\r\nHost:api.heclouds.com\r\nConnection:close\r\n\r\n\r\n";
 const char *postArray=Poststring.c_str();
  wifi.send((const uint8_t*)postArray,strlen(postArray));
  Serial.println(F("Send Success!"));
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if(len>0)
  {
    Serial.print(F("hao"));
    for(uint32_t i=0;i<len;i++)
    {
      Serial.print((char)buffer[i]);
    }
    for (uint32_t i = 0; i < len; i++) {
      if((char)buffer[i]=='a'&&(char)buffer[i+1]=='l'&&(char)buffer[i+2]=='u'&&(char)buffer[i+3]=='e')
      {
              if((char)buffer[i+6]>='0'&&(char)buffer[i+6]<='9')
              {
                st=buffer[i+6];
                Serial.print("\n");
                Serial.print(st);
                Serial.print("\n");
              }
      }
      }
       }
      else{
        Serial.print(F("huai"));
      }
}
void loop() {
    online();
//      if (sensor_time > millis())  sensor_time = millis();  
//  if(millis() - sensor_time > INTERVAL_SENSOR)
//  {  
//    sensor_time = millis();
//  } 
//  LEDControl();
    Wire.beginTransmission(8);
    Wire.write(st);
    Wire.endTransmission();
    delay(100);
  }

