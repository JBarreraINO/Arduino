
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
int opnente_det;
int bandera_inicio;
int timeout_str;
int control_md, control_mi;
const int sens = 12;
#define MODULOSTART 14
// Variables de estado
int ultimo = -1;  // Último sensor que detectó al oponente (-1: ninguno)

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
          control_md = 200;
          control_mi = 220;
          timeout_str = 500;
          opnente_det = 110;  //OPONENETE A IZQUIERDA
          myOLED.print("esperar de frente", LEFT, 32);
          myOLED.print("1 3 4 OFF", CENTER, 40);



          break;
        }
      case 1:
        {  //OPOENTE DE DERECHA DIAGONAL --2 ON 3 4 OFF
          control_mi = VELOCIDAD_BUSQUEDA * 2 / 4;
          control_md = VELOCIDAD_BUSQUEDA;
          timeout_str = 300;
          opnente_det = 1;  //OPONENETE A DERECHA
          myOLED.print("OP de derecha diagonal", CENTER, 32);
          myOLED.print("1 ON 3 4 OFF", CENTER, 40);
          break;
        }
      case 2:
        {  //OPOENTE DE ATRAS CENTRO DE PISTA - GIRO DE UNA --2 OFF 3ON 4 OFF
          control_md = VELOCIDAD_BUSQUEDA;
          control_mi = -VELOCIDAD_BUSQUEDA;
          timeout_str = 200;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de espalda GIRO D1", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 OFF", CENTER, 40);
          break;
        }
      case 3:
        {  //OPOENTE DE DERECHA GIRO COMPLETO --2 ON 3ON 4 OFF
          control_md = VELOCIDAD_BUSQUEDA;
          control_mi = -VELOCIDAD_BUSQUEDA;
          timeout_str = 200;
          opnente_det = 1;  //OPONENETE A DERECHA
          myOLED.print("OP de derecha giro 360°", CENTER, 32);
          myOLED.print("1 ON 3 ON 4 OFF", CENTER, 40);
          break;
        }
      case 4:
        {
          //OPOENTE DE IZQUIERDA DIAGONAL --2 OFF 3 OFF 4 ON
          control_mi = VELOCIDAD_BUSQUEDA;
          control_md = VELOCIDAD_BUSQUEDA * 3 / 4;
          timeout_str = 200;
          opnente_det = 100;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de izquierda diagonal ", CENTER, 32);
          myOLED.print("1 OFF 3 OFF 4 ON", CENTER, 40);
          break;
        }
      case 5:
        {  //OPOENTE DE FRENTE EN CENTRO DE PISTA --2 ON 3 OFF 4 ON
          control_md = VELOCIDAD_BUSQUEDA;
          control_mi = VELOCIDAD_BUSQUEDA;
          timeout_str = 100;
          opnente_det = 110;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de frente", CENTER, 32);
          myOLED.print("1 ON 3 OFF 4 ON", CENTER, 40);
          break;
        }
      case 6:
        {  //OPOENTE DE IZQUIERDA GIRO TOTAL --2 OFF 3 ON 4 ON
          control_md = -VELOCIDAD_BUSQUEDA;
          control_mi = VELOCIDAD_BUSQUEDA;
          timeout_str = 200;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de izquierda giro 360° ", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 ON", CENTER, 40);
          break;
        }
      case 7:
        {  //OPONENTE ATRAS EN BORDE DE PISTA MINISUMO--2 3 4 ON
          control_md = -VELOCIDAD_BUSQUEDA;
          control_mi = -VELOCIDAD_BUSQUEDA;
          timeout_str = 400;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
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
  if (bandera_inicio == 1) {
    if (timeout_str)  //HAY TIEMPO
    {
      timeout_str--;
    }
  }

  if (timeout_str <= 0) {
    bandera_inicio = 0;
  }

  if (estado1x > sens && estado2x > sens)  //Los sensores de piso detectaron el borde
  { Retroceder();  Derecha(); }                        //El robot debe retroceder

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

 //no sensores no piso 
  else {
    {   controlarMotores( control_mi, control_md); 
    
    
    }
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
  controlarMotores(-VELOCIDAD_ATAQUE/2, -VELOCIDAD_ATAQUE);
}

void RetrocederIzquierda() {
  controlarMotores(-VELOCIDAD_ATAQUE, -VELOCIDAD_ATAQUE/2);
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
void avanceconestrategia(){
  controlarMotores( control_mi, control_md);
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

