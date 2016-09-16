#include <SPI.h>
#include <LiquidCrystal.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include "Sodaq_DS3231.h"
#define CE   9
#define CSN 10
//Receptor
//IRQ //12
//11 //13
//10 //9
//3V3//GND
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE, CSN); 
int data[2]; 
LiquidCrystal lcd(7, 8, 6, 5, 4, 3);
void setup() {
pinMode(2,OUTPUT);
digitalWrite(2,LOW);
Wire.begin();
lcd.begin(16,2); //(colum, filas)
rtc.begin();
radio.begin();
radio.openReadingPipe(1,pipe);//lo lee
radio.startListening();
}

void loop() {
  printTime();
  if ( radio.available() ){
  radio.read( data , sizeof(data) ); 
  LED(data[0],data[1]);
  }  
}

void LED(int dat1, int dat2) { 
          if(dat1==0 ){
            digitalWrite(2,LOW);}
          if(dat1==1){
            digitalWrite(2,HIGH);}
          if(dat1==0 && dat2==1){
            digitalWrite(2,HIGH);
            delay(4900);
            digitalWrite(2,LOW);}
 }

void printTime(){
  DateTime now = rtc.now();
  lcd.setCursor(4,0);
  if (now.hour()<10)  {
    lcd.print("0");
  }
  lcd.print(now.hour());
  lcd.print(':');
  if (now.minute()<10)  {
    lcd.print("0");
  }
  lcd.print(now.minute());
  lcd.print(':');
  if (now.second()<10)  {
    lcd.print("0");
  }
  lcd.print(now.second());
  lcd.setCursor(1,1);
  lcd.print("Vallesol S.A.C ");
  delay(100);
  if ((now.minute()==0 && now.second()==0) || ((now.minute()%5)==0 && now.second()==0))  {
    digitalWrite(2,HIGH);
    delay(4800);
    digitalWrite(2,LOW);
   }   
} 


