/*
 * 
 * lectura de sensores ir en blanco 208  393  973  972  259  197  280  160  203  156  256  279  292  412  264  327
 * lectura de sensores ir en negro  972  980  1007  1007  975  974  982  973  982  971  979  976  977  982  968  974
 * valor muestras = (valor blanco + valor negro)/2
 * valor muestras 590, 686, 600, 600, 617,585, 631, 566, 592, 563, 617, 627, 634, 697, 616, 650
 */

  #include <IngenieroMakerSeguidor16s.h>
  #include <IngenieroMakerMax.h>
 //CREO EL OBJETO Control
 motores Control;
 //CREO EL OBJETO Robot
barra16 Robot;
 //Mapeo de pines

#define LED     13
#define GO  7 //10
#define BOTON 4 //12
int p;
int Target = 750;

/// variables para el pid
int  derivativo = 0, proporcional = 0, integral = 0; //parametros
int  salida_pwm = 0, proporcional_pasado = 0;
// Regulación de la velocidad Máxima


unsigned int position = 0;
///////////////VARIABLES    //////////////
int velocidad = 40;            //variable para la velocidad, el maximo es 255
float Kp = 16, Kd = 4, Ki = 0.001;
//float Kp=0.20, Kd=5, Ki=0.001; //constantes
//variable para escoger el tipo de linea
int linea = 0;        
void setup()
{ /*
  Serial.begin(9600);
  // Declaramos como salida los pines utilizados
  pinMode(LED   , OUTPUT);
  pinMode(GO, INPUT);
  pinMode(BOTON, INPUT);
  //CALIBRACION
   Robot.leer_blanco(); //PONER SENSORES EN BLANCO
  delay(3000);
  WaitBoton();          //PRESIONAR BOTON
  Robot.leer_negro();   //PONER SENSORES EN NEGRO
  delay(3000);
  WaitBoton();           //PRESIONAR BOTON
  Robot.Calcula_muestras(); //CALCULA TABLA DE MUESTRAS
  GO_Boton();            // CONTROL DE ARRANQUE

*/

  Serial.begin(9600);
  // Declaramos como salida los pines utilizados
  pinMode(LED   , OUTPUT);
  pinMode(GO, INPUT);
  pinMode(BOTON, INPUT);
  //CALIBRACION

  WaitBoton();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  Robot.leer_blanco(); //PONER SENSORES EN BLANCO
  
  digitalWrite(LED_BUILTIN, LOW);
  
  WaitBoton();          //PRESIONAR BOTON
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  Robot.leer_negro();   //PONER SENSORES EN NEGRO
   digitalWrite(LED_BUILTIN, LOW);
 
  WaitBoton();           //PRESIONAR BOTON

  digitalWrite(LED_BUILTIN, HIGH);
  Robot.Calcula_muestras(); //CALCULA TABLA DE MUESTRAS
  GO_Boton();            // CONTROL DE ARRANQUE
  digitalWrite(LED_BUILTIN, LOW);
}



void loop()
{
  
 Robot.valor();
            
}
