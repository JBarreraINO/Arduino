int frontal = 8;
int derecho = 4;
int izquierdo = 2;
int Dderecho = 7;  //SENSOR EN DIAGONAL DERECHO
int Dizquierdo = 10;  //SENSOR EN DIAGONAL IZQUIERDO

 //Sensores Piso
int piso1 = A2;
int piso2 = A1;

//Declaracion pin motores
int MOTOR1_IN1 = 3;
int MOTOR1_IN2 = 6;
int MOTOR2_IN1 = 9;
int MOTOR2_IN2 = 5;

//Ultimo sensor en detectar al oponente
int ultimo = 0;
int ultimo2 = 0;
int ultimo3 = 0;

void setup() {
  // Establecer los sensores como entradas de señal con resistores de pull-down
  pinMode(frontal, INPUT_PULLUP);
  pinMode(derecho, INPUT_PULLUP);
  pinMode(izquierdo, INPUT_PULLUP);
  pinMode(Dderecho, INPUT_PULLUP);
  pinMode(Dizquierdo, INPUT_PULLUP);

  // Esperar 5 segundos antes de iniciar
  delay(4000);
}



void loop() {
if ((analogRead(piso1)<900)&&(analogRead(piso2)<900)) //Los sensores de piso detectaron el borde
{Retroceder();} //El robot debe retroceder

else if ((analogRead(piso1)<900)) //Los sensores de piso detectaron el borde
{Retrocederderecha();} //El robot debe retroceder

else if ((analogRead(piso2)<900)) //Los sensores de piso detectaron el borde
{Retrocederizquierda();} //El robot debe retroceder

else if ((analogRead(piso1)<900)&&(analogRead(piso2)<900)) //Los sensores de piso detectaron el borde
{Retroceder();} //El robot debe retroceder

else if ((analogRead(piso1)<900)) //Los sensores de piso detectaron el borde
{Retrocederderecha();} //El robot debe retroceder

else if ((analogRead(piso2)<900)) //Los sensores de piso detectaron el borde
{Retrocederizquierda();} //El robot debe retroceder


  else if (digitalRead(frontal) == 0) //El sensor frontal detecto al oponente (EL VALOR CAMBIA DEPENDEINDO DEL SENSOR EN MI CASO MI SENSOR TIENE VALOR DE 100 O MAYOR CUANDO DETECTA ALGO)
 {
 Avanzar();
 } //El robot debe avanzar y embestir al oponente y recordar el ultimo sensor que lo vio

   else if (digitalRead(derecho) == 0) //El sensor derecho detecto al oponente
 {
 derecha(); //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar
 ultimo=0;
 } //El robot debe recordar el ultimo sensor que vio al oponente para encontrarlo mas rapido  

   else if (digitalRead(Dderecho) == 0) //El sensor derecho diagonal detecto al oponente
 {
 derechalento();
 ultimo=0;
 } //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar  (la velocidad se reduce para que el robot no termine girando por accidente)  

   else if (digitalRead(izquierdo) == 0) //El sensor izquierdo detecto al oponente
 {
 izquierda(); //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar  
 ultimo=1;
 } //El robot debe recordar el ultimo sensor que vio al oponente para encontrarlo mas rapido

   else if (digitalRead(Dizquierdo) == 0) //El sensor izquierdo diagonal detecto al oponente
 {
 izquierdalento();
ultimo=1;
 } //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar  (la velocidad se reduce para que el robot no termine girando por accidente)  



else if ((digitalRead(frontal)== 0)&&(analogRead(Dizquierdo) == 0))
 {
Avanzar();;
 }
 else if ((digitalRead(frontal)== 0)&&(analogRead(Dderecho) == 0))
 {
Avanzar();;
 }
 else if ((digitalRead(frontal)== 0)&&(analogRead(Dderecho) == 0)&&(analogRead(Dizquierdo) == 0))
 {
Avanzar();;
 }

else if (ultimo==0)  //El robot recuerda que vio al oponente con su sensor derecho
{derechalento();}
else if (ultimo==1)  //El robot recuerda que vio al oponente con su sensor izquierdo
{izquierdalento();}

 
else {
{PARAR();}
}


}

//MOVIMIENTO ROBOT
void Avanzar() {
  // Avanzar
  digitalWrite(MOTOR1_IN2, LOW);
  analogWrite(MOTOR1_IN1, 240); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN1, LOW);
  analogWrite(MOTOR2_IN2, 240); //DEFINIR PWM A GUSTO DE 1-255
  }

void Avanzarlento() {
  // Avanzar
  digitalWrite(MOTOR1_IN2, LOW);
  analogWrite(MOTOR1_IN1, 155); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN1, LOW);
  analogWrite(MOTOR2_IN2, 155); //DEFINIR PWM A GUSTO DE 1-255
  }

void Retroceder() {
  // Retroceder
  digitalWrite(MOTOR1_IN1, LOW);
  analogWrite(MOTOR1_IN2, 250); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN2, LOW);
  analogWrite(MOTOR2_IN1, 250); //DEFINIR PWM A GUSTO DE 1-255
  }
 void Retrocederizquierda() {
  // Retroceder
  digitalWrite(MOTOR1_IN1, LOW);
  analogWrite(MOTOR1_IN2, 180); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN2, LOW);
  analogWrite(MOTOR2_IN1, 200); //DEFINIR PWM A GUSTO DE 1-255
  }

 
 void Retrocederderecha() {
  // Retroceder
  digitalWrite(MOTOR1_IN1, LOW);
  analogWrite(MOTOR1_IN2, 200); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN2, LOW);
  analogWrite(MOTOR2_IN1, 180); //DEFINIR PWM A GUSTO DE 1-255
  }

void derecha() {
  // Girar derecha
  digitalWrite(MOTOR1_IN1, LOW);
  analogWrite(MOTOR1_IN2, 240); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN1, LOW);
  analogWrite(MOTOR2_IN2, 240); //DEFINIR PWM A GUSTO DE 1-255
  }
 
void derechalento() {
  // Girar derecha
  digitalWrite(MOTOR1_IN1, LOW);
  analogWrite(MOTOR1_IN2, 200); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN1, LOW);
  analogWrite(MOTOR2_IN2, 200); //DEFINIR PWM A GUSTO DE 1-255
  }
 
void izquierda() {
  // Girar izquierda
  digitalWrite(MOTOR1_IN2, LOW);
  analogWrite(MOTOR1_IN1, 240); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN2, LOW);
  analogWrite(MOTOR2_IN1, 240); //DEFINIR PWM A GUSTO DE 1-255  
  }
 
void izquierdalento() {
  // Girar izquierda
  digitalWrite(MOTOR1_IN2, LOW);
  analogWrite(MOTOR1_IN1, 200); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN2, LOW);
  analogWrite(MOTOR2_IN1, 200); //DEFINIR PWM A GUSTO DE 1-255  
  }

  void PARAR() {
  // El robot para
  digitalWrite(MOTOR1_IN2, LOW);
  analogWrite(MOTOR1_IN1, 0); //DEFINIR PWM A GUSTO DE 1-255
  digitalWrite(MOTOR2_IN1, LOW);
  analogWrite(MOTOR2_IN2, 0); //DEFINIR PWM A GUSTO DE 1-255  
  }