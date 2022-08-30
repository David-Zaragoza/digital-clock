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
const int contraste = 100;// sets the contrast to its standard setting
// sets the standard time display for 00:00:00 AM or midnight
int horas=00;
int minutos=00;
int segundos=00;
int bandera=0; //PM
// buttons for time setting
int primerBoton;
int segundoBoton;
// this defines the pins for time setting
int ubicacionDeHoras=1;// this is pin 1 for setting the hours
int ubicacionDeMinutos=2;// this is pin 2 for setting the minutes
// defines the timing out for the backlight
const int Time_light=150;
int paLaLuz=Time_light;// this defines the process of the backlight timing out
int LDT=10; // this is the amount of time it takes for the backlight to time out
const int luzDeTras=120; 
static uint32_t last_time, now = 0; 
void setup()
{
  lcd.begin(16,2);
  pinMode(ubicacionDeHoras,jalaINPUT);  
pinMode(ubicacionDeMinutos,jalaINPUT);
  analogWrite(cs,contraste);
  analogWrite(LDT,luzDeTras);// turns on the backlight
  now=millis(); // this will read the RTC value 
}
void loop()
{ 
  lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("Time ");
 if(horas<10)lcd.print("0");// always 2 digits
 lcd.print(horas);
 lcd.print(":");
 if(minutos <10)lcd.print("0");
 lcd.print(minutos);
 lcd.print(":");
 if(segundos<10)lcd.print("0");
 lcd.print(segundos);
 if(bandera==0) lcd.print(" AM");
 if(bandera==1) lcd.print(" PM");
 lcd.setCursor(0,1);
 lcd.print("Precision clock");
for ( int i=0 ;i<5 ;i++)
{
  while ((now-last_time)<200) //this delays by 0.2 seconds
  { 
    now=millis();
  }
 last_time=now;
 primerBoton=digitalRead(ubicacionDeHoras);
 segundoBoton=digitalRead(ubicacionDeMinutos);
 paLaLuz--;
 if(paLaLuz == 0)
 {
  analogWrite(LDT,0);// Backlight OFF
  paLaLuz++;
 }
 //process to press whatever button to turn on the backlight 
 if(  ((primerBoton==0)|(segundoBoton==0)) & (paLaLuz==1)  )
 {
  paLaLuz=Time_light;
  analogWrite(LDT,luzDeTras);
  while ((primerBoton==0)|(segundoBoton==0))
  {
   primerBoton=digitalRead(ubicacionDeHoras);
   segundoBoton=digitalRead(ubicacionDeMinutos);
  }
 }
 else
 {
  if(primerBoton==0){
   horas++;
   paLaLuz=Time_light;
   analogWrite(LDT,luzDeTras);
  }
 if(segundoBoton==0){
  segundos=0;
  minutos++;
  paLaLuz=Time_light;
  analogWrite(LDT,luzDeTras);
  }
/* ---- manage seconds, minutes, hours am/pm overflow ----*/
 if(s==60){
  segundos=0;
   minutos++;
 }
 if(minutos == 60)
 {
  minutos =0;
  horas++;
 }
 if(horas == 13)
 {
  horas =1;
  bandera++;
  if(bandera == 2) bandera=0;
 }
 if((primerBoton==0)|(segundoBoton==0)) 
{
  lcd.setCursor(0,0);
  lcd.print("Time ");
  if(horas < 10)lcd.print("0");  
  lcd.print(horas);
  lcd.print(":");
  if(minutos < 10)lcd.print("0");
  lcd.print(minutos);
  lcd.print(":");
  if(segundos<10)lcd.print("0");
  lcd.print(segundos);
  if(bandera == 0) lcd.print(" AM");
  if(bandera == 1) lcd.print(" PM");
    lcd.setCursor(0,1);
  lcd.print("Precision clock");
 }
 } // terminate the if else loop
}// terminate the for loop
 segundos++; 
 if(segundos == 60){
  segundos = 0;
  minutos++;
 }
 if(minutos == 60)
 {
  minutos = 0;
  horas++;
 }
 if(horas == 13)
 {
  horas = 1;
  bandera++;
  if(bandera == 2)
bandera = 0;
 }
// end this loop
}

// end all loops
//end program