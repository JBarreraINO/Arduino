const int pinAcelerador = 17;
const int pinAdelanteAtrasMotor = 18;
const int pinIzquierdaDerechaMotor = 19;



const int IN1_IZQUIERDA = 27;  // Pin de dirección IN1 para motor izquierdo DIR
const int IN2_IZQUIERDA = 26;  // Pin de dirección IN2 para motor izquierdo PWM
const int IN1_DERECHA = 32;    // Pin de dirección IN1 para motor derecho DIR
const int IN2_DERECHA = 33;    // Pin de dirección IN2 para motor derecho PWM
const int Olvidar = 13;
// propiedades PWM
const int frecuencia = 5000;
const int IN1_IZQ = 0;
const int IN2_IZQ = 2;  //pwm
const int IN1_DER = 3;
const int IN2_DER = 4;
const int resolucion = 10;
const int velMIN = 0;
const int ledConected=2;


const int Aceleracion = 250;
const int minThrottle = 0;
const int maxThrottle = 1020;
const int minBrake = 0;
const int maxBrake = 1020;
//VARIABLES DE MANDO
float factorFiltro = 0.7;  // Ajusta el factor de filtro según tus necesidades
float factorFiltroX = 0.9;  // Ajusta el factor de filtro según tus necesidades
 int valorThrottleFiltrado,valorThrottleFiltradox;
const int deadbandThreshold = 20;
//TIPO DE CONTROL EN DRIVER : 1 PARA TLE5205, 0 PARA DRV8876
bool BitOff = 0;

//variables usadas
int mapaxisX = 0;
int valorThrottle;
int valorBrake;
int valorAxisX;
int bateria;
int MINpwm = 20;
int MAXpwm = 1023;
int VelMI, VelMD;

void setup() {
  Serial.begin(9600);
  if (BitOff == true) {
    int temp = MINpwm;
    MINpwm = MAXpwm;
    MAXpwm = temp;
    delay(100);
    Serial.println("bit de control: " + String(BitOff) + ",MINpwm: " + String(MINpwm) + ",Maxpwm: " + String(MAXpwm));
  }




  ledcSetup(IN1_IZQ, frecuencia, resolucion);
  ledcSetup(IN2_IZQ, frecuencia, resolucion);
  ledcSetup(IN1_DER, frecuencia, resolucion);
  ledcSetup(IN2_DER, frecuencia, resolucion);



  ledcAttachPin(IN1_IZQUIERDA, IN1_IZQ);
  ledcAttachPin(IN2_IZQUIERDA, IN2_IZQ);
  ledcAttachPin(IN1_DERECHA,  IN1_DER);
  ledcAttachPin(IN2_DERECHA, IN2_DER);

  pinMode(IN1_IZQUIERDA, OUTPUT);
  //pinMode(IN2_IZQUIERDA, OUTPUT);
  pinMode(IN1_DERECHA, OUTPUT);
  //pinMode(IN2_DERECHA, OUTPUT);
  controlarMotores(velMIN, velMIN);


}

void loop() {
// Lee los pulsos PWM de cada canal
  unsigned long pulseAcelerador = pulseIn(pinAcelerador, HIGH);
  unsigned long pulseAdelanteAtras = pulseIn(pinAdelanteAtrasMotor, HIGH);
  unsigned long pulseIzquierdaDerecha = pulseIn(pinIzquierdaDerechaMotor, HIGH);

  // Imprime los valores de los pulsos PWM
  Serial.print("Acelerador: ");
  Serial.print(pulseAcelerador);
  Serial.print(" us, Adelante/Atrás: ");
  Serial.print(pulseAdelanteAtras);
  Serial.print(" us, Izquierda/Derecha: ");
  Serial.print(pulseIzquierdaDerecha);
  Serial.println(" us");

  // Velocidad del motor controlada por el canal del acelerador
  int velocidad = map(pulseAcelerador, 1000, 2000, 0, 1023); // Mapear a rango [-255, 255]

  // Dirección del motor controlada por los canales de adelante/atrás e izquierda/derecha
  int velocidadIzquierda = -velocidad;
  int velocidadDerecha = -velocidad;

  if (pulseAdelanteAtras < 1400) {
    // Retroceder si se inclina hacia atrás
    velocidadIzquierda *= -1;
    velocidadDerecha *= -1;
  }

  
  if (pulseAdelanteAtras > 1600) {
    // Retroceder si se inclina hacia atrás
    velocidadIzquierda *= 1;
    velocidadDerecha *= 1;
  }

  if (pulseIzquierdaDerecha > 1600) {
    // Girar a la izquierda si se inclina hacia la izquierda
    velocidadIzquierda *= -0.6; // Disminuye velocidad del motor izquierdo para girar
    velocidadDerecha *= 1.5; // Disminuye velocidad del motor izquierdo para girar
  } 

   if (pulseIzquierdaDerecha < 1400) {
    // Girar a la izquierda si se inclina hacia la izquierda
    velocidadIzquierda *= 1.5; // Disminuye velocidad del motor izquierdo para girar
    velocidadDerecha *= -0.5; // Disminuye velocidad del motor izquierdo para girar
  } 



  // Llamar a la función para controlar los motores
  controlarMotores(velocidadIzquierda, velocidadDerecha);

  delay(100); // Espera un poco antes de tomar la próxima lectura

}

void controlarMotores(int velocidadMotorIzquierda, int velocidadMotorDerecha) {
  // Control de la dirección para el motor izquierdo
  if (velocidadMotorIzquierda > 0) {
    digitalWrite(IN1_IZQUIERDA, LOW);  // Gira CW
    ledcWrite(IN2_IZQ, abs(velocidadMotorIzquierda));

  } else if (velocidadMotorIzquierda < 0) {
    digitalWrite(IN1_IZQUIERDA, HIGH);  // Gira CCW
    ledcWrite(IN2_IZQ, abs(velocidadMotorIzquierda));
  } else if (velocidadMotorIzquierda == 0) {
    digitalWrite(IN1_IZQUIERDA, BitOff);  // Detén el motor izquierdo
    digitalWrite(IN2_IZQUIERDA, BitOff);
    if (BitOff == true) { ledcWrite(IN2_IZQ, 1023); }  
    else if (BitOff == false) {
      ledcWrite(IN2_IZQ, BitOff);
    }
  }


  // Control de la dirección para el motor derecho
  if (velocidadMotorDerecha > 0) {
    digitalWrite(IN1_DERECHA, LOW);  // Gira hacia adelante
                                     //digitalWrite(IN2_DERECHA, LOW);
    ledcWrite(IN2_DER, abs(velocidadMotorDerecha));
  } else if (velocidadMotorDerecha < 0) {
    //digitalWrite(IN2_DERECHA, HIGH);
    digitalWrite(IN1_DERECHA, HIGH);  // Gira hacia atrás

    ledcWrite(IN2_DER, abs(velocidadMotorDerecha));
  } else if (velocidadMotorDerecha == 0) {
    digitalWrite(IN1_DERECHA, BitOff);  // Detén el motor derecho
    digitalWrite(IN2_DERECHA, BitOff);
    if (BitOff == true) { ledcWrite(IN2_DER, 1023); }  
    else if (BitOff == false) {
      ledcWrite(IN2_DER, BitOff);
    }
  }
}