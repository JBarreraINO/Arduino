#include <Arduino.h>
#line 1 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"

#include "pitches.h" //add Equivalent frequency for musical note
#include "themes2.h" //add Note vale and duration 


#line 6 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void poc();
#line 34 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void loop();
#line 44 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void cf();
#line 73 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void mario();
#line 102 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void ttn();
#line 130 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void newn();
#line 158 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void desp();
#line 184 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void setup();
#line 6 "C:\\Users\\tiche\\AppData\\Local\\Temp\\arduino_modified_sketch_448613\\toneMelody.ino"
void poc()
{ 
  for (int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Pirates_duration[thisNote];//convert duration to time delay
   if(thisNote%3==0){
    
   
    tone(9, Pirates_note[thisNote], noteDuration);
   }
     if(thisNote%4==0){
    
   
    tone(9, Pirates_note[thisNote], noteDuration);
   }   if(thisNote%5==0){
    
   
    tone(9, Pirates_note[thisNote], noteDuration);
   }   else{
    
   
    tone(9, Pirates_note[thisNote], noteDuration);
   } 
    int pauseBetweenNotes = noteDuration * 1.05; //Here 1.05 is tempo, increase to play it slower
    delay(pauseBetweenNotes);
    noTone(9); //stop music on pin 8 
    }
}
void loop()
{ 
 poc();
 cf();
 mario();
 ttn();
 newn();
 desp();
}

void cf()
{
  for (int thisNote = 0; thisNote < (sizeof(CrazyFrog_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / CrazyFrog_duration[thisNote]; //convert duration to time delay
 if(thisNote%3==0){
    
   
    tone(9, CrazyFrog_note[thisNote], noteDuration);
   }
     if(thisNote%4==0){
    
   
    tone(9, CrazyFrog_note[thisNote], noteDuration);
   }   if(thisNote%5==0){
    
   
    tone(9, CrazyFrog_note[thisNote], noteDuration);
   }   else{
    
   
    tone(9, CrazyFrog_note[thisNote], noteDuration);
   } 
    int pauseBetweenNotes = noteDuration * 1.30;//Here 1.30 is tempo, decrease to play it faster
    delay(pauseBetweenNotes);
    noTone(9); //stop music on pin 8 
    }
}

void mario()
{
    for (int thisNote = 0; thisNote < (sizeof(MarioUW_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / MarioUW_duration[thisNote];//convert duration to time delay
     if(thisNote%3==0){
    
   
    tone(9, MarioUW_note[thisNote], noteDuration);
   }
     if(thisNote%4==0){
    
   
    tone(9, MarioUW_note[thisNote], noteDuration);
   }   if(thisNote%5==0){
    
   
    tone(9, MarioUW_note[thisNote], noteDuration);
   }   else{
    
   
    tone(9, MarioUW_note[thisNote], noteDuration);
   } 
    int pauseBetweenNotes = noteDuration * 1.80;
    delay(pauseBetweenNotes);
    noTone(8); //stop music on pin 8 
    }
}

void ttn()
{
    for (int thisNote = 0; thisNote < (sizeof(Titanic_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Titanic_duration[thisNote];//convert duration to time delay
     if(thisNote%3==0){
    
   
    tone(9, Titanic_note[thisNote], noteDuration);
   }
     if(thisNote%4==0){
    
   
    tone(9, Titanic_note[thisNote], noteDuration);
   }   if(thisNote%5==0){
    
   
    tone(9, Titanic_note[thisNote], noteDuration);
   }   else{
    
   
    tone(9, Titanic_note[thisNote], noteDuration);
   } 
    int pauseBetweenNotes = noteDuration * 2.70;
    delay(pauseBetweenNotes);
    noTone(9); //stop music on pin 8 
    }
}
void newn()
{
    for (int thisNote = 0; thisNote < (sizeof(new_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / new_duration[thisNote];//convert duration to time delay
     if(thisNote%3==0){
    
   
    tone(9, new_note[thisNote], noteDuration);
   }
     if(thisNote%4==0){
    
   
    tone(9, new_note[thisNote], noteDuration);
   }   if(thisNote%5==0){
    
   
    tone(9, new_note[thisNote], noteDuration);
   }   else{
    
   
    tone(9, new_note[thisNote], noteDuration);
   } 
    int pauseBetweenNotes = noteDuration * 2.70;
    delay(pauseBetweenNotes);
    noTone(9); //stop music on pin 8 
    }
}
void desp(){
   for (int thisNote = 0; thisNote < (sizeof(desp_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / desp_duration[thisNote];//convert duration to time delay
   if(thisNote%3==0){
    
   
    tone(9, desp_note[thisNote], noteDuration);
   }
     if(thisNote%4==0){
    
   
    tone(9, desp_note[thisNote], noteDuration);
   }   if(thisNote%5==0){
    
   
    tone(9, desp_note[thisNote], noteDuration);
   }   else{
    
   
    tone(9, desp_note[thisNote], noteDuration);
   } 
    int pauseBetweenNotes = noteDuration * 1.50; //Here 1.05 is tempo, increase to play it slower
    delay(pauseBetweenNotes);
    noTone(8); //stop music on pin 8 
    }}
void setup() {
 //Button 4 with internal pull up
Serial.begin(9600);
}
