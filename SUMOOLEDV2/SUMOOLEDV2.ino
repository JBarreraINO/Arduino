//DEFINICIONES
#include <Wire.h>
#include <OLED_I2C.h>
OLED myOLED(21, 22);
extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];
extern uint8_t logo[];
#include <ESP32Servo.h>
//Instanciamos nuestro servo
Servo servo;
int pinServo = 15;
#define s0 16
#define s1 17
#define s2 18
#define s3 19
#define OM 4
// Sensores
int sensores[16];
// Sensores
int frontal = 25;
int derecho = 34;
int izquierdo = 35;
int Dderecho = 13;   // Sensor diagonal derecho
int Dizquierdo = 2;  // Sensor diagonal izquierdo
int Desplegar = 0;
// Sensores de piso
int piso1 = 25;
int piso2 = 15;

// Declaración pines motores
int MOTOR1_IN1 = 27;  // PWM izquierdo
int MOTOR1_IN2 = 26;  // PWM izquierdo
int MOTOR2_IN1 = 32;  // PWM derecho
int MOTOR2_IN2 = 33;  // PWM derecho
#define VELOCIDAD_ATAQUE 1020
#define VELOCIDAD_AVANCE 600
#define VELOCIDAD_BUSQUEDA 800
#define VELOCIDAD_LENTA 200
#define VELOCIDAD_BUSQUEDALENTA 450

bool atacando = false;
bool calibrado = false;

#define DIPSW2 35
#define DIPSW3 5
#define DIPSW4 4

#define LED1 5

uint16_t estado1;
uint16_t estado2;
uint16_t estado3;
int16_t maxs1 = 0;
uint16_t maxs2 = 0;
uint16_t maxs3 = 0;
int16_t mins1 = 0;
uint16_t mins2 = 0;
int16_t mins3 = 0;
int estado1x = 0;
int estado2x = 0;
int estado3x = 0;
int line_data = 2;  // elegir el color de la linea, 2 negro o 1 blanco
// Configuración PWM
const int frecuencia = 5000;
const int resolucion = 10;
const int velMIN = 0;
const int DSC=23;
int dsw;
int opnente_det;
int bandera_inicio;
int bandera_estretegia = 0;
int timeout_str;
int timeout_busqueda;
int control_md, control_mi;
int sens;
#define MODULOSTART 14
// Variables de estado
bool enBorde = false;


int estrategiaSeleccionada;

// ULTIMO SENSOR
int ultimo_sensor = -1;  // -1: ninguno, 0: derecha, 1: izquierda
unsigned long tiempo_ultimo_sensor = 0;
const unsigned long tiempo_max_memoria = 500;  // 1 segundo de memoria activa

bool desplegarBandera = false;  // Bandera para ejecutar solo una vez

unsigned long tiempo_busqueda = 0;
unsigned long intervalo_giro = 400;  // tiempo de giro inicial
unsigned long incremento = 200;      // cuánto se incrementa en cada ciclo
byte sentido_giro = 0;               // 0: derecha, 1: izquierda
unsigned long ultimo_cambio = 0;
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
  pinMode(frontal, INPUT_PULLDOWN);
  pinMode(DSC, INPUT_PULLUP);
  pinMode(derecho, INPUT_PULLDOWN);
  pinMode(izquierdo, INPUT_PULLDOWN);
  pinMode(Dderecho, INPUT_PULLDOWN);
  pinMode(Dizquierdo, INPUT_PULLDOWN);

  pinMode(MODULOSTART, INPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(LED1, OUTPUT);

  // pinMode(DIPSW2, INPUT);
  // pinMode(DIPSW3, INPUT);
  // pinMode(DIPSW4, INPUT);

  // Inicializar motores apagados
  controlarMotores(0, 0);
  myOLED.clrScr();
  int Analogpw = digitalRead(MODULOSTART);
  int DSCR=digitalRead(DSC);
  unsigned long startTime = millis();  // Guardamos el tiempo al inicio del bucle
  while (1) {

    if (DSCR== LOW || Analogpw==HIGH || (millis() - startTime >= 30000)) {
     myOLED.print("Esperando go", CENTER, 56);
      myOLED.update();
      myOLED.clrScr();
      break;
    }
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
      myOLED.printNumI(millis() - startTime, RIGHT, 24);  // Tiempo en segundos a la derecha
    switch (dsw) {
      case 0:
        {  //ESPERAR DE FRENTE --1 3 4 OFF

          timeout_str = 10;
          timeout_busqueda = 500;
          opnente_det = 110;  //OPONENETE A IZQUIERDA
          myOLED.print("esperar de frente", LEFT, 32);
          myOLED.print("1 3 4 OFF", CENTER, 40);
          myOLED.print("caso 0", CENTER, 48);
          desplegarBandera = false;
          Desplegar = 170;
          break;
        }
      case 1:
        {  //OPOENTE DE DERECHA DIAGONAL --2 ON 3 4 OFF
          control_mi = VELOCIDAD_ATAQUE / 2;
          control_md = VELOCIDAD_ATAQUE;
          timeout_str = 500;
          timeout_busqueda = 500;
          opnente_det = 1;  //OPONENETE A DERECHA
          myOLED.print("OP de derecha diagonal", CENTER, 32);
          myOLED.print("1 ON 3 4 OFF", CENTER, 40);
          myOLED.print("caso 1", CENTER, 48);
          desplegarBandera = false;
          Desplegar = 10;
          break;
        }
      case 2:
        {  //OPOENTE DE ATRAS CENTRO DE PISTA - GIRO DE UNA --2 OFF 3ON 4 OFF
         control_md = VELOCIDAD_BUSQUEDA;
          control_mi = VELOCIDAD_BUSQUEDA / 2;
          timeout_str = 160;
          timeout_busqueda = 500;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de espalda GIRO D1", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 OFF", CENTER, 40);
          myOLED.print("caso 2", CENTER, 48);
          desplegarBandera = false;
          Desplegar = 10;
          break;
        }
      case 3:
        {  //OPOENTE DE DERECHA GIRO COMPLETO --2 ON 3ON 4 OFF
          control_md = VELOCIDAD_BUSQUEDA;
          control_mi = -VELOCIDAD_BUSQUEDA;
          timeout_str = 100;
          timeout_busqueda = 500;
          opnente_det = 1;  //OPONENETE A DERECHA
          myOLED.print("OP de derecha giro 180°", CENTER, 32);
          myOLED.print("1 ON 3 ON 4 OFF", CENTER, 40);
          myOLED.print("caso 3", CENTER, 48);
          desplegarBandera = false;
          Desplegar = 170;
          break;
        }
      case 4:
        {
          //OPOENTE DE IZQUIERDA DIAGONAL --2 OFF 3 OFF 4 ON
          control_mi = VELOCIDAD_BUSQUEDA;
          control_md = VELOCIDAD_BUSQUEDA / 2;
          timeout_str = 500;
          timeout_busqueda = 500;
          opnente_det = 100;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de izquierda diagonal ", CENTER, 32);
          myOLED.print("1 OFF 3 OFF 4 ON", CENTER, 40);
           myOLED.print("caso 4", CENTER, 48);
          desplegarBandera = false;
          Desplegar = 170;
          break;
        }
      case 5:
        {  //OPOENTE DE FRENTE EN CENTRO DE PISTA --2 ON 3 OFF 4 ON
          control_md = VELOCIDAD_BUSQUEDA;
          control_mi = VELOCIDAD_BUSQUEDA;
          timeout_str = 100;
          timeout_busqueda = 500;
          opnente_det = 110;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de frente", CENTER, 32);
          myOLED.print("1 ON 3 OFF 4 ON", CENTER, 40);
           myOLED.print("caso 5", CENTER, 48);
          desplegarBandera = false;
          Desplegar = 10;
          break;
        }
      case 6:
        {  //OPOENTE DE IZQUIERDA GIRO TOTAL --2 OFF 3 ON 4 ON
          control_md = -VELOCIDAD_BUSQUEDA;
          control_mi = VELOCIDAD_BUSQUEDA;
          timeout_str = 100;
          timeout_busqueda = 500;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de izquierda giro 180° ", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 ON", CENTER, 40);
           myOLED.print("caso 6", CENTER, 48);
          desplegarBandera = false;
          Desplegar = 10;
          break;
        }
      case 7:
        {  //OPONENTE ATRAS EN BORDE DE PISTA MINISUMO--2 3 4 ON
          control_md = VELOCIDAD_BUSQUEDA;
          control_mi = VELOCIDAD_BUSQUEDA / 2;
          timeout_str = 500;
          timeout_busqueda = 500;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
          myOLED.print("OP atras en borde de pista ", CENTER, 32);
          myOLED.print("1 3 4 ON", CENTER, 40);
           myOLED.print("caso 7", CENTER, 48);
           desplegarBandera = false;
          Desplegar = 170;

          break;
        }
      default:
        {
          opnente_det == 1000;  //OPONENETE A IZQUIERDA
          break;
        }
        myOLED.update();
    }
    ESP32PWM::allocateTimer(3);
    servo.attach(pinServo, 500, 2500);
    servo.write(90);

    DSCR= digitalRead(DSC);
    Analogpw = digitalRead(MODULOSTART);
    
    myOLED.update();
  }

 while (Analogpw == LOW) {
Analogpw = digitalRead(MODULOSTART);
digitalWrite(LED1,HIGH);
    if (Analogpw == HIGH) {

    
      break;
    }
    
  }
  
}
void ejecutarEstrategia() {
  static unsigned long tiempo_inicio = millis();
  unsigned long tiempo_actual = millis();

  estrategiaSeleccionada = leer_dipsw();
  switch (estrategiaSeleccionada) {
    case 0:  // Estrategia 1: ESPERAR DE FRENTE 1 2 3 OFF
     // busquedaestrategica();
      MovDes();
      break;

    case 1:  // Estrategia :derecha diagonL

      if (tiempo_actual - tiempo_inicio < timeout_str) {
        controlarMotores(control_mi, control_md);
      } else if (tiempo_actual - tiempo_inicio < timeout_str + 200) {
        Izquierda();
      } else if (tiempo_actual - tiempo_inicio < timeout_str + 300) {
        Atacar();
      } else {

        controlarMotores(0, 0);
        busquedaestrategica();
        //MovDes();
      }
      break;

    case 2:  // oponeten de espaldas

      if (tiempo_actual - tiempo_inicio < timeout_str) {
      GiroRapidoIZQ();

      } else if (tiempo_actual - tiempo_inicio < timeout_str + timeout_str) {
        Atacar();
      } else {
        controlarMotores(0, 0);
        //MovDes();
        busquedaestrategica();
      }

      break;

    case 3:  //OP de derecha giro 180°
      if (tiempo_actual - tiempo_inicio < timeout_str) {
        GiroRapidoIZQ();
      } else if (tiempo_actual - tiempo_inicio < timeout_str * 3) {
        AvanzarLento();
      } else {
        controlarMotores(0, 0);
        busquedaestrategica();
      }
      break;

    case 4:  //izquierda diagonL
      if (tiempo_actual - tiempo_inicio < timeout_str) {
        controlarMotores(control_mi, control_md);
      } else if (tiempo_actual - tiempo_inicio < timeout_str + 200) {
        Derecha();
      } else if (tiempo_actual - tiempo_inicio < timeout_str + 300) {
        Atacar();
      } else {

        controlarMotores(0, 0);
        // MovDes();
        busquedaestrategica();
      }
      break;

    case 5:  // Estrategia 6: Buscar borde y retroceder
      if (tiempo_actual - tiempo_inicio < 800) {
        Avanzar();
      } else if (tiempo_actual - tiempo_inicio < 1200) {
        Retroceder();
      } else {
        controlarMotores(0, 0);
        //estado_actual = SEARCH;
      }
      break;

    case 6:

      if (tiempo_actual - tiempo_inicio < timeout_str) {
      GiroRapidoDER();
      } else if (tiempo_actual - tiempo_inicio < timeout_str * 3) {
        AvanzarLento();
      } else {
        controlarMotores(0, 0);
        busquedaestrategica();
      }

      break;

    case 7:  // Rodear a partir de la espalda (sin delay)
     // static unsigned long tiempo_anterior = millis();
     // static int estado = 0;  // Subestado para las fases

      // Máquina de estados para la estrategia 7
    
static unsigned long tiempo_anterior = millis();
      static int estado = 1;  // Subestado para las fases

      // Máquina de estados para la estrategia 7
      switch (estado) {
        case 1:  // Girar a la izquierda
          Izquierda();
          if (tiempo_actual - tiempo_anterior >= 100) {
            estado++;
            tiempo_anterior = tiempo_actual;
          }
          break;
        case 2:  // Controlar motores
          controlarMotores(control_mi, control_md);
          if (tiempo_actual - tiempo_anterior >= 550) {
            estado++;
            tiempo_anterior = tiempo_actual;
          }
          break;
        case 3:  // Girar a la izquierda nuevamente
          Izquierda();
          if (tiempo_actual - tiempo_anterior >= 100) {
            estado++;
            tiempo_anterior = tiempo_actual;
          }
          break;
        case 4:  // Atacar
          Atacar();
          if (tiempo_actual - tiempo_anterior >= 160) {
            estado++;
            tiempo_anterior = tiempo_actual;
          }
          break;
        case 5:  // Detener motores y finalizar
          controlarMotores(0, 0);
          //MovDes();    // Llama a la próxima acción
     busquedaestrategica();
          break;
      }
      
      break;


    default:
      MovDes();
      // estado_actual = SEARCH;
      break;
  }
}
// Bucle principal
void loop() {

  int Analogpw = digitalRead(MODULOSTART);
  //Serial.print(" POWER : ");
  //Serial.println(Analogpw);
  if (Analogpw == LOW) {
    servo.write(90);
    controlarMotores(0, 0);
    while (1)
      ;  //SE APAGA
  }



  lectura();
  if (desplegarBandera == false) {  // Verifica si la condición ya se ejecutó
    servo.write(Desplegar);         // Mueve el servo a 90° solo una vez
    desplegarBandera = true;        // Cambia la bandera para no repetir
  }
  if (!calibrado) {
    calibrar();
    calibrado = true;
  }

  estado1x = (estado1 - mins1) * maxs1 / (255 - mins1);
  if (estado1x <= 0) { estado1x = 0; }
  if (estado1x >= 255) { estado1x = 255; }

  estado2x = (estado2 - mins2) * maxs2 / (255 - mins2);
  if (estado2x <= 0) { estado2x = 0; }
  if (estado2x >= 255) { estado2x = 255; }

  //Serial.print("estado1");
  //Serial.print(estado1);
  Serial.print("estadox");
  Serial.println(estado1x);



  // Lectura de sensores al inicio del ciclo
  int senFrontal = digitalRead(frontal);
  int senDerecho = digitalRead(derecho);
  int senDDerecho = digitalRead(Dderecho);
  int senIzquierdo = digitalRead(izquierdo);
  int senDIzquierdo = digitalRead(Dizquierdo);

  // Lógica de control optimizada
  if (atacando == false && (estado1x > sens || estado2x > sens)) {
    enBorde = true;
    Serial.println("Borde detectado");
    Retroceder();
  } else if (atacando == false && enBorde) {
    Serial.println("Saliendo del borde, retomando estrategia");
    retornar();  // vuelve a su estrategia
    enBorde = false;
  }

  else if (senFrontal == 1) {
    Atacar();
    atacando = true;
  } else if (atacando && senFrontal == 0) {
    atacando = false;
  }

  else if (senDerecho == 1) {
    Derecha();
    ultimo_sensor = 0;
  }

  else if (senDDerecho == 1) {
    DerechaLento();
    ultimo_sensor = 0;
  }

  else if (senIzquierdo == 1) {
    Izquierda();
    ultimo_sensor = 1;
  }

  else if (senDIzquierdo == 1) {
    IzquierdaLento();
    ultimo_sensor = 1;
  }

  else if ((senFrontal == 1) && (senDIzquierdo == 1)) {
    Avanzar();
  }

  else if ((senFrontal == 1) && (senDDerecho == 1)) {
    Avanzar();
  }

  else if ((senFrontal == 1) && (senDDerecho == 1) && (senDIzquierdo == 1)) {
    Atacar();
  }

  else if ((millis() - tiempo_ultimo_sensor < tiempo_max_memoria) && ultimo_sensor != -1) {
    atacando = false;
    if (ultimo_sensor == 0) {
      DerechaLento();  // Lo vio por la derecha
    } else if (ultimo_sensor == 1) {
      IzquierdaLento();  // Lo vio por la izquierda
    }
  }

  else {
    atacando = false;
    ejecutarEstrategia();

    if (bandera_estretegia == 1) {
      busquedaestrategica();
    }
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
  controlarMotores(VELOCIDAD_AVANCE, VELOCIDAD_AVANCE);
}

void Atacar() {
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
  controlarMotores(VELOCIDAD_BUSQUEDA, -VELOCIDAD_BUSQUEDA);
}

void DerechaLento() {
  controlarMotores(VELOCIDAD_BUSQUEDALENTA, -VELOCIDAD_BUSQUEDALENTA);
}

void Izquierda() {
  controlarMotores(-VELOCIDAD_BUSQUEDA, VELOCIDAD_BUSQUEDA);
}

void IzquierdaLento() {
  controlarMotores(-VELOCIDAD_BUSQUEDALENTA, VELOCIDAD_BUSQUEDALENTA);
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
void RetrocederLento() {
  controlarMotores(-VELOCIDAD_LENTA, -VELOCIDAD_LENTA);
}

void GiroRapidoIZQ()
{
  controlarMotores(-VELOCIDAD_ATAQUE,VELOCIDAD_ATAQUE);
}

void GiroRapidoDER()
{
  controlarMotores(VELOCIDAD_ATAQUE,-VELOCIDAD_ATAQUE);
}

void MovDes() {
  static unsigned long tiempoAnterior = millis();  // Tiempo de la última transición
  static int avanzando = 0;                        // Estado actual (0: detener, 1: avanzar, 2: retroceder)

  unsigned long tiempoActual = millis();  // Tiempo actual

  // Verifica si ha pasado el tiempo necesario para cambiar de estado
  if (tiempoActual - tiempoAnterior >= timeout_str) {
    tiempoAnterior = tiempoActual;  // Actualiza el tiempo de la última transición
    avanzando++;                    // Cambia al siguiente estado

    if (avanzando > 10) {  // Reinicia la secuencia después del último estado
      avanzando = 0;
    }
  }

  // Realiza la acción correspondiente al estado actual
  if (avanzando == 1) {
    AvanzarLento();  // Robot avanza lentamente
  } else if (avanzando == 2) {
    controlarMotores(-VELOCIDAD_LENTA, -VELOCIDAD_LENTA);  // Robot retrocede lentamente
  } else if (avanzando == 3) {
    controlarMotores(0, 0);  // Robot se detiene
  }
}

void busquedaestrategica() {
  static unsigned long tiempoAnterior = millis();  // Tiempo de la última transición
  static int avanzando = 0;                        // Estado actual (0: detener, 1: avanzar, 2: retroceder)

  unsigned long tiempoActual = millis();  // Tiempo actual

  // Verifica si ha pasado el tiempo necesario para cambiar de estado
  if (tiempoActual - tiempoAnterior >= timeout_str) {
    tiempoAnterior = tiempoActual;  // Actualiza el tiempo de la última transición
    avanzando++;                    // Cambia al siguiente estado

    if (avanzando > 8) {  // Reinicia la secuencia después del último estado
      avanzando = 0;
    }
  }

  // Realiza la acción correspondiente al estado actual
  if (avanzando == 1) {
    AvanzarLento();
  }  // Robot avanza lentamente
  else if (avanzando == 2) {
    IzquierdaLento();
  } else if (avanzando == 3) {
    DerechaLento();
  } else if (avanzando == 4) {
    DerechaLento();
  } else if (avanzando == 5) {
    IzquierdaLento();
  }
}

void busquedaestrategica2() {
  if (millis() - ultimo_cambio >= intervalo_giro) {
    ultimo_cambio = millis();

    if (sentido_giro == 0) {
      DerechaLento();
      sentido_giro = 1;
    } else {
      IzquierdaLento();
      sentido_giro = 0;
    }

    intervalo_giro += incremento;  // hace que busque en arcos más amplios
  }
}



void retornar() {

  Izquierda();
  delay(100);
}

void calibrar() {
  lectura();
  //if (estado1 > maxs1) { maxs1 = estado1; }
  if (estado1 > mins1) { mins1 = estado1; }

  //if (estado2 > maxs2) { maxs2 = estado2; }
  if (estado2 > mins2) { mins2 = estado2; }

  if (estado3 > mins3) { mins3 = estado3; }
  maxs1 = 255 + mins1;
  maxs2 = 255 + mins2;
  maxs3 = 255 + mins3;

  Serial.print("calibre");
  Serial.print(maxs1);
}

void lectura() {
  for (int i = 0; i < 16; i++) {
    digitalWrite(s0, i & 0x01);
    digitalWrite(s1, i & 0x02);
    digitalWrite(s2, i & 0x04);
    digitalWrite(s3, i & 0x08);

    sensores[i] = analogRead(OM);

    //Serial.print(sensores[i]);
    //Serial.print("\t");
  }
  Serial.println(" ");

  estado1 = (sensores[9] / 16);
  estado2 = (sensores[10] / 16);
  estado3 = (sensores[11] / 16);
  sens=15;
  //Serial.print(estado1);
  // Serial.print("\t");

  // 2 para linea negre, el robot normalmente da maximo en blanco minimo en negro
  if (line_data == 2) {
    sens=230;
    estado1 = abs(256 - estado1);
    estado2 = abs(256 - estado2);
    estado3 = abs(256 - estado3);
  }
}
int leer_dipsw(void) {

  int value;
  int buttonState = sensores[0];
  // Serial.print("  SW2 : ");
  //Serial.print(buttonState);
  if (buttonState > 0) {
   
    value = 0;
  } else {
   
    value = 1;
  }

  buttonState = sensores[1];
  //Serial.print("  SW3 : ");
  //Serial.print(buttonState);
  if (buttonState > 0) {

  } else {

    value = value + 2;
  }

  buttonState = sensores[2];
  //Serial.print("  SW4 : ");
  //Serial.print(buttonState);
  if (buttonState > 0) {
    //digitalWrite(LED2, HIGH);
  } else {
    //digitalWrite(LED2, HIGH);
    value = value + 4;
  }

  return value;
}
