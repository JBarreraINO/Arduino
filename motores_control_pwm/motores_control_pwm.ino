double canal[9];
long unsigned int pos = 0;
//DRIVER1
int izqA = 7 ;
int izqB = 8 ;
int derA = 12;
int derB = 13  ;
//DRIVER 2
int derA2 = 14 ;
int derB2 = 15 ;
int izqA2 = 2 ;
int izqB2 = 4 ;
// RELE
int rele = 16;

int neutralh = 1500;
int neutrall = 1420;
int maxval = 2000;
int minval = 980;

void setup()
{ Serial.begin(250000);
  pinMode (3, INPUT);
  pinMode (5, INPUT);
  pinMode (6, INPUT);
  pinMode (9, INPUT);
  pinMode (10, INPUT);
  pinMode (11, INPUT);
  pinMode (2, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (13, OUTPUT);
  pinMode (14, OUTPUT);
  pinMode (15, OUTPUT);
  pinMode (16, OUTPUT);

  canal[0] = pulseIn (3, HIGH);
  canal[1] = pulseIn (5, HIGH);
  canal[2] = pulseIn (6, HIGH);
  canal[3] = pulseIn (9, HIGH);
  canal[4] = pulseIn (10, HIGH);
  canal[5] = pulseIn (11, HIGH);

  Serial.print(canal[0]);
  Serial.print("   -   ");
  Serial.print(canal[1]);





}
void loop() {
  int valorVelocidad = pulseIn(3, HIGH);
  int valorDireccion = pulseIn(5, HIGH);
  Serial.print(canal[0]);
  Serial.print("   -   ");
  Serial.print(canal[1]);
  Serial.print("   -   ");
  Serial.print(canal[2]);
  Serial.print("   -   ");
  Serial.print(canal[3]);
  Serial.print( "    -    ");
  Serial.println( "    -    ");


if (valorVelocidad >= 1400 && valorVelocidad <= 1530) { neutral();}




}//FIN LOOP




void adelante()
{
  digitalWrite(izqA,HIGH);
  digitalWrite(izqB,LOW);
  digitalWrite(derA,HIGH);
  digitalWrite(derB,LOW);
  
 }



 void atras()
{
  digitalWrite(izqA,LOW);
  digitalWrite(izqB,HIGH);
  digitalWrite(derA,LOW);
  digitalWrite(derB,HIGH);
  
 }


 void neutral()
{
   digitalWrite(izqA,LOW);
  digitalWrite(izqB,LOW);
  digitalWrite(derA,LOW);
  digitalWrite(derB,LOW);
  
 }

 
