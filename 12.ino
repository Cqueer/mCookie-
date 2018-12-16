#define INTERVAL_SENSOR   17000
#include <Microduino_SHT2x.h>
#define IDLE_TIMEOUT_MS  3000 
#define INTERVAL_sensor 2000
unsigned long sensorlastTime = millis();
#define INTERVAL_OLED 1000
String mCottenData;
float sensor_tem, sensor_hum;
unsigned long sensor_time = millis();
Tem_Hum_S2 TempMonitor;
short st=54;
//#include "OurSpark.h"
//ColorLEDController LEDController1(3, 6);
#include "Wire.h"
#include <Rtc_Pcf8563.h>
Rtc_Pcf8563 rtc;
#include "U8glib.h"
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
#define init_draw 10
unsigned long timer_draw,timer;
String dateStr, ret;
/*void LEDControl()
{
  if(st==49)LEDController1.ShowColor(0,0,0,0);
  if(st==50)LEDController1.ShowColor(0,255,255,255);
  if(st==51)LEDController1.ShowColor(0,170,170,170);
  if(st==52)LEDController1.ShowColor(0,65,65,65);
  if(st==53)
  {
  LEDController1.ShowColor(0,255,0,0);
  delay(50);
  LEDController1.ShowColor(0,0,255,0);
  delay(50);
  LEDController1.ShowColor(0,0,0,255);
  delay(50);
  LEDController1.ShowColor(0,127,127,255);
  delay(50);
  LEDController1.ShowColor(0,127,255,127);
  delay(50);
  LEDController1.ShowColor(0,255,127,127);
  delay(50);
  LEDController1.ShowColor(0,255,255,255);
  delay(50);
  }
  if(st==54)LEDController1.ShowColor(0,170,170,170);
}*/


void setup(void) {
  
  Serial.begin(115200);
// setRtcTime(18, 12, 3, 1, 23, 49, 00);
  timer=millis();
}
String getRtcTimeString() {
  dateStr = rtc.formatDate(RTCC_DATE_US);
  dateStr += " ";
  dateStr += rtc.formatTime(RTCC_TIME_HMS);
  return dateStr;
}
void draw()
{
    float tem=TempMonitor.getTemperature(),hum=TempMonitor.getHumidity();
  setFont_M;
u8g.setPrintPos(2,64);
u8g.print("tem:");
u8g.setPrintPos(27,64);
u8g.print(tem);
u8g.setPrintPos(65,64);
u8g.print("hum:");
u8g.setPrintPos(90,64);
u8g.print(hum);
  setFont_L;
  u8g.setPrintPos(4, 16);
  u8g.print(rtc.formatDate(RTCC_DATE_US));
  u8g.print("    ");
  switch (rtc.getWeekday()) {
    case 1:
      u8g.print("Mon");
      break;
    case 2:
      u8g.print("Tue");
      break;
    case 3:
      u8g.print("Wed");
      break;
    case 4:
      u8g.print("Thu");
      break;
    case 5:
      u8g.print("Fri");
      break;
    case 6:
      u8g.print("Sat");
      break;
    case 7:
      u8g.print("Sun");
      break;
  }
  setFont_SS;
  u8g.setPrintPos(18, 49);
  u8g.print(rtc.getHour());
  u8g.setPrintPos(55, 46);
  {if (rtc.getSecond() % 2 == 0)
    {u8g.print(":");}
  else
    {u8g.print(" ");}}
  u8g.setPrintPos(68, 48);
  if (rtc.getMinute() < 10)
  {
    u8g.print("0");
    u8g.print(rtc.getMinute());
  }
  else
    u8g.print(rtc.getMinute());
}
void setRtcTime (byte _year, byte _month, byte _day, byte _week, byte _hour, byte _minute, byte _sec)
{
  //clear out all the registers
  rtc.initClock();
  rtc.setDate(_day, _week, _month, 0, _year);
  rtc.setTime(_hour, _minute, _sec);
}
void loop() {
  ret = getRtcTimeString();
  if (sensor_time > millis())  sensor_time = millis();  
  if(millis() - sensor_time > INTERVAL_SENSOR)
  {  
    sensor_time = millis();
  } 
//  LEDControl();
    u8g.firstPage();
    do {
      draw();
    }
    while ( u8g.nextPage() );

    Serial.print("\n");
    delay(100);
  }
