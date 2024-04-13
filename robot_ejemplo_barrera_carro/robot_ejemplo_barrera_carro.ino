#include <Barreraino.h>
barrera Robot;//Declaracion del objeto
#include <BarreraTB6612.h>
 motores Control;
const int Trigger = 12;   //Pin digital 2 para el Trigger del sensor
const int Echo = 13;   //Pin digital 3 para el Echo del sensor
const int valorUmbral = 8;// distancia minima 
const int s1=A1;
const int s2=A2;
void setup() {
  // put your setup code here, to run once:
Robot.unoBarrera();
  //Configuracion de la consola serial
  Serial.begin(9600);
   pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
   pinMode(s1, INPUT); //pin como salida
    pinMode(s2, INPUT); //pin como salida
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Robot.Boton1()){
    while(true){


 long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
 
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
 int s1state = digitalRead(s1);
int s2state = digitalRead(s2);
 Serial.println(s2state);

 if(d>valorUmbral && s2state==HIGH)
  {
 
    Control.Motor(100,100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
    delay(200);
  }
 else if(d<valorUmbral || s2state == LOW)
  {
 Serial.println(s2state);

     Control.Motor(-100,-100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)

   delay(500);
  
   Control.Motor(100,-100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
   delay(500);
  }


  else if(d<valorUmbral && s1state==HIGH )
  {
  Control.Motor(-80,-80);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)

   delay(500);
  
   Control.Motor(-100,100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
   delay(500);
  }

  else if (d<valorUmbral && s1state==LOW) {
 if (random(0, 2) == 0) {
      Control.Motor(-100,100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
    } else {
      Control.Motor(100,-100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
    }
  }

}
}

 
  

}
