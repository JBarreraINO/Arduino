/*
 * 
 * lectura de sensores ir en blanco 208  393  973  972  259  197  280  160  203  156  256  279  292  412  264  327
 * lectura de sensores ir en negro  972  980  1007  1007  975  974  982  973  982  971  979  976  977  982  968  974
 * valor muestras = (valor blanco + valor negro)/2
 * valor muestras 590, 686, 600, 600, 617,585, 631, 566, 592, 563, 617, 627, 634, 697, 616, 650
 */
 //Mapeo de pines
#define STBY 6
#define AIN1  7
#define AIN2  8
#define PWMB  3
#define PWMA  9
#define BIN1  5
#define BIN2  4
#define LED     11
#define BOTON  4 //10


const int LedsIr = 0;    //Pin para encender los leds ir
const int S0 = 14;        //Pin A0 de modo digital 
const int S1 = 15;        //Pin A1 de modo digital
const int S2 = 16;        //Pin A2 de modo digital
const int S3 = 17;        //Pin A3 de modo digital
const int ANALOG_IN = A4;

int Muestras[16]={858,808, 822, 804, 796,797,803,815,830, 835, 836, 843, 812, 839, 830, 841}; 
int sensorValores[16];
int Valor_Digital[16];
int x;
int y;
int p;

// Constantes para PID
float KP = 1; //0.01; /valor maximo teorico de 65535
float KD = 2; // 1.0;
float Ki = 0.006;//.006

// Regulación de la velocidad Máxima
int Velmax = 50 ;//40 //Maximo 255 nieveles

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
int Target = 7500; // Setpoint (Como utilizamos 16 sensores, la línea debe estar entre 0 y 15000, por lo que el ideal es que esté en 7500)

void setup()
{
  Serial.begin(9600);
  // Declaramos como salida los pines utilizados
  pinMode(LED   , OUTPUT);
  pinMode(BIN2  , OUTPUT);
 pinMode(STBY  , OUTPUT);
  pinMode(BIN1  , OUTPUT);
  pinMode(PWMB  , OUTPUT);
  pinMode(AIN1  , OUTPUT);
  pinMode(AIN2  , OUTPUT);
  pinMode(PWMA  , OUTPUT);
  pinMode(BOTON, INPUT);

  //pinMode(BUZZER, OUTPUT);
  pinMode(LedsIr, OUTPUT);  //
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  digitalWrite(LedsIr,HIGH); // Enciendo los leds ir
}

void loop()
{
Leer_Sensores_ir(0); //Leo los sensores 1 si hay linea blanca 0 si hay linea negra
pid();               // Calculo pid y control motores
  delay(500);               
}


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

// Función accionamiento motor izquierdo
void Motoriz(int value)
{
  if ( value >= 0 )
  {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else
  {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    value ;
  }
  analogWrite(PWMB, value);
}

// Función accionamiento motor derecho
void Motorde(int value)
{
  if ( value >= 0 )
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  else
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    value *= -1;
  }
  analogWrite(PWMA, value);
}
//Accionamiento de motores
void Motor(int left, int righ)
{
//  digitalWrite(STBY, HIGH);
  Motoriz(left);
  Motorde(righ);
}

//función de freno
void freno(boolean left, boolean righ, int value)
{
  //digitalWrite(STBY, HIGH);
  if ( left )
  {

  }
  if ( righ )
  {

  }
}

// BOTON DE ESPERA
void WaitBoton() {
  while (!digitalRead(BOTON));
}
void pid()
{
   proporcional = p - 7500;
    Serial.print("<< ");
  Serial.println(proporcional);
   Serial.print("<< ");
  if ( proporcional <= -Target )
  {
    Motorde(0);
    freno(true, false, 255);
  }
  else if ( proporcional >= Target )
  {
    Motoriz(0);
    freno(false, true, 255);
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
  Motor(Velmax + diferencial, Velmax) : Motor(Velmax, Velmax - diferencial);
    
  }

