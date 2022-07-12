
//CODIGO SEGUIDOR DE LINEA 
//DESIGN BY JUAN BARRERA
//SAMURAI TEAM BLACK
/*
 * 
 * lectura de sensores ir en blanco 208  393  973  972  259  197  280  160  203  156  256  279  292  412  264  327
 * lectura de sensores ir en negro  972  980  1007  1007  975  974  982  973  982  971  979  976  977  982  968  974
 * valor muestras = (valor blanco + valor negro)/2
 * valor muestras 590, 686, 600, 600, 617,585, 631, 566, 592, 563, 617, 627, 634, 697, 616, 650
 */
#include <sky.h>
#include<Servo.h>
 #include <QTRSensors.h>
Servo ESC; //Crear un objeto de clase servo


sky Robot;
const int LedsIr = 9;    //Pin para encender los leds ir
const int S0 = 3;        //Pin A0 de modo digital 
const int S1 = 0;        //Pin A1 de modo digital
const int S2 = 10;        //Pin A2 de modo digital
const int S3 = 1;        //Pin A3 de modo digital
const int ANALOG_IN = A0;
 
int vel = 1000; //amplitud del pulso   
int pin_pwm_i   =  6;
int pin_pwm_d    = 5;
int led1   =       11;
int mot_i =        8;
int mot_d    =     7;



int Muestras[16]={858,808, 822, 804, 796,797,803,815,830, 835, 836, 843, 812, 839, 830, 841}; 
int sensorValores[16];
int Valor_Digital[16];
int x;
int y;
int p;

unsigned int position=0;
 
/// variables para el pid
int  derivativo=0, proporcional=0, integral=0; //parametros
int  salida_pwm=0, proporcional_pasado=0;
 ////////////////////////////////
 ////////////////// SAMURAI /////////
///////////////VARIABLES    //////////////
int velocidad=70;              //variable para la velocidad, el maximo es 255
float Kp=1, Kd=2, Ki=0.001;  //constantes
//variable para escoger el tipo de linea
int linea=0;                    //  0 para lineas negra, 1 para lineas blancas
 /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////
  /////////////////////
 //////////////////////////////////////////
 /////////////////////
 /////////////////////////

void setup()
{//modo de 16
   pinMode(LedsIr, OUTPUT);  //
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  digitalWrite(LedsIr,HIGH); // Enciendo los leds ir
 //activacion esc
 
  ESC.attach(0);
  ESC.writeMicroseconds(1000); //1000 
 delay(3000); 
 pinMode(led1, OUTPUT); //led1
  Robot.SkyDragon();
    //calibracion QTR     
 for (int i = 0; i <100; i++)  //calibracion durante 2.5 segundos,
 {                                 //para calibrar es necesario colocar los sensores sobre la superficie negra y luego 
  digitalWrite(led1, HIGH);  //la blanca
  delay(20);
  
  digitalWrite(led1, LOW);  
  delay(20);
 }
digitalWrite(led1, LOW); //apagar sensores para indicar fin de calibracion 
delay(400); 
turbina(1500);
//digitalWrite(led2,HIGH); //encender led 2 para indicar la
while(true)
{
  
  
     if(Robot.Boton()) //si se presiona boton 
    {
//        digitalWrite(led2,LOW); //indicamos que se presiono boton
        digitalWrite(led1,HIGH); //encendiendo led 1
        delay(3000);
        break; //saltamos hacia el bucle principal
    }
}
}       
 
 
void loop()
{
Leer_Sensores_ir(0);
 //pid(0, 120, 0.18, 0.001, 4 );
  pid(velocidad,Kp,Ki,Kd); //funcion para algoritmo pid 
                                 //primer parametro: 0 para lineas negras, tipo 1 para lineas blancas
                                 //segundo parametro: velocidad pwm de 0 a 255
                                 //tercer parametro: constante para accion proporcional
                                 //cuarto parametro: constante para accion integral
                                 //quinto parametro: constante para accion derivativa
  //frenos_contorno(0,700);
  frenos_contorno(linea,700); //funcion para frenado en curvas tipo 
                              //primer parametro :0 para lineas negras, tipo 1 para lineas blancas
                              //segundo parametro:flanco de comparaciÃ³n va desde 0 hasta 1000 , esto para ver 
}
 
////////funciones para el control del robot////
void Leer_Sensores_ir(boolean L) {
 for(int i=0; i<=15;i++)  {       //Leo los 16 canales               
    digitalWrite(S0, i&0x01);
    digitalWrite(S1, i&0x02);
    digitalWrite(S2, i&0x04);
    digitalWrite(S3, i&0x08);
    
    sensorValores[i] = analogRead(ANALOG_IN); //guardo los valores de los sensores
    if(L==1) {
    if(sensorValores[i] < Muestras[i] ){Valor_Digital[i] = 1 ;}  //Convierto los valores de analogicos a digitales para linea blanca
    else {Valor_Digital[i] = 0 ;} }

    
      if(L==0){
    if(sensorValores[i] < Muestras[i] ){Valor_Digital[i] = 0 ;}  //Convierto los valores de analogicos a digitales para linea negra
    else {Valor_Digital[i] = 1 ;}}
       Serial.print(Valor_Digital[i]);  //aqui monitoreamos cada una de las lecturas digitales
   Serial.print("  ");
    }

   
     posicion_ponderada ();
  }

void posicion_ponderada ()
{
  x=(14000*Valor_Digital[0]+13000*Valor_Digital[1]+12000*Valor_Digital[2]+11000*Valor_Digital[4]+10000*Valor_Digital[5]+9000*Valor_Digital[6]+8000*Valor_Digital[7]+7000*Valor_Digital[8]+6000*Valor_Digital[9]+5000*Valor_Digital[10]+4000*Valor_Digital[11]+3000*Valor_Digital[12]+2000*Valor_Digital[13]+1000*Valor_Digital[14]+0*Valor_Digital[15]);
  y=(Valor_Digital[0]+Valor_Digital[1]+Valor_Digital[2]+Valor_Digital[3]+Valor_Digital[4]+Valor_Digital[5]+Valor_Digital[6]+Valor_Digital[7]+Valor_Digital[8]+Valor_Digital[9]+Valor_Digital[10]+Valor_Digital[11]+Valor_Digital[12]+Valor_Digital[13]+Valor_Digital[14]+Valor_Digital[15]);
 p=x/y;
  Serial.print("<< ");
 Serial.print(p);
 Serial.print("<< ");
  }
  
 void pid( int velocidad, float Kp, float Ki, float Kd)
{
  position =p;
  proporcional = (position) - 7500; // set point es 3500, asi obtenemos el error
  integral=integral + proporcional_pasado; //obteniendo integral
  derivativo = (proporcional - proporcional_pasado); //obteniedo el derivativo
  if (integral>1000) integral=1000; //limitamos la integral para no causar problemas
  if (integral<-1000) integral=-1000;
  salida_pwm =( proporcional * Kp ) + ( derivativo * Kd )+(integral*Ki);
   
  if (  salida_pwm > velocidad )  salida_pwm = velocidad; //limitamos la salida de pwm
  if ( salida_pwm < -velocidad )  salida_pwm = -velocidad;
   
  if (salida_pwm < 0)
 {
        Robot.Speeds(velocidad+salida_pwm, velocidad);
 }
 if (salida_pwm >0)
 {
  Robot.Speeds(velocidad, velocidad-salida_pwm);
 }
 
 proporcional_pasado = proporcional;  
}
 
//funcion para control de motores

void motores(int motor_izq, int motor_der)
{
  if ( motor_izq >= 0 )  //motor izquierdo
 {
  digitalWrite(mot_i,HIGH); // con high avanza

 }
 else
 {
  digitalWrite(mot_i,LOW); //con low retrocede

 }
 
  if ( motor_der >= 0 ) //motor derecho
 {
  digitalWrite(mot_d,HIGH);

 }
 else
 {
  digitalWrite(mot_d,LOW);

 }
 
   
}
 


void frenos_contorno(int tipo,int flanco_comparacion)
{
   
if(tipo==0)
{
  if(position<=50) //si se salio por la parte derecha de la linea
 {
  //debido a la inercia, el motor 
       Robot.Speeds (-150,140)  ;     
       turbina(1600);                   
                                
  while(true)  
  {
   qtrrc.read(sensorValues); //lectura en bruto de sensor   
   if( sensorValues[0]>flanco_comparacion || sensorValues[1]>flanco_comparacion ) 
   //asegurar que esta en linea
   {
    break;
   } 
  }
 }
 
 if (position>=6550) //si se salio por la parte izquierda de la linea
 { 
   Robot.Speeds(140,-150);
     turbina(1800);
  while(true)
  {
   qtrrc.read(sensorValues);
   if(sensorValues[7]>flanco_comparacion || sensorValues[6]>flanco_comparacion )
   {
    break;
   }  
  }
 }
}
 
if(tipo==1) //para linea blanca con fondo negro
{
 if(position<=50) //si se salio por la parte derecha de la linea
 {
   Robot.Speeds(-120,100); //debido a la inercia el motor 
                   //tendera a seguri girando
                   //por eso le damos para atras  
                   //para que frene lo mas rapido posible 
  while(true)  
  {
   qtrrc.read(sensorValues); //lectura en bruto de sensor
   if(sensorValues[0]<flanco_comparacion || sensorValues[1]<flanco_comparacion )   //asegurar que esta en linea
   {
    break;
   }
  }
 }
 
 if(position>=6550) //si se salio por la parte izquierda de la linea
 { 
   Robot.Speeds(100,-120);
  while(true)
  {
   qtrrc.read(sensorValues);
   if(sensorValues[7]<flanco_comparacion || sensorValues[6]<flanco_comparacion)
   {
    break;
   }  
  }
 }
}
}









void turbina(int vel)
{
    if(vel != 0)
    {
      ESC.writeMicroseconds(vel); //Generar un pulso con el numero recibido
    }
    
}


