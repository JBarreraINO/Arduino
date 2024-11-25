


// Sensores
int frontal = 18;
int derecho = 23;
int izquierdo = 16;
int Dderecho = 19;    // Sensor diagonal derecho
int Dizquierdo = 17;  // Sensor diagonal izquierdo

// Sensores de piso
int piso1 = 25;
int piso2 = 15;

// Declaración pines motores
int MOTOR1_IN1 = 26;  // PWM izquierdo
int MOTOR1_IN2 = 27;  // PWM izquierdo
int MOTOR2_IN1 = 33;  // PWM derecho
int MOTOR2_IN2 = 32;  // PWM derecho

uint16_t estado1;
uint16_t estado2;
int16_t maxs1 = 0;
uint16_t maxs2 = 0;
int16_t mins1 = 0;
uint16_t mins2 = 0;
int estado1x = 0;
int estado2x = 0;
int line_data = 1;  // elegir el color de la linea, 2 negro o 1 blanco
// Configuración PWM
const int frecuencia = 5000;
const int resolucion = 10;
const int velMIN = 0;

const int sens = 12;
#define MODULOSTART 14
// Variables de estado
int ultimo = -1;  // Último sensor que detectó al oponente (-1: ninguno)

// Configuración inicial
void setup() {
  Serial.begin(9600);
  // Configurar PWM para motores
  ledcSetup(0, frecuencia, resolucion);
  ledcSetup(1, frecuencia, resolucion);
  ledcSetup(2, frecuencia, resolucion);
  ledcSetup(3, frecuencia, resolucion);

  ledcAttachPin(MOTOR1_IN1, 0);
  ledcAttachPin(MOTOR1_IN2, 1);
  ledcAttachPin(MOTOR2_IN1, 2);
  ledcAttachPin(MOTOR2_IN2, 3);

  // Configurar sensores como entradas
  pinMode(frontal, INPUT_PULLUP);
  pinMode(derecho, INPUT_PULLUP);
  pinMode(izquierdo, INPUT_PULLUP);
  pinMode(Dderecho, INPUT_PULLUP);
  pinMode(Dizquierdo, INPUT_PULLUP);
  pinMode(piso1, INPUT);
  pinMode(piso2, INPUT);
  pinMode(MODULOSTART, INPUT);
  // Inicializar motores apagados
  controlarMotores(0, 0);

  int Analogpw = digitalRead(MODULOSTART);
  while (Analogpw == LOW) {
    Serial.print(" POWER : ");
    Serial.println(Analogpw);
    Analogpw = digitalRead(MODULOSTART);
    controlarMotores(0, 0);
       if (Analogpw == HIGH) {
      calibrar();
    }
  }
}

// Bucle principal
void loop() {

  int Analogpw = digitalRead(MODULOSTART);
  //Serial.print(" POWER : ");
  //Serial.println(Analogpw);
  if (Analogpw == LOW) {
    controlarMotores(0, 0);
    while (1);  //SE APAGA
 
  }

  lectura();
  estado1x = (estado1 - mins1) * maxs1 / (255 - mins1);
  if (estado1x <= 0) { estado1x = 0; }
  if (estado1x >= 255) { estado1x = 255; }


  estado2x = (estado2 - mins2) * maxs2 / (255 - mins2);
  if (estado2x <= 0) { estado2x = 0; }
  if (estado2x >= 255) { estado2x = 255; }


  if (estado1x > sens && estado2x > sens)  //Los sensores de piso detectaron el borde
  { Retroceder(); }                        //El robot debe retroceder

  else if (estado1x > sens)  //Los sensores de piso detectaron el borde
  {
    RetrocederDerecha();
  }  //El robot debe retroceder

  else if (estado2x > sens)   //Los sensores de piso detectaron el borde
  { RetrocederIzquierda(); }  //El robot debe retroceder


  else if (digitalRead(frontal) == 1)  //El sensor frontal detecto al oponente (EL VALOR CAMBIA DEPENDEINDO DEL SENSOR EN MI CASO MI SENSOR TIENE VALOR DE 100 O MAYOR CUANDO DETECTA ALGO)
  {
    Avanzar();
  }  //El robot debe avanzar y embestir al oponente y recordar el ultimo sensor que lo vio

  else if (digitalRead(derecho) == 1)  //El sensor derecho detecto al oponente
  {
    Derecha();  //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar
    ultimo = 0;
  }  //El robot debe recordar el ultimo sensor que vio al oponente para encontrarlo mas rapido

  else if (digitalRead(Dderecho) == 1)  //El sensor derecho diagonal detecto al oponente
  {
    DerechaLento();
    ultimo = 0;
  }  //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar  (la velocidad se reduce para que el robot no termine girando por accidente)

  else if (digitalRead(izquierdo) == 1)  //El sensor izquierdo detecto al oponente
  {
    Izquierda();  //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar
    ultimo = 1;
  }  //El robot debe recordar el ultimo sensor que vio al oponente para encontrarlo mas rapido

  else if (digitalRead(Dizquierdo) == 1)  //El sensor izquierdo diagonal detecto al oponente
  {
    IzquierdaLento();
    ultimo = 1;
  }  //El robot debe girar para que el sensor frontal pueda detectar al oponente y atacar  (la velocidad se reduce para que el robot no termine girando por accidente)



  else if ((digitalRead(frontal) == 1) && (digitalRead(Dizquierdo) == 1)) {
    Avanzar();
    ;
  } else if ((digitalRead(frontal) == 1) && (digitalRead(Dderecho) == 1)) {
    Avanzar();
    ;
  } else if ((digitalRead(frontal) == 1) && (digitalRead(Dderecho) == 1) && (digitalRead(Dizquierdo) == 1)) {
    Avanzar();
    ;
  }

  else if (ultimo == 0)  //El robot recuerda que vio al oponente con su sensor derecho
  {
    DerechaLento();
  } else if (ultimo == 1)  //El robot recuerda que vio al oponente con su sensor izquierdo
  {
    IzquierdaLento();
  }


  else {
    { Parar(); }
  }
}


// Funciones de movimiento
void controlarMotores(int velIzq, int velDer) {
  ledcWrite(0, velIzq > 0 ? velIzq : 0);
  ledcWrite(1, velIzq < 0 ? -velIzq : 0);
  ledcWrite(2, velDer > 0 ? velDer : 0);
  ledcWrite(3, velDer < 0 ? -velDer : 0);
}

void Avanzar() {
  controlarMotores(800, 800);
}

void Retroceder() {
  controlarMotores(-800, -800);
}

void RetrocederDerecha() {
  controlarMotores(-600, -800);
}

void RetrocederIzquierda() {
  controlarMotores(-800, -600);
}

void Derecha() {
  controlarMotores(800, -800);
}

void DerechaLento() {
  controlarMotores(600, -600);
}

void Izquierda() {
  controlarMotores(-800, 800);
}

void IzquierdaLento() {
  controlarMotores(-600, 600);
}

void Parar() {
  controlarMotores(0, 0);
}
void calibrar() {
  lectura();
  //if (estado1 > maxs1) { maxs1 = estado1; }
  if (estado1 > mins1) { mins1 = estado1; }

  //if (estado2 > maxs2) { maxs2 = estado2; }
  if (estado2 > mins2) { mins2 = estado2; }

  maxs1 = 255 + mins1;
  maxs2 = 255 + mins2;
}

void lectura() {
  estado1 = analogRead(piso1) / 16;
  estado2 = analogRead(piso2) / 16;



  // 2 para linea negre, el robot normalmente da maximo en blanco minimo en negro
  if (line_data == 2) {

    estado1 = abs(255 - estado1);
    estado2 = abs(255 - estado2);
  }
}
