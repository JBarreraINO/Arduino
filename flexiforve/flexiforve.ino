int flexiForcePin = A7; //analog pin 0

void setup(){
Serial.begin(9600);
}

void loop(){
int flexiForceReading = analogRead(flexiForcePin);

Serial.println(flexiForceReading*2);
Serial.println("gramos");
delay(20); //just here to slow down the output for easier reading
}
