const int Trigger = 12;   //Pin digital 2 para el Trigger del sensor
const int Echo = 13;   //Pin digital 3 para el Echo del sensor
 #include <Barreraino.h>
barrera Robot;  //Declaracion del objeto
#include <BarreraTB6612.h>
motores Control;
const int valorUmbral = 12;// distancia minima 
void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  while(true){
    if(Robot.Boton1()){break;}}
}
 
void loop()
{
 
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
 
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100);          //Hacemos una pausa de 100ms



   if(d>valorUmbral )
  {
 
    Control.Motor(100,100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
    delay(200);
  }
   else if(d<valorUmbral )
  {

     Control.Motor(-100,-100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)

   delay(500);
  
   Control.Motor(100,-100);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
   delay(500);
  }
}