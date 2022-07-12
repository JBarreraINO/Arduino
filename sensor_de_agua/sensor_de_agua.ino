const int waterSens = A0; //define water sensor
const int led = 9;//define led to pin 9
int waterVal; //define the water sensor value


void setup() {
pinMode(led, OUTPUT); //set led as an output
pinMode(waterSens, INPUT);//set water sensor as an input
Serial.begin(9600);  //start the serial port at 9600 bauds

}

void loop() {
  waterVal = analogRead(waterSens); //read the water sensor
  
  Serial.println(waterVal); //print the value of the water sensor to the serial monitor
  delay(1000);
if (waterVal <= 0){
  digitalWrite(led, HIGH);//if the water sensor senses water turn the led on
}
else{
  digitalWrite(led, LOW);//if it doesn't sense anything turn the led off
}
}
