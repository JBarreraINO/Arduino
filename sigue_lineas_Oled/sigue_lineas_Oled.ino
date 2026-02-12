//*********PARAMTROS A CALIBRAR *************************************************************************************************
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define BUZZER_PIN 3
long G3  = 196.00,
     Gb3 = 207.65,
     Ab3 = 233.08,
     C   = 261.63,
     D   = 293.67,
     Db  = 311.13,
     E   = 329.63,
     F   = 349.23,
     G   = 392.00,
     Gb  = 415.31,
     Ab  = 440.00,
     C5  = 523.25,
     D5  = 587.33,
     Db5 = 622.25,
     E5  = 659.26,
     G5  = 783.99,
     Gb5 = 830.61,
     Ab5 = 932.33,
     C6  = 1046.5,
     pau = 10; // pausa (no se usa en tone)
// Melodía de Victoria de Super Mario
// Secuencia parecida al Flagpole de Mario
long melodia[] = {
  G3,  C,   E,   G,   C5,  E5,  G5,  E5,  0,
  Gb3, C,   Db,  Gb,  C5,  Db5, Gb5, Db5, 0,
  Ab3, D,   F,   Ab,  D5,  Ab5, Ab5, Ab5, Ab5, C6
};

// Tiempos (ms)
int b = 900, n = 500, w = 200, s = 220; 

int tiempo[] = {
  w, w, w, w, w, w, n, n, n,
  w, w, w, w, w, w, n, n, n,
  w, w, w, w, w, n, s, s, s, b
};


// Duración de cada nota (misma cantidad de elementos que melody[])
int noteDurations[] = {
  8, 8, 8, 8, 4, 8, 8, 8, 8, 4
};
#define OLED_RESET -1
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
int velocidad = 30;  // Velocidad crucero de robot max 255

float Kp = 0.1;  // calibracion proporciona0.7
float Kd = 3;    //  calibracion derivativo9.65

int frente = 70;   // Velocidad a la que ira el motor hacia adelante cuando pierda la linea max 255
int reversa = 78;  // Velocidad a la que ira el motor hacia atras cuando pierda la linea    max 255

int color = 1;  // 1 linea negra 2 linea blanca
//********CONEXION DE PUERTOS****************************************************************************************************
int OP = A3;  // A0 conectdado a OP    SALIDA DEL MULTIPLEXOR
int S0 = A0;  // A4 conectado a S0     S0 DEL MULTIPLEXOR
int S1 = A1;  // A3 conectado a S1     S1 DEL MULTIPLEXOR
int S2 = A2;  // A1 conectado a S2     S2 DEL MULTIPLEXOR

int led = 13;  // Led default de Arduino

int pini = 9;
int pwmi = 6;
int pind = 10;
int pwmd = 5;

int go = 8;  // Puerto donde se conecta el arrancador ( si el modulo no esta conectado, debe ponerse una resistencia pull-down)
int rdy = 12;
int boton_izq = 7;  // boton izquierdo
//int boton_der = 7; // boton derecho
//int lon = 11;
//*******VARIABLES A UTILIZAR****************************************************************************************************


const unsigned char leon[] PROGMEM = {
  // 'pngtree-lion-head-face-logo-silhouette-black-icon-tattoo-mascot-hand-drawn-png-image_12372021, 128x64px
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0e, 0x38, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xc0, 0x0f, 0xec, 0x01, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xfc, 0x0f, 0xf0, 0x0f, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xfe, 0x01, 0xff, 0xfe, 0x1b, 0xe0, 0x3f, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x03, 0xff, 0x09, 0xc0, 0x7f, 0xf0, 0x00, 0x7f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xf1, 0x81, 0xc0, 0xe3, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x01, 0x08, 0x40, 0x80, 0x8c, 0x40, 0x00, 0x3f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf8, 0xff, 0xf0, 0x00, 0x00, 0x80, 0x00, 0x03, 0xff, 0xcf, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf3, 0x83, 0x86, 0x00, 0x00, 0x00, 0x00, 0x18, 0x70, 0x73, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xc6, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x31, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x06, 0x18, 0x00, 0x07, 0xf8, 0x07, 0xf0, 0x00, 0x06, 0x18, 0x7f, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0x06, 0x10, 0x00, 0x01, 0xff, 0x3f, 0xc0, 0x00, 0x02, 0x10, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xfc, 0x00, 0x10, 0x00, 0x1f, 0xfc, 0x0f, 0xfe, 0x00, 0x02, 0x20, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x7f, 0xfe, 0x3f, 0xff, 0x80, 0x00, 0x00, 0xcf, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x01, 0x00, 0xfc, 0xff, 0x3f, 0xdf, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0x11, 0x02, 0x03, 0xc0, 0x3f, 0x7f, 0x00, 0xe0, 0x10, 0x62, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xfc, 0x6e, 0x0c, 0x83, 0x00, 0x3f, 0xfe, 0x00, 0x30, 0x4c, 0x1d, 0x8f, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0xf0, 0x3a, 0x07, 0xf0, 0x1f, 0xfe, 0x03, 0xf8, 0x37, 0x03, 0xc7, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x81, 0xec, 0x07, 0xff, 0x1f, 0xfc, 0x3f, 0xf8, 0x0f, 0xe0, 0xf7, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0x0f, 0xf0, 0x07, 0xff, 0x1f, 0xfe, 0x3f, 0xf8, 0x03, 0xfc, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0x7f, 0xe1, 0x03, 0xfe, 0x3f, 0xfe, 0x3f, 0xf0, 0x21, 0xff, 0x07, 0xff, 0xff,
  0xff, 0xff, 0xf0, 0x1f, 0x86, 0x00, 0xfc, 0x7f, 0xff, 0x1f, 0x80, 0x30, 0x7e, 0x03, 0xff, 0xff,
  0xff, 0xff, 0xe0, 0xfe, 0x0e, 0x00, 0x38, 0xff, 0xff, 0xc7, 0x00, 0x9c, 0x3f, 0x81, 0xff, 0xff,
  0xff, 0xff, 0xc1, 0xcc, 0x3d, 0x80, 0x71, 0xc0, 0xc0, 0xe2, 0x00, 0x6f, 0x0c, 0xe0, 0xff, 0xff,
  0xff, 0xff, 0x87, 0x18, 0xff, 0x00, 0x23, 0xc0, 0x00, 0xf2, 0x00, 0x3f, 0x86, 0x70, 0xff, 0xff,
  0xff, 0xff, 0x86, 0x21, 0xfe, 0x00, 0x01, 0xf8, 0x07, 0xe0, 0x00, 0x1f, 0xe2, 0x18, 0x7f, 0xff,
  0xff, 0xff, 0x8c, 0x03, 0xfc, 0x00, 0x01, 0xfe, 0x1f, 0xe0, 0x00, 0x1f, 0xf0, 0x1c, 0x7f, 0xff,
  0xff, 0xff, 0x9c, 0x07, 0xfc, 0x10, 0x03, 0xff, 0x3f, 0xf0, 0x02, 0x0f, 0xf8, 0x0e, 0xff, 0xff,
  0xff, 0xff, 0xd8, 0x0f, 0xf8, 0x20, 0x07, 0xfe, 0x3f, 0xf0, 0x03, 0x0e, 0xf8, 0x0e, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0x0f, 0xb8, 0xe0, 0x00, 0x38, 0x0f, 0x00, 0x01, 0x87, 0x7c, 0x07, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0x0f, 0x38, 0xc2, 0x00, 0x03, 0xe0, 0x00, 0x20, 0xc7, 0x3c, 0x07, 0xff, 0xff,
  0xff, 0xff, 0xf8, 0x0e, 0x3f, 0xc2, 0x00, 0x7f, 0xff, 0x00, 0x10, 0xff, 0x1c, 0x0f, 0xff, 0xff,
  0xff, 0xff, 0xfc, 0x0e, 0x3f, 0xc6, 0x00, 0xff, 0xff, 0x80, 0x10, 0xff, 0x1c, 0x0f, 0xff, 0xff,
  0xff, 0xff, 0xfc, 0x04, 0x3f, 0xc6, 0x00, 0x7f, 0xff, 0x80, 0x18, 0xff, 0x18, 0x0f, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0x04, 0x3f, 0xc6, 0x00, 0x04, 0xc8, 0x00, 0x38, 0xfe, 0x10, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xfe, 0x00, 0x17, 0xc7, 0x00, 0x00, 0x00, 0x0a, 0x38, 0xfa, 0x00, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x07, 0xe7, 0x14, 0x00, 0x00, 0x10, 0x31, 0xf8, 0x00, 0x3f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x80, 0x03, 0xf3, 0x0a, 0x18, 0x06, 0x34, 0x33, 0xf0, 0x00, 0x7f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xc0, 0x03, 0xbf, 0x85, 0x84, 0x18, 0x78, 0x6f, 0x70, 0x01, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xf0, 0x41, 0xcf, 0xc3, 0xe0, 0x01, 0xf0, 0xfc, 0xc1, 0x83, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xfc, 0x30, 0x41, 0xc1, 0xf0, 0x03, 0xc0, 0xe1, 0x83, 0x0f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xb8, 0x00, 0x00, 0x78, 0x07, 0x80, 0x00, 0x07, 0x7f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x38, 0x1e, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x08, 0x38, 0x00, 0x40, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x60, 0x08, 0xe0, 0x01, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1c, 0x01, 0x80, 0x0e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0x83, 0x00, 0x78, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 16224)


int mins1 = 255, mins2 = 255, mins3 = 255, mins4 = 255, mins5 = 255, mins6 = 255, mins7 = 255, mins8 = 255, mins9 = 255, mins10 = 255, mins11 = 255, mins12 = 255, mins13 = 255, mins14 = 255, mins15 = 255, mins16 = 255;

int maxs1 = 0, maxs2 = 0, maxs3 = 0, maxs4 = 0, maxs5 = 0, maxs6 = 0, maxs7 = 0, maxs8 = 0, maxs9 = 0, maxs10 = 0, maxs11 = 0, maxs12 = 0, maxs13 = 0, maxs14 = 0, maxs15 = 0, maxs16 = 0;

int valor_sensor1 = 0, valor_sensor2 = 0, valor_sensor3 = 0, valor_sensor4 = 0, valor_sensor5 = 0, valor_sensor6 = 0, valor_sensor7 = 0, valor_sensor8 = 0;

int valor_sensor9 = 0, valor_sensor10 = 0, valor_sensor11 = 0, valor_sensor12 = 0, valor_sensor13 = 0, valor_sensor14 = 0, valor_sensor15 = 0, valor_sensor16 = 0;

int valor_bd = 0, state_go = 0, state_rdy = 0, allow_off = 0, valor_bi = 0, memory_deg = 0, posicion = 0, MUESTREO = 1, sensibilidad = 100, c = 0, espera = 0, modo = LOW, value_x = 0;
int vel = 0;
unsigned long presente = 0;
long antes = 0;
long pausa = 70;
unsigned long pasado = 0;
unsigned long ahora;
double ERROR_POSICION = 0;
double ERROR_ULTIMO = 0;
double CX = 0;

int sensores[8];
// Lectura de sensores (ejemplo)

#define MAX_DECISIONES 5  // número de eventos que esperas

// 0 = recto, 1 = derecha, 2 = izquierda
byte decisiones[MAX_DECISIONES] = { 0, 2, 2, 2 };
int indiceDecision = 0;

bool hayBifurcacion = false;
bool hayBifurcaciontipoT = false;
bool hayCruce = false;

enum TipoEvento {
  EVENTO_NINGUNO,
  EVENTO_BIFURCACION,
  EVENTO_BIFURCACION_T,
  EVENTO_CRUCE_DERECHA,
  EVENTO_CRUCE_IZQUIERDA
};

TipoEvento eventoActual = EVENTO_NINGUNO;



void detectarEvento() {

  int cuentaActivos = 0;

  if (valor_sensor1 > sensibilidad) cuentaActivos++;
  if (valor_sensor2 > sensibilidad) cuentaActivos++;
  if (valor_sensor3 > sensibilidad) cuentaActivos++;
  if (valor_sensor4 > sensibilidad) cuentaActivos++;
  if (valor_sensor5 > sensibilidad) cuentaActivos++;
  if (valor_sensor6 > sensibilidad) cuentaActivos++;
  if (valor_sensor7 > sensibilidad) cuentaActivos++;
  if (valor_sensor8 > sensibilidad) cuentaActivos++;



  bool extremosActivos = (valor_sensor1 > sensibilidad && valor_sensor8 > sensibilidad);
  bool crucetipoT = (valor_sensor2 > sensibilidad && valor_sensor3 > sensibilidad && valor_sensor4 > sensibilidad && valor_sensor5 > sensibilidad && valor_sensor6 > sensibilidad && valor_sensor7 > sensibilidad);
  bool centroActivo = (valor_sensor4 > sensibilidad || valor_sensor5 > sensibilidad);
  bool crueceizquiera = (valor_sensor1 < sensibilidad && valor_sensor2 < sensibilidad && valor_sensor3 < sensibilidad && valor_sensor4 < sensibilidad && valor_sensor5 > sensibilidad && valor_sensor6 > sensibilidad && valor_sensor7 > sensibilidad && valor_sensor8 > sensibilidad);
  bool cruecederecha = (valor_sensor1 > sensibilidad && valor_sensor2 > sensibilidad && valor_sensor3 > sensibilidad && valor_sensor4 > sensibilidad && valor_sensor5 < sensibilidad && valor_sensor6 < sensibilidad && valor_sensor7 < sensibilidad && valor_sensor8 < sensibilidad);
  // Reset evento
  eventoActual = EVENTO_NINGUNO;
   digitalWrite(3, LOW);
  if (crucetipoT || cuentaActivos >= 6) {
    digitalWrite(3, HIGH);
    eventoActual = EVENTO_BIFURCACION_T;
  } else if (extremosActivos) {
    digitalWrite(3, HIGH);
    eventoActual = EVENTO_BIFURCACION;
  } else if (crueceizquiera && cuentaActivos <= 4 && !crucetipoT && !extremosActivos)
  {
    //eventoActual = EVENTO_CRUCE_IZQUIERDA;
    //digitalWrite(3, HIGH);
  }
  else if (cruecederecha && cuentaActivos <= 4 && !crucetipoT && !extremosActivos)
  {
   // eventoActual = EVENTO_CRUCE_DERECHA;
    //digitalWrite(3, HIGH);
  }
  // Aquí puedes poner otra condición para EVENTO_CRUCE si quieres
}
void setup() {



  pinMode(led, OUTPUT);
  pinMode(3, OUTPUT);
  // pinMode(lon, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  pinMode(OP, INPUT);
  pinMode(go, INPUT);
  pinMode(boton_izq, INPUT);
  //  pinMode ( boton_der, INPUT);
  pinMode(rdy, INPUT);

  pinMode(pini, OUTPUT);
  pinMode(pwmi, OUTPUT);
  pinMode(pind, OUTPUT);
  pinMode(pwmd, OUTPUT);
  //digitalWrite(lon, HIGH);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hola Hartford");
  display.display();

rutina1:

  display.drawBitmap(0, 0, leon, 128, 64, WHITE);
  display.display();
  delay(1000);
  digitalWrite(led, HIGH);

rutina2:
  lectura();


  if (valor_bi == LOW) {
    value_x = 1;
  }
  if (valor_bi == HIGH && value_x == 1) {
    delay(50);
    goto rutina3;
  }
  goto rutina2;


  //****************************************************************************************************************************************************************************


rutina3:  // Calibracion de sensores

  while (espera < 4000) {
    lectura();

    lectura1();
    display.clearDisplay();
    for (int i = 0; i < 8; i++) {
      int altura = map(sensores[i], 0, 255, 0, 55);
      int x = (7 - i) * 16;  // Posición horizontal de la barra
      int y = 64 - altura;   // Posición vertical superior de la barra

      // Dibujar barra
      display.fillRect(x, y, 10, altura, WHITE);

      // Mostrar valor encima
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(x, y - 8);  // 8 píxeles arriba de la barra
      display.print(sensores[i]);   // Muestra el valor original del sensor
    }

    display.display();


    if (valor_bi == LOW) {
      espera = 5000;
    }
    presente = millis();
    if (presente - antes > pausa) {
      antes = presente;
      if (modo == LOW) {
        modo = HIGH;
      } else {
        modo = LOW;
      }
      digitalWrite(led, modo);
       digitalWrite(3, modo);
    }




    if (valor_sensor1 < mins1) {
      mins1 = valor_sensor1;
    }
    if (valor_sensor2 < mins2) {
      mins2 = valor_sensor2;
    }
    if (valor_sensor3 < mins3) {
      mins3 = valor_sensor3;
    }
    if (valor_sensor4 < mins4) {
      mins4 = valor_sensor4;
    }
    if (valor_sensor5 < mins5) {
      mins5 = valor_sensor5;
    }
    if (valor_sensor6 < mins6) {
      mins6 = valor_sensor6;
    }
    if (valor_sensor7 < mins7) {
      mins7 = valor_sensor7;
    }
    if (valor_sensor8 < mins8) {
      mins8 = valor_sensor8;
    }


    if (valor_sensor1 > maxs1) {
      maxs1 = valor_sensor1;
    }
    if (valor_sensor2 > maxs2) {
      maxs2 = valor_sensor2;
    }
    if (valor_sensor3 > maxs3) {
      maxs3 = valor_sensor3;
    }
    if (valor_sensor4 > maxs4) {
      maxs4 = valor_sensor4;
    }
    if (valor_sensor5 > maxs5) {
      maxs5 = valor_sensor5;
    }
    if (valor_sensor6 > maxs6) {
      maxs6 = valor_sensor6;
    }
    if (valor_sensor7 > maxs7) {
      maxs7 = valor_sensor7;
    }
    if (valor_sensor8 > maxs8) {
      maxs8 = valor_sensor8;
    }

  }  // Termina calibracion de sensores

digitalWrite(3, LOW);
  digitalWrite(led, LOW);
  delay(500);



rutina4:

  digitalWrite(led, HIGH);
  lectura();
  if (state_go == HIGH) {
    allow_off = 1;
    goto PD;
  }
  if (valor_bi == LOW) {
    c = 1;
  }
  if (valor_bi == HIGH && c == 1) {
    delay(50);
    digitalWrite(led, LOW);


    goto PD;
  }
  goto rutina4;



off:
  lectura();
  if (state_go == HIGH) {
    goto PD;
  }
  analogWrite(pwmi, 0);
  analogWrite(pwmd, 0);
  goto off;





  //*****************************************************************> PROGRAMA PRINCIPAL DE PD <**************************************************************************************

PD:

  if (state_go == 0 && allow_off == 1) {
    goto off;
  }

  ahora = millis();
  int ACTUAL = ahora - pasado;
  if (ACTUAL >= MUESTREO) {

    lectura();

    ERROR_POSICION = valor_sensor1 * (-1) + valor_sensor2 * (-0.5) + valor_sensor3 * (-0.3) + valor_sensor4 * (-.1) + valor_sensor5 * (0.1) + valor_sensor6 * (.3) + valor_sensor7 * (0.5) + valor_sensor8 * (1);


    double ERROR_D = (ERROR_POSICION - ERROR_ULTIMO);
    float P = Kp * ERROR_POSICION;

    float D = Kd * ERROR_D;

    CX = P + D;

    pasado = ahora;
    ERROR_ULTIMO = ERROR_POSICION;

    if (CX >= 255) {
      CX = 255;
    }
    if (CX <= -255) {
      CX = -255;
    }




    int pwm1 = velocidad + (CX);
    int pwm2 = velocidad - (CX);

    if (pwm1 >= 255) {
      pwm1 = 255;
    }
    if (pwm2 >= 255) {
      pwm2 = 255;
    }


    if (valor_sensor2 > sensibilidad) {
      posicion = 0;
    }
    if (valor_sensor1 > sensibilidad && valor_sensor4 < sensibilidad && valor_sensor5 < sensibilidad) {
      posicion = 1;
    }

    if (valor_sensor6 > sensibilidad) {
      posicion = 0;
    }
    if (valor_sensor8 > sensibilidad && valor_sensor4 < sensibilidad && valor_sensor5 < sensibilidad) {
      posicion = 16;
    }


    detectarEvento();  // Detecta hayCruce y hayBifurcacion

    if (eventoActual != EVENTO_NINGUNO) {
      // Retroceso breve antes de actuar
      analogWrite(pwmd, 0);
      analogWrite(pwmi, 0);
   
      delay(30);
      // Si ya no hay más decisiones, parar motores
      if (indiceDecision >= MAX_DECISIONES) {

        analogWrite(pwmd, reversa);
        digitalWrite(pind, LOW);
        analogWrite(pwmi, reversa);
        digitalWrite(pini, HIGH);
        delay(50);
        analogWrite(pwmd, 0);
        analogWrite(pwmi, 0);
        delay(50);
           digitalWrite(3, LOW);
  for (int nota = 0; nota < 28; nota++) {
    if (melodia[nota] > 0) { // si no es pausa
      tone(3, melodia[nota]);
    }
    delay(tiempo[nota]);
    noTone(3);
  }
        return;
      }

      // Acción dependiendo del tipo de evento y de la decisión guardada
      byte accion = decisiones[indiceDecision];

      switch (eventoActual) {
        case EVENTO_BIFURCACION:
          if (accion == 0) { eventoActual = EVENTO_NINGUNO; }  // recto
          if (accion == 1) {
            analogWrite(pwmd, reversa);
            digitalWrite(pind, LOW);
            analogWrite(pwmi, reversa);
            digitalWrite(pini, HIGH);
            delay(50);
            analogWrite(pwmd, 0);
            analogWrite(pwmi, 0);
            delay(10);
            posicion = 1;
            delay(300);
          }  // izquierda
          if (accion == 2) {
            analogWrite(pwmd, reversa);
            digitalWrite(pind, LOW);
            analogWrite(pwmi, reversa);
            digitalWrite(pini, HIGH);
            delay(50);
            analogWrite(pwmd, 0);
            analogWrite(pwmi, 0);
            delay(10);
            posicion = 16;
            delay(300);
          }  // derecha
          break;

        case EVENTO_BIFURCACION_T:
          if (accion == 0) { eventoActual = EVENTO_NINGUNO; }  // recto
          if (accion == 2) {
            while (true) {
              analogWrite(pwmd, frente);
              digitalWrite(pind, HIGH);
              analogWrite(pwmi, frente);
              digitalWrite(pini, HIGH);
               lectura();
              delay(10);
              if (valor_sensor8 > sensibilidad && valor_sensor2 < sensibilidad && valor_sensor3 < sensibilidad && valor_sensor4 < sensibilidad && valor_sensor5 < sensibilidad && valor_sensor6 < sensibilidad && valor_sensor7 < sensibilidad && valor_sensor1 < sensibilidad) break;
            
            }



          }  // izquierda
          if (accion == 1) {
            while (true) {
              analogWrite(pwmi, frente);
              digitalWrite(pini, LOW);
              analogWrite(pwmd, frente);
              digitalWrite(pind, LOW);
              lectura();
              delay(10);
              if (valor_sensor1 > sensibilidad && valor_sensor2 < sensibilidad && valor_sensor3 < sensibilidad && valor_sensor4 < sensibilidad && valor_sensor5 < sensibilidad && valor_sensor6 < sensibilidad && valor_sensor7 < sensibilidad && valor_sensor8 < sensibilidad) break;
            
            }

          }  // derecha
          break;

        case EVENTO_CRUCE_DERECHA:
          if (accion == 0) { posicion = 0; }   // recto
          if (accion == 1) { velocidad = 0; }  // izquierda
          if (accion == 2) {
            velocidad = 0;
            delay(500);
          }  // derecha
          break;

        case EVENTO_CRUCE_IZQUIERDA:
          if (accion == 0) { velocidad = 0; }  // recto
          if (accion == 1) { velocidad = 0; }  // izquierda
          if (accion == 2) { velocidad = 0; }  // derecha
          break;


        default:
          break;
      }

      // Pasar al siguiente evento
      delay(10);
      indiceDecision++;
       
      // Reset del evento
      eventoActual = EVENTO_NINGUNO;
    }






    float r1 = abs(pwm1);
    float r2 = abs(pwm2);

    if (r1 >= 255) {
      r1 = 255;
    }
    if (r2 >= 255) {
      r2 = 255;
    }
    //Si te sales
    if (posicion == 16 && !hayBifurcacion) {
      analogWrite(pwmd, reversa);
      digitalWrite(pind, HIGH);
      analogWrite(pwmi, frente);
      digitalWrite(pini, HIGH);
      ;
    }

    if (posicion == 1 && !hayBifurcacion) {
      analogWrite(pwmd, frente);
      digitalWrite(pind, LOW);
      analogWrite(pwmi, reversa);
      digitalWrite(pini, LOW);
      ;
    }
    //control de motores
    if (posicion != 16 && posicion != 1 && !hayBifurcacion) {

      if (pwm1 < 0) {
        analogWrite(pwmd, r1);
        digitalWrite(pind, LOW);  //Derecho atras
      }
      if (pwm2 < 0) {
        analogWrite(pwmi, r2);
        digitalWrite(pini, HIGH);
        ;
      }

      if (pwm1 == 0) {
        analogWrite(pwmd, 0);
        digitalWrite(pind, LOW);
   
        ;
      }
      if (pwm2 == 0) {
        analogWrite(pwmi, 0);
        digitalWrite(pini, LOW);
      
        ;
      }

      if (pwm1 > 0) {
        analogWrite(pwmd, pwm1);
        digitalWrite(pind, HIGH);
        ;
      }
      if (pwm2 > 0) {
        analogWrite(pwmi, pwm2);
        digitalWrite(pini, LOW);
        ;
      }
    }
  }
  goto PD;
}




void loop() {}

void lectura() {

  valor_bi = digitalRead(boton_izq);
  //valor_bd = digitalRead ( boton_der);
  state_go = digitalRead(go);
  state_rdy = digitalRead(rdy);


  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  valor_sensor1 = analogRead(OP) / 4;
  digitalWrite(S0, HIGH);
  valor_sensor2 = analogRead(OP) / 4;
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  valor_sensor3 = analogRead(OP) / 4;
  digitalWrite(S0, HIGH);
  valor_sensor4 = analogRead(OP) / 4;
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  valor_sensor5 = analogRead(OP) / 4;
  digitalWrite(S0, HIGH);
  valor_sensor6 = analogRead(OP) / 4;
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  valor_sensor7 = analogRead(OP) / 4;
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  valor_sensor8 = analogRead(OP) / 4;



  if (color == 2) {

    valor_sensor1 = map(valor_sensor1, 0, 255, 255, 0);
    valor_sensor2 = map(valor_sensor2, 0, 255, 255, 0);
    valor_sensor3 = map(valor_sensor3, 0, 255, 255, 0);
    valor_sensor4 = map(valor_sensor4, 0, 255, 255, 0);
    valor_sensor5 = map(valor_sensor5, 0, 255, 255, 0);
    valor_sensor6 = map(valor_sensor6, 0, 255, 255, 0);
    valor_sensor7 = map(valor_sensor7, 0, 255, 255, 0);
    valor_sensor8 = map(valor_sensor8, 0, 255, 255, 0);
  }



  valor_sensor1 = map(valor_sensor1, mins1, maxs1, 0, 255);
  valor_sensor2 = map(valor_sensor2, mins2, maxs2, 0, 255);
  valor_sensor3 = map(valor_sensor3, mins3, maxs3, 0, 255);
  valor_sensor4 = map(valor_sensor4, mins4, maxs4, 0, 255);
  valor_sensor5 = map(valor_sensor5, mins5, maxs5, 0, 255);
  valor_sensor6 = map(valor_sensor6, mins6, maxs6, 0, 255);
  valor_sensor7 = map(valor_sensor7, mins7, maxs7, 0, 255);
  valor_sensor8 = map(valor_sensor8, mins8, maxs8, 0, 255);
}
void lectura1() {

  for (int i = 0; i < 8; i++) {
    digitalWrite(S0, i & 0x01);
    digitalWrite(S1, (i >> 1) & 0x01);
    digitalWrite(S2, (i >> 2) & 0x01);
    delayMicroseconds(5);  // Pequeña espera de estabilización
    sensores[i] = analogRead(OP) / 4;
  }
}
