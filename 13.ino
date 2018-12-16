#include "OurSpark.h"
ColorLEDController LEDController1(3, 6);
#include "Wire.h"
#include "math.h"
short st=49;
double Pi=3.1415926;
double i;
int LD=255;
int R(int i)
{double a;
a=fabs(LD*sin(0.001*i+Pi/3));
return a;
}
int G(int i)
{double b;
b=fabs(LD*sin(0.001*i+2*Pi/3));
return b;
}
int B(int i)
{double c;
c=fabs(LD*sin(0.001*i+Pi));
return c;
}
void receiveEvent(int howMany)
{
  st=Wire.read();
  Serial.print(st);
}
void setup()
{
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}
void loop()
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
  if(st==56)
{    for(double i=0;i>=0;++i)
    {
      LEDController1.ShowColor(0,R(i),G(i),B(i));
     delay(15);
     }
}
  if(st==57){
 
for(int i=0;i<=255;i++)
{
  LEDController1.ShowColor(0,i,0,0);
  delay(20);
}
for(int i=255;i>=0;i--)
{
  LEDController1.ShowColor(0,i,0,0);
  delay(20);
}
for(int i=0;i<=255;i++)
{
  LEDController1.ShowColor(0,0,i,0);
  delay(20);
}
for(int i=255;i>=0;i--)
{
  LEDController1.ShowColor(0,0,i,0);
  delay(20);
}
for(int i=0;i<=255;i++)
{
  LEDController1.ShowColor(0,0,0,i);
  delay(20);
}
for(int i=255;i>=0;i--)
{
  LEDController1.ShowColor(0,0,0,i);
  delay(20);
}
for(int i=0;i<=255;i++)
{
  LEDController1.ShowColor(0,i,i,i);
  delay(20);
}
for(int i=255;i>=0;i--)
{
  LEDController1.ShowColor(0,i,i,i);
  delay(20);
}
  }
}
