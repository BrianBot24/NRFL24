#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int SW1 = 7;
int SW2 = 6;
void setup(void){
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(pipe);}
void loop(void){
if (digitalRead(SW1) == HIGH){
msg[0] = 111;
radio.write(msg, 1);}
if (digitalRead(SW1) == LOW){
msg[0] = 112;
radio.write(msg, 1);}
if (digitalRead(SW2) == HIGH){
msg[0] = 113;
radio.write(msg, 1);}
if (digitalRead(SW2) == LOW){
msg[0] = 114;
radio.write(msg, 1);}}

