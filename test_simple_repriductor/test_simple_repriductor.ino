#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
 
void setup () {
 Serial.begin (9600);
 mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module 
 delay(1);
 mp3_set_volume (10);  // set volume of speaker (0~30)
}
 
void loop () {        
 
 mp3_play (1); //play 0001.mp3
 delay (10000); //10 sec, time delay to allow 0001.mp3 to finish playing
 
 mp3_play (2);
 delay (5000);
 
 mp3_play (3);
 delay (5000);
 
 mp3_play (4); //play 0004.mp3
 delay (9000);
 
 mp3_play (5);
 delay (6000);
  
}
