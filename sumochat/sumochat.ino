
//DEFINICIONES
#include <Wire.h>
#include <OLED_I2C.h>
OLED myOLED(21, 22);
extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];
extern uint8_t logo[];
// Sensores

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
int MOTOR1_IN1 = 27;  // PWM izquierdo
int MOTOR1_IN2 = 26;  // PWM izquierdo
int MOTOR2_IN1 = 32;  // PWM derecho
int MOTOR2_IN2 = 33;  // PWM derecho
#define VELOCIDAD_ATAQUE 900
#define VELOCIDAD_BUSQUEDA 700
#define VELOCIDAD_LENTA 200
#define DIPSW2 35
#define DIPSW3 5
#define DIPSW4 4
#define LED1 2

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
int dsw;
int estrategiaSeleccionada;
int opnente_det;
int bandera_inicio;
int timeout_str;
int control_md, control_mi;
const int sens = 12;
#define MODULOSTART 14
// Variables de estado
int ultimo_sensor = -1;  // Último sensor que detectó al oponente (-1: ninguno)
enum Estados { IDLE,
               STRATEGY,
               SEARCH,
               ATTACK,
               AVOID_EDGE };
Estados estado_actual = IDLE;
bool estrategia_completada = false;  // Para asegurarnos de que solo se ejecute una vez

// Configuración inicial
void setup() {
  controlarMotores(0, 0);
  Wire.begin();

  myOLED.begin();
  myOLED.clrScr();
  myOLED.drawBitmap(0, 0, logo, 128, 64);
  myOLED.update();
  myOLED.setFont(SmallFont);
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

  pinMode(LED1, OUTPUT);


  pinMode(DIPSW2, INPUT);
  pinMode(DIPSW3, INPUT);
  pinMode(DIPSW4, INPUT);
  // Inicializar motores apagados
  controlarMotores(0, 0);
  myOLED.clrScr();
  int Analogpw = digitalRead(MODULOSTART);
  while (Analogpw == LOW) {
    myOLED.clrScr();
    lectura();
    myOLED.setFont(TinyFont);
    myOLED.print("calibrado:", LEFT, 0);
    myOLED.print("VAL:", CENTER, 0);
    myOLED.print("MIN:", 80, 0);
    myOLED.print("MAX:", RIGHT, 0);


    myOLED.print("izquierda", LEFT, 8);
    myOLED.printNumI(estado1, CENTER, 8);
    myOLED.printNumI(mins1, 80, 8);
    myOLED.printNumI(maxs1, RIGHT, 8);

    myOLED.print("derecha", LEFT, 16);
    myOLED.printNumI(estado2, CENTER, 16);
    myOLED.printNumI(mins2, 80, 16);
    myOLED.printNumI(maxs2, RIGHT, 16);
    myOLED.drawLine(0, 22, 128, 22);


    //LEER ESTRATEGIA
    dsw = leer_dipsw();
    bandera_inicio = 1;
    myOLED.print("Estrategia:", LEFT, 24);
    switch (dsw) {
      case 0:
        {  //ESPERAR DE FRENTE --1 3 4 OFF

          myOLED.print("esperar de frente", LEFT, 32);
          myOLED.print("1 3 4 OFF", CENTER, 40);



          break;
        }
      case 1:
        {  //OPOENTE DE DERECHA DIAGONAL --2 ON 3 4 OFF

          timeout_str = 300;
          opnente_det = 1;  //OPONENETE A DERECHA
          myOLED.print("OP de derecha diagonal", CENTER, 32);
          myOLED.print("1 ON 3 4 OFF", CENTER, 40);
          break;
        }
      case 2:
        {  //OPOENTE DE ATRAS CENTRO DE PISTA - GIRO DE UNA --2 OFF 3ON 4 OFF

          myOLED.print("OP de espalda GIRO D1", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 OFF", CENTER, 40);
          break;
        }
      case 3:
        {  //OPOENTE DE DERECHA GIRO COMPLETO --2 ON 3ON 4 OFF

          myOLED.print("OP de derecha giro 360°", CENTER, 32);
          myOLED.print("1 ON 3 ON 4 OFF", CENTER, 40);
          break;
        }
      case 4:
        {

          myOLED.print("OP de izquierda diagonal ", CENTER, 32);
          myOLED.print("1 OFF 3 OFF 4 ON", CENTER, 40);
          break;
        }
      case 5:
        {  //OPOENTE DE FRENTE EN CENTRO DE PISTA --2 ON 3 OFF 4 ON

          myOLED.print("OP de frente", CENTER, 32);
          myOLED.print("1 ON 3 OFF 4 ON", CENTER, 40);
          break;
        }
      case 6:
        {  //OPOENTE DE IZQUIERDA GIRO TOTAL --2 OFF 3 ON 4 ON

          myOLED.print("OP de izquierda giro 360° ", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 ON", CENTER, 40);
          break;
        }
      case 7:
        {  //OPONENTE ATRAS EN BORDE DE PISTA MINISUMO--2 3 4 ON

          myOLED.print("OP atras en borde de pista ", CENTER, 32);
          myOLED.print("1 3 4 ON", CENTER, 40);

          break;
        }
      default:
        {
          opnente_det == 1000;  //OPONENETE A IZQUIERDA
          break;
        }
        myOLED.update();
    }


    Analogpw = digitalRead(MODULOSTART);
    myOLED.print("Esperando go...", CENTER, 56);
    myOLED.update();
    if (Analogpw == HIGH) {
      calibrar();
      myOLED.clrScr();
    }
  }
}
void ejecutarEstrategia() {
  static unsigned long tiempo_inicio = millis();
  unsigned long tiempo_actual = millis();
  estrategiaSeleccionada = leer_dipsw();
  switch (estrategiaSeleccionada) {
    case 0:  // Estrategia 1: Avanzar directamente
      if (tiempo_actual - tiempo_inicio < 1000) {
        AvanzarLento();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    case 1:  // Estrategia 2: Rotación completa
      if (tiempo_actual - tiempo_inicio < 1000) {
        Derecha();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    case 2:  // Estrategia 3: Zigzag
      if (tiempo_actual - tiempo_inicio < 700) {
        Avanzar();
      } else if (tiempo_actual - tiempo_inicio < 1000) {
        Izquierda();
      } else if (tiempo_actual - tiempo_inicio < 1700) {
        Avanzar();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    case 3:  // Estrategia 4: Giro inicial hacia la derecha
      if (tiempo_actual - tiempo_inicio < 500) {
        Derecha();
      } else if (tiempo_actual - tiempo_inicio < 1500) {
        Avanzar();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    case 4:  // Estrategia 5: Giro inicial hacia la izquierda
      if (tiempo_actual - tiempo_inicio < 500) {
        Izquierda();
      } else if (tiempo_actual - tiempo_inicio < 1500) {
        Avanzar();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    case 5:  // Estrategia 6: Buscar borde y retroceder
      if (tiempo_actual - tiempo_inicio < 800) {
        Avanzar();
      } else if (tiempo_actual - tiempo_inicio < 1200) {
        Retroceder();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    case 6:  // Estrategia 7: Movimiento aleatorio
      if (tiempo_actual - tiempo_inicio < 700) {
        Avanzar();
      } else if (tiempo_actual - tiempo_inicio < 1000) {
        (random(0, 2) == 0) ? Izquierda() : Derecha();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    case 7:  // Estrategia 8: Búsqueda lenta y precisa
      if (tiempo_actual - tiempo_inicio < 1000) {
        AvanzarLento();
      } else {
        controlarMotores(0, 0);
        estado_actual = SEARCH;
      }
      break;

    default:
      controlarMotores(0, 0);
      estado_actual = SEARCH;
      break;
  }
}

// Bucle principal
void loop() {

  int Analogpw = digitalRead(MODULOSTART);
  //Serial.print(" POWER : ");
  //Serial.println(Analogpw);
  if (Analogpw == LOW) {
    controlarMotores(0, 0);
    while (1)
      ;  //SE APAGA
  }

  lectura();
  estado1x = (estado1 - mins1) * maxs1 / (255 - mins1);
  if (estado1x <= 0) { estado1x = 0; }
  if (estado1x >= 255) { estado1x = 255; }


  estado2x = (estado2 - mins2) * maxs2 / (255 - mins2);
  if (estado2x <= 0) { estado2x = 0; }
  if (estado2x >= 255) { estado2x = 255; }
  /*

  myOLED.print("VAL:", CENTER, 0);
  myOLED.print("MIN:", 80, 0);
  myOLED.print("MAX:", RIGHT, 0);


  myOLED.print("izquierda", LEFT, 8);
  myOLED.print("   ", CENTER, 8);
  myOLED.printNumI(estado1x, CENTER, 8);
  myOLED.printNumI(mins1, 80, 8);
  myOLED.printNumI(maxs1, RIGHT, 8);

  myOLED.print("derecha", LEFT, 16);
  myOLED.print("   ", CENTER, 16);
  myOLED.printNumI(estado2x, CENTER, 16);
  myOLED.printNumI(mins2, 80, 16);
  myOLED.printNumI(maxs2, RIGHT, 16);
  myOLED.drawLine(0, 22, 128, 22);
  */
  //ESTARTEGIA DE INICIO
  switch (estado_actual) {
    case IDLE:
      controlarMotores(0, 0);
      if (Analogpw == HIGH) {
        estado_actual = STRATEGY;
        estrategia_completada = false;  // Reiniciar estrategia
      }
      break;

    case STRATEGY:
      ejecutarEstrategia();
      break;

    case SEARCH:
      buscarOponente();
      break;

    case ATTACK:
      atacar();
      break;

    case AVOID_EDGE:
      evitarCaida();
      break;
  }
}


// Funciones de movimiento
void controlarMotores(int velIzq, int velDer) {
  ledcWrite(0, velIzq > 0 ? velIzq : 0);
  ledcWrite(1, velIzq < 0 ? -velIzq : 0);
  ledcWrite(2, velDer > 0 ? velDer : 0);
  ledcWrite(3, velDer < 0 ? -velDer : 0);
  /*
  myOLED.setFont(TinyFont);
  myOLED.print("     ", LEFT, 32);
  myOLED.print("     ", RIGHT, 32);
  myOLED.printNumI(velIzq, LEFT, 32);
  myOLED.printNumI(velDer, RIGHT, 32);
  myOLED.update();*/
}

void Avanzar() {
  controlarMotores(VELOCIDAD_ATAQUE, VELOCIDAD_ATAQUE);
}

void Retroceder() {
  controlarMotores(-VELOCIDAD_ATAQUE, -VELOCIDAD_ATAQUE);
}

void RetrocederDerecha() {
  controlarMotores(-VELOCIDAD_ATAQUE / 2, -VELOCIDAD_ATAQUE);
}

void RetrocederIzquierda() {
  controlarMotores(-VELOCIDAD_ATAQUE, -VELOCIDAD_ATAQUE / 2);
}

void Derecha() {
  controlarMotores(VELOCIDAD_ATAQUE, -VELOCIDAD_ATAQUE);
}

void DerechaLento() {
  controlarMotores(VELOCIDAD_BUSQUEDA, -VELOCIDAD_BUSQUEDA);
}

void Izquierda() {
  controlarMotores(-VELOCIDAD_ATAQUE, VELOCIDAD_ATAQUE);
}

void IzquierdaLento() {
  controlarMotores(-VELOCIDAD_BUSQUEDA, VELOCIDAD_BUSQUEDA);
}

void Parar() {
  controlarMotores(0, 0);
}
void avanceconestrategia() {
  controlarMotores(control_mi, control_md);
}
void AvanzarLento() {
  controlarMotores(VELOCIDAD_LENTA, VELOCIDAD_LENTA);
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
int leer_dipsw(void) {
  int value;
  int buttonState = digitalRead(DIPSW2);
  Serial.print("  SW2 : ");
  Serial.print(buttonState);
  if (buttonState > 0) {
    digitalWrite(LED1, LOW);
    value = 0;
  } else {
    digitalWrite(LED1, HIGH);
    value = 1;
  }

  buttonState = digitalRead(DIPSW3);
  Serial.print("  SW3 : ");
  Serial.print(buttonState);
  if (buttonState > 0) {

  } else {

    value = value + 2;
  }

  buttonState = digitalRead(DIPSW4);
  Serial.print("  SW4 : ");
  Serial.print(buttonState);
  if (buttonState > 0) {
    //digitalWrite(LED2, HIGH);
  } else {
    //digitalWrite(LED2, HIGH);
    value = value + 4;
  }

  return value;
}

void buscarOponente() {
  if (digitalRead(piso1) == HIGH || digitalRead(piso2) == HIGH) {
    estado_actual = AVOID_EDGE;  // Cambiar al estado de evitar borde
  } else if (digitalRead(frontal) == HIGH) {
    estado_actual = ATTACK;  // Cambiar al estado de ataque
  } else if (digitalRead(izquierdo) == HIGH) {
    Izquierda();  // Girar hacia la izquierda
    ultimo_sensor = 1;
  } else if (digitalRead(derecho) == HIGH) {
    Derecha();  // Girar hacia la derecha
    ultimo_sensor = 0;
  } else if (digitalRead(Dizquierdo) == HIGH) {
    IzquierdaLento();
    ultimo_sensor = 1;
  } else if (digitalRead(Dderecho) == HIGH) {
    DerechaLento();
    ultimo_sensor = 0;
  } else if (ultimo_sensor == 0 && digitalRead(piso1) == LOW && digitalRead(piso1) == LOW) {
    DerechaLento();
  } else if (ultimo_sensor == 1 && digitalRead(piso1) == LOW && digitalRead(piso1) == LOW) {
    IzquierdaLento();
  }
}


void atacar() {
  if (digitalRead(piso1) == HIGH || digitalRead(piso2) == HIGH) {
    estado_actual = AVOID_EDGE;  // Cambiar al estado de evitar borde
  } else if (digitalRead(frontal) == HIGH) {
    Avanzar();  // Atacar directamente
  } else if ((digitalRead(frontal) == 1) && (digitalRead(Dizquierdo) == 1)) {
    Avanzar();
    ;
  } else if ((digitalRead(frontal) == 1) && (digitalRead(Dderecho) == 1)) {
    Avanzar();
    ;
  } else if ((digitalRead(frontal) == 1) && (digitalRead(Dderecho) == 1) && (digitalRead(Dizquierdo) == 1)) {
    Avanzar();
    ;
  } else {
    estado_actual = SEARCH;  // Si no ve al oponente, volver a buscar
  }
}

void evitarCaida() {
  if (digitalRead(piso1) == HIGH && digitalRead(piso2) == HIGH) {
    Retroceder();
  // Ajusta la dirección para volver al área segura
  } else if (digitalRead(piso1) == HIGH) {
    RetrocederDerecha();  // Mueve hacia la derecha
  } else if (digitalRead(piso2) == HIGH) {
    RetrocederIzquierda();  // Mueve hacia la izquierda
  } else {
    estado_actual = SEARCH;
  }
}
