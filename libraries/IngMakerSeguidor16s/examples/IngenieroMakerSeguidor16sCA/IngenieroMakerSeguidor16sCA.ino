/*Codigo de ejemplo para un seguidor de linea basado en:
 * Arduino Nano
 * Motores pololu 6V HPCP
 * TB6612 Rojo (generico)
 * Barra de 16 sensores marca Ingeniero Maker
 * Chasis para seguidor de linea en PCB marca Ingeniero Maker
 * Modulo de arranque
 * 
 * Procedimiento de Calibración
 * 1.-la barra de sensores se debe poner primero en el color blanco de la pista procurando 
 * que todos los sensores esten sobre el color blanco.
 * 
 * 2.- Presionar el boton en el PCB del robot, despues de esto ya estara calibrado el color blanco.
 * 
 * 3.-la barra de sensores se debe poner despues en el color negro de la pista procurando 
 * que todos los sensores esten sobre el color negro.
 * 
 * 4.- Presionar el boton en el PCB del robot, despues de esto ya estara calibrado el color negro.
 * 
 * 5.- Presionar de nuevo el boton para hacer el calculo de muestras.
 * el robot se encuentra listo para el arranque.
 */
 
 #include <IngenieroMakerSeguidor16s.h>
 #include <IngenieroMakerTB6612.h>
 //CREO EL OBJETO Control
 motores Control;
 //CREO EL OBJETO Robot
barra16 Robot;
 //Mapeo de pines

#define LED     13
#define GO  10 //10
#define BOTON 12 //12
int p;
// Constantes para PID
float KP = 1; //0.01; /valor maximo teorico de 65535
float KD = 2; // 1.0;
float Ki = 0.000;//.006

// Regulación de la velocidad Máxima
int Velmax = 85  ;//40 //Maximo 255 nieveles

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
{
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
  while (!digitalRead(GO));
}
void pid()
{
   proporcional = p - 750;
  Serial.println(proporcional);
  if ( proporcional <= -Target )
  {
    Control.Motorde(0);
    Control.freno(true, false, 255);
  }
  else if ( proporcional >= Target )
  {
    Control.Motoriz(0);
    Control.freno(false, true, 255);
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
  

   
