/*
 Buttons work like this:
 - A short stroke on either button turns on the backlight after 30 seconds of inactivity
 Settings for time:
H increments the hours
M increments the minutes and sets the seconds to 0
*/
#include "LiquidCrystal.h"
// associates the digital pins with LCD
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//defines contrast for the LCD
int cs=9;// 9th pin
const int screenContrast = 100;// sets the contrast to its standard setting
// sets the standard time display for 00:00:00 AM or midnight
int hoursetting=00;
int minutessetting=00;
int secondssetting=00;
int boolflag=0; //PM
// buttons for time setting
int buttonOne;
int buttonTwo;
// this defines the pins for time setting
int hoursButton=1;// this is pin 1 for setting the hours
int minutesButton=2;// this is pin 2 for setting the minutes
// defines the timing out for the backlight
const int Time_light=150;
int lightAdjust=Time_light;// this defines the process of the backlight timing out
int backlightTimeOut=10; // this is the amount of time it takes for the backlight to time out
const int backlightAdjust=120; 
static uint32_t last_time, now = 0; 
void setup()
{
  lcd.begin(16,2);
  pinMode(hoursButton,jalaINPUT);  
pinMode(minutesButton,jalaINPUT);
  analogWrite(cs,screenContrast);
  analogWrite(backlightTimeOut,backlightAdjust);// turns on the backlight
  now=millis(); // this will read the RTC value 
}
void loop()
{ 
  lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("Time ");
 if(hoursetting<10)lcd.print("0");// always 2 digits
 lcd.print(hoursetting);
 lcd.print(":");
 if(minutessetting <10)lcd.print("0");
 lcd.print(minutessetting);
 lcd.print(":");
 if(secondssetting<10)lcd.print("0");
 lcd.print(secondssetting);
 if(boolflag==0) lcd.print(" AM");
 if(boolflag==1) lcd.print(" PM");
 lcd.setCursor(0,1);
 lcd.print("Precision clock");
for ( int i=0 ;i<5 ;i++)
{
  while ((now-last_time)<200) //this delays by 0.2 seconds
  { 
    now=millis();
  }
 last_time=now;
 buttonOne=digitalRead(hoursButton);
 buttonTwo=digitalRead(minutesButton);
 --;
 if(lightAdjust == 0)
 {
  analogWrite(backlightTimeOut,0);// Backlight OFF
  lightAdjust++;
 }
 //process to press whatever button to turn on the backlight 
 if(  ((buttonOne==0)|(buttonTwo==0)) & (lightAdjust==1)  )
 {
  lightAdjust=Time_light;
  analogWrite(backlightTimeOut,backlightAdjust);
  while ((buttonOne==0)|(buttonTwo==0))
  {
   buttonOne=digitalRead(hoursButton);
   buttonTwo=digitalRead(minutesButton);
  }
 }
 else
 {
  if(buttonOne==0){
   hoursetting++;
   lightAdjust=Time_light;
   analogWrite(backlightTimeOut,backlightAdjust);
  }
 if(buttonTwo==0){
  secondssetting=0;
  minutessetting++;
  lightAdjust=Time_light;
  analogWrite(backlightTimeOut,backlightAdjust);
  }
/* ---- manage seconds, minutes, hours am/pm overflow ----*/
 if(s==60){
  secondssetting=0;
   minutessetting++;
 }
 if(minutessetting == 60)
 {
  minutessetting =0;
  hoursetting++;
 }
 if(hoursetting == 13)
 {
  hoursetting =1;
  boolflag++;
  if(boolflag == 2) boolflag=0;
 }
 if((buttonOne==0)|(buttonTwo==0)) 
{
  lcd.setCursor(0,0);
  lcd.print("Time ");
  if(hoursetting < 10)lcd.print("0");  
  lcd.print(hoursetting);
  lcd.print(":");
  if(minutessetting < 10)lcd.print("0");
  lcd.print(minutessetting);
  lcd.print(":");
  if(secondssetting<10)lcd.print("0");
  lcd.print(secondssetting);
  if(boolflag == 0) lcd.print(" AM");
  if(boolflag == 1) lcd.print(" PM");
    lcd.setCursor(0,1);
  lcd.print("Precision clock");
 }
 } // terminate the if else loop
}// terminate the for loop
 secondssetting++; 
 if(secondssetting == 60){
  secondssetting = 0;
  minutessetting++;
 }
 if(minutessetting == 60)
 {
  minutessetting = 0;
  hoursetting++;
 }
 if(hoursetting == 13)
 {
  hoursetting = 1;
  boolflag++;
  if(boolflag == 2)
boolflag = 0;
 }
// end this loop
}

// end all loops
//end program
