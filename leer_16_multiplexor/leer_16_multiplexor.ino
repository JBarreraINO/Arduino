
#define s0 5 // Sensor Selection pins.
#define s1 A1
#define s2 A2
#define s3 A3
#define Sens A4 // Analog input pin.
int value;

void setup() {
  pinMode(s0, OUTPUT); // 4 Selection pins are output.
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  Serial.begin(9600);
}

void loop() { 
              
   for (int i=0; i <= 15; i++){ 

     if (i == 0)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      delay(1);
      value=analogRead(Sens);
    }
    else if (i == 1)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      delay(1);
      value=analogRead(Sens);
    }
    else if (i == 2)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      delay(1);
      value=analogRead(Sens);
    }
    else if (i == 3)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      delay(1);
      value=analogRead(Sens);
    }
    else if (i == 4)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
      delay(1);
      value=analogRead(Sens);
    }
    else if (i == 5)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
      delay(1);
        value=analogRead(Sens);    
      
   }
    else if (i == 6)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
      value=analogRead(Sens); 
    }
    else if (i == 7)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
      value=analogRead(Sens);
    }
    else if (i == 8)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      value=analogRead(Sens);    
    }
    else if (i == 9)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      value=analogRead(Sens);
    }
    else if (i == 10)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
       value=analogRead(Sens);
    }
    else if (i == 11)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      value=analogRead(Sens);
    }
    else if (i == 12)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
      value=analogRead(Sens);
    }
    else if (i == 13)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
      value=analogRead(Sens);
      }
    else  if (i == 14)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
       value=analogRead(Sens);
        }
            else  if (i == 15)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
      value=analogRead(Sens);
    }
    Serial.print("s");
    Serial.print(i+1);Serial.print(":");
    Serial.print(value);
    Serial.print(" ");
    
  }
 
  Serial.println(""); 
   }
