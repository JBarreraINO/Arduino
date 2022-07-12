
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
     pinMode(30, OUTPUT);
       pinMode(34, OUTPUT);
         pinMode(46, OUTPUT);
   pinMode(42, OUTPUT);
   pinMode(40, OUTPUT);
   pinMode(52, OUTPUT);
       pinMode(10, INPUT);   
         pinMode(11, INPUT); 
         pinMode(12, INPUT); 
}

// the loop function runs over and over again forever
void loop() {
 if(digitalRead(10)==HIGH){ONE(); delay(3000);off();}
  if(digitalRead(11)==HIGH){TW0(); delay(3000);off();}
 if(digitalRead(12)==HIGH){three(); delay(3000);off();}
    off();  
  /*
    
     ONE(); delay(1000);off();
  TW0(); delay(1000);off();
  three(); delay(1000);off(); 
    */   
}


void off(){
  
  digitalWrite(42, HIGH);  
  digitalWrite(40, HIGH);
  digitalWrite(52, HIGH);
    digitalWrite(30, HIGH);
      digitalWrite(34, HIGH);
        digitalWrite(46, HIGH);
}


void ONE(){  digitalWrite(42, HIGH);  
  digitalWrite(52, HIGH); // turn the LED on (HIGH is the voltage level)
   
  digitalWrite(52, LOW);// wait for a second
   digitalWrite(42, LOW);   
   }
  void TW0(){
      digitalWrite(40, LOW);// wait for a second
   digitalWrite(42, LOW);  
   digitalWrite(30, LOW);
      digitalWrite(34, LOW);
        digitalWrite(46, LOW); }
        
       void three(){
        
         digitalWrite(52, LOW);// wait for a second
   digitalWrite(42, LOW);   
     digitalWrite(40, LOW);// wait for a second
   
   
    digitalWrite(34, LOW);
        digitalWrite(46, LOW); 
        
        }
