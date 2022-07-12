/*  A4988
    DMOS Microstepping Driver with Translator
    And Overcurrent Protection

    Microstepping Resolution - Quarter Step
    MS1 LOW
    MS2 HIGH
    MS3 LOW
    
    Shunt between SLEEP and RESET
    VDD GND 5Vdc
    VMOT GND 8-35 Vdc
    
   these constants won't change:
*/
const int EnablePin = 8;  // Enable
const int StepPin = 3;    // Step
const int DirPin =6;    // Dir

const int NumberOfSteps_1_Turn = 40;
int StepCounter;

boolean Controle_A4988(boolean Dir,int NumberOfSteps ) {
  
  digitalWrite(DirPin,Dir); // Set Dir high
  
  for(StepCounter = 0; StepCounter < NumberOfSteps; StepCounter++) // Loop NumberOfSteps times
  {
      digitalWrite(StepPin,HIGH); // Output high
      delayMicroseconds(1000); // Wait 1/2 a ms
      digitalWrite(StepPin,LOW); // Output low
      delayMicroseconds(1000); // Wait 1/2 a ms
    }

} // End function Controle_A4988()

void setup()
{
  pinMode(EnablePin,OUTPUT); // Enable
  pinMode(StepPin,OUTPUT); // Step
  pinMode(DirPin,OUTPUT); // Dir
  
  digitalWrite(EnablePin,LOW); // Set Enable low
  }
  


void loop()
{
  
  Controle_A4988(HIGH,NumberOfSteps_1_Turn);
  delay(1000); // pause one second
  
  Controle_A4988(LOW,NumberOfSteps_1_Turn);
  delay(1000); // pause one second
  
  boolean Turn = false;
  int Angle = 1;
  
for (int j=0; j<10;j++){  // increase angle
  
  for (int u= 0; u<2; u++) {  // turn dir 
  
   for (int i = 0; i< 20;i++){  // Steps
     
    Controle_A4988(Turn,Angle);
    delay(20); // pause 20 mS
    
    }  //end for i
    
      Turn = !Turn;
  } //end for u


  Angle = Angle + j;
  
  
  
} //end for j
}
