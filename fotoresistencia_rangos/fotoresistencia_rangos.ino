void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
 int pot= analogRead(A0);

if(pot >200)
{
 Serial.println("es de dìa");
}
if(pot <150)
{
 Serial.println("es de noche") ;
}
 
 


}
