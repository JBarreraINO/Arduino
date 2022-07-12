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
// Constantes para PID
float KP = 10; //0.01; /valor maximo teorico de 65535
float KD = 1; // 1.0;
float Ki = 0.08;//.006

// Regulación de la velocidad Máxima
int Velmax = 50  ;//40 //Maximo 255 nieveles

// Data para intrgal
int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;
unsigned int position = 0;
//declara variables para utilizar PID
int proporcional = 0;         // Proporcional
int integral = 0;           //Intrgral
int derivativo = 0;          // Derivativo
int diferencial = 0;   // Diferencia aplicada a los motores
int last_prop;         // Última valor del proporcional (utilizado para calcular la derivada del error)
int Target = 750; // Setpoint (Como utilizamos 16 sensores, la línea debe estar entre 0 y 1500, por lo que el ideal es que esté en 750)

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

  Robot.Leer_Sensores_ir(0);
   p=Robot.proporcional();
// Serial.println(p);
pid();               // Calculo pid y control motores
//  delay(500);               
}

// BOTON DE ESPERA
void WaitBoton() {
  while (digitalRead(BOTON));
}
// BOTON DE INICIO
void GO_Boton() {
  while (digitalRead(GO));
}
void pid()
{
   proporcional = p - 750;
  Serial.println(proporcional);
   Serial.println(p);
  if ( proporcional <= -Target )
  {
    Control.Motorde(0);
  Control.Motoriz(-150);
  }
  else if ( proporcional >= Target )
  {
   // Control.Motoriz(0);
    //Control.Motorde(-150);
      Control.Motor(-150,150 );
  }

  derivativo = proporcional - last_prop;
  integral = error1 + error2 + error3 + error4 + error5 + error6;
  last_prop = proporcional;

  error6 = error5;
  error5 = error4;
  error4 = error3;
  error3 = error2;
  error2 = error1;
  error1 = proporcional;

  int diferencial = ( proporcional * KP ) + ( derivativo * KD ) + (integral * Ki) ;

  if ( diferencial > Velmax ) diferencial = Velmax;
  else if ( diferencial < -Velmax ) diferencial = -Velmax;

  ( diferencial < 0 ) ?
Control.Motor(Velmax + diferencial, Velmax) :Control.Motor(Velmax, Velmax - diferencial);
    
  }
  

   
