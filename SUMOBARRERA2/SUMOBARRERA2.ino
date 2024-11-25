//INCLUDES

//DEFINICIONES
#include <Wire.h>
#include <OLED_I2C.h>
OLED myOLED(21, 22);
extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t BigNumbers[];
extern uint8_t MediumNumbers[];
// Sensores

// Sensores de piso
int piso1 = 25;
int piso2 = 15;

// Declaración pines motores
int MOTOR1_IN1 = 26;  // PWM izquierdo
int MOTOR1_IN2 = 27;  // PWM izquierdo
int MOTOR2_IN1 = 33;  // PWM derecho
int MOTOR2_IN2 = 32;  // PWM derecho

// Configuración PWM
const int frecuencia = 5000;
const int resolucion = 10;
const int velMIN = 0;
const int sens = 12;
int line_data = 1;  // elegir el color de la linea, 2 negro o 1 blanco
#define LED1 2
int ultimo = -1;  // Último sensor que detectó al oponente (-1: ninguno)
int frontal = 18;
int derecho = 23;
int izquierdo = 16;
int Dderecho = 19;      // Sensor diagonal derecho
int Dizquierdo = 17;    // Sensor diagonal izquierdo
#define SENSOR_IN_C 18  //CAMBIO POR ANALOGO



#define DIPSW2 35
#define DIPSW3 5
#define DIPSW4 4

#define MODULOSTART 14

#define VELOCIDAD_ATAQUE 600
#define VELOCIDAD_BUSQUEDA 400

//VARIABLES

//Sensores
uint16_t estado1;
uint16_t estado2;
int16_t maxs1 = 0;
uint16_t maxs2 = 0;
int16_t mins1 = 0;
uint16_t mins2 = 0;
int estado1x = 0;
int estado2x = 0;
int SensorDistaciaCentral;
int detecto_oponente;
extern uint8_t logo[];
//estrategia
int dsw;
int opnente_det;
int bandera_inicio;
int timeout_str;

//Ataque
int a_ataque;
int a_ubicacion;
int control_md, control_mi;


void setup() {
  controlarMotores(0, 0);
  Wire.begin();

  myOLED.begin();
  myOLED.clrScr();
  myOLED.drawBitmap(0, 0, logo, 128, 64);
  myOLED.update();
  myOLED.setFont(SmallFont);
  pinMode(MODULOSTART, INPUT);
  //PWM
  ledcSetup(0, frecuencia, resolucion);
  ledcSetup(1, frecuencia, resolucion);
  ledcSetup(2, frecuencia, resolucion);
  ledcSetup(3, frecuencia, resolucion);

  ledcAttachPin(MOTOR1_IN1, 0);
  ledcAttachPin(MOTOR1_IN2, 1);
  ledcAttachPin(MOTOR2_IN1, 2);
  ledcAttachPin(MOTOR2_IN2, 3);

  controlarMotores(0, 0);
  //TEST FUNCION DE MOTORES
  //controlarMotores(0, -250);
  //delay(10000);

  myOLED.clrScr();
  pinMode(piso1, INPUT);
  pinMode(piso2, INPUT);

  pinMode(LED1, OUTPUT);


  pinMode(DIPSW2, INPUT);
  pinMode(DIPSW3, INPUT);
  pinMode(DIPSW4, INPUT);

  Serial.begin(9600);

  //CALIBRAR SENSORES DE PISO

  delay(2000);




  myOLED.update();
  myOLED.setFont(TinyFont);







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
          control_md = VELOCIDAD_ATAQUE * 2 / 4;
          control_mi = VELOCIDAD_ATAQUE;
          timeout_str = 300;
          opnente_det = 1;  //OPONENETE A DERECHA
          myOLED.print("OP de derecha diagonal", CENTER, 32);
          myOLED.print("1 ON 3 4 OFF", CENTER, 40);
          break;
        }
      case 2:
        {  //OPOENTE DE ATRAS CENTRO DE PISTA - GIRO DE UNA --2 OFF 3ON 4 OFF
          control_md = VELOCIDAD_ATAQUE;
          control_mi = -VELOCIDAD_ATAQUE;
          timeout_str = 200;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de atras centro de pista GIRO D1", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 OFF", CENTER, 40);
          break;
        }
      case 3:
        {  //OPOENTE DE DERECHA GIRO COMPLETO --2 ON 3ON 4 OFF
          control_md = -VELOCIDAD_ATAQUE;
          control_mi = VELOCIDAD_ATAQUE;
          timeout_str = 200;
          opnente_det = 1;  //OPONENETE A DERECHA
          myOLED.print("OP de derecha giro 360°", CENTER, 32);
          myOLED.print("1 ON 3 ON 4 OFF", CENTER, 40);
          break;
        }
      case 4:
        {
          //OPOENTE DE IZQUIERDA DIAGONAL --2 OFF 3 OFF 4 ON
          control_md = VELOCIDAD_ATAQUE;
          control_mi = VELOCIDAD_ATAQUE * 3 / 4;
          timeout_str = 200;
          opnente_det = 100;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de izquierda diagonal ", CENTER, 32);
          myOLED.print("1 OFF 3 OFF 4 ON", CENTER, 40);
          break;
        }
      case 5:
        {  //OPOENTE DE FRENTE EN CENTRO DE PISTA --2 ON 3 OFF 4 ON
          control_md = VELOCIDAD_ATAQUE;
          control_mi = VELOCIDAD_ATAQUE;
          timeout_str = 100;
          opnente_det = 110;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de frente en centro de pista", CENTER, 32);
          myOLED.print("1 ON 3 OFF 4 ON", CENTER, 40);
          break;
        }
      case 6:
        {  //OPOENTE DE IZQUIERDA GIRO TOTAL --2 OFF 3 ON 4 ON
          control_md = -VELOCIDAD_ATAQUE;
          control_mi = VELOCIDAD_ATAQUE;
          timeout_str = 200;
          opnente_det = 1000;  //OPONENETE A IZQUIERDA
          myOLED.print("OP de izquierda giro 360° ", CENTER, 32);
          myOLED.print("1 OFF 3 ON 4 ON", CENTER, 40);
          break;
        }
      case 7:
        {  //OPONENTE ATRAS EN BORDE DE PISTA MINISUMO--2 3 4 ON
          control_md = -VELOCIDAD_ATAQUE;
          control_mi = -VELOCIDAD_ATAQUE;
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


void loop() {

  myOLED.update();
  myOLED.setFont(TinyFont);
  int Analogpw = digitalRead(MODULOSTART);

  //Serial.print(" POWER : ");
  //Serial.println(Analogpw);
  if (Analogpw == LOW) {
    controlarMotores(0, 0);
    ;
    while (1)
      ;  //SE APAGA
  }


  //LECTURA DE SENSORES


  //Serial.print(" Oponete : ");
  //Serial.print(opnente_det);

  //Serial.print("  OP: ");
  //Serial.print(detecto_oponente);

  a_ubicacion = Detectar_Ubicacion();
  myOLED.print("       ", RIGHT, 56);
  myOLED.print("ubicacion ", LEFT, 56);
  myOLED.printNumI(a_ubicacion, RIGHT, 56);

  myOLED.print("F:", LEFT, 0);
  myOLED.printNumI(bandera_inicio, 8, 0);
  myOLED.print("OP:", 15, 0);
  myOLED.print("       ", 25, 0);
  myOLED.printNumI(opnente_det, 27, 0);



  //Serial.print("  a_ubicacion : ");
  //Serial.print(a_ubicacion);


  int Analogain = digitalRead(SENSOR_IN_C);
  if (Analogain == 1) {
    SensorDistaciaCentral = 1;
  } else {
    SensorDistaciaCentral = 0;
  }





  //sensores de piso
  lectura();
  estado1x = (estado1 - mins1) * maxs1 / (255 - mins1);
  if (estado1x <= 0) { estado1x = 0; }
  if (estado1x >= 255) { estado1x = 255; }


  estado2x = (estado2 - mins2) * maxs2 / (255 - mins2);
  if (estado2x <= 0) { estado2x = 0; }
  if (estado2x >= 255) { estado2x = 255; }

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

  ///////////////INICIO DE ESTRATEGIA DE BATALLA
  //PRIMERA PRIORIDAD ATAQUE CON SENSORES CERCANOS
  if (a_ubicacion != -1) {

    myOLED.print("                    ", LEFT, 24);
    myOLED.print("PRIMERA PRIORIDAD", LEFT, 24);
    detecto_oponente = 1;  // PARA DEBUGER
    bandera_inicio = 0;    //SE ACABA ESTRATEGIA
    timeout_str = 0;

    if (digitalRead(frontal) == 1)  //El sensor frontal detecto al oponente (EL VALOR CAMBIA DEPENDEINDO DEL SENSOR EN MI CASO MI SENSOR TIENE VALOR DE 100 O MAYOR CUANDO DETECTA ALGO)
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



  }

  //SEGUNDA SENSORES DE PISO

  //SENSOR PISO
  else if (estado1x > sens || estado2x > sens) {
    myOLED.print("sensores de piso", LEFT, 24);
    detecto_oponente = 9;

    digitalWrite(LED1, HIGH);

    bandera_inicio = 1;
    timeout_str = 150;
    opnente_det = 1000;  //OPONENETE A IZQUIERDA

    if ((estado1x > sens) && (estado2x > sens))  //Los sensores de piso detectaron el borde
    {
      control_md = -VELOCIDAD_ATAQUE;
      control_mi = -VELOCIDAD_ATAQUE;
      myOLED.print("        ", RIGHT, 24);
      myOLED.print("Ambos", RIGHT, 24);
    }  //El robot debe retroceder

    else if ((estado1x > sens))  //Los sensores de piso detectaron el borde
    {
      control_md = -VELOCIDAD_ATAQUE;
      control_mi = -VELOCIDAD_ATAQUE;
      myOLED.print("sensor1", RIGHT, 24);
    }  //El robot debe retroceder

    else if ((estado2x > sens))  //Los sensores de piso detectaron el borde
    {
      control_md = -VELOCIDAD_ATAQUE;
      control_mi = -VELOCIDAD_ATAQUE;
      myOLED.print("sensor2", RIGHT, 24);
    }  //El robot debe retroceder



  }


  //TERCERA PRIORIDAD SENSOR DE DISTANCIA CENTRAL DETECTADO y BUSQUEDA

  else if (SensorDistaciaCentral == 1) {
    myOLED.print("                    ", LEFT, 24);
    myOLED.print("TERCERA PRIORIDAD", LEFT, 24);

    digitalWrite(LED1, HIGH);
    detecto_oponente = 6;

    bandera_inicio = 0;  //SE ACABA ESTRATEGIA
    timeout_str = 0;


/*
    // SE REVISA EN QUE SENTIDO GIRO PARA CORREGIR
    if (opnente_det == 1 || opnente_det == 10) {
      //OPONENTE DETECTADO GIRANDO A DERECHA - MOTORES A IZQUIERDA CAMBIO DE GIRO
      control_md = VELOCIDAD_BUSQUEDA;
      control_mi = VELOCIDAD_BUSQUEDA
      opnente_det = 100;
    } else if (opnente_det == 1000 || opnente_det == 100) {
      //OPONENTE DETECTADO GIRANDO A IZQUIERDA - MOTORES A DERECHA CAMBIO DE GIRO
      control_md = VELOCIDAD_BUSQUEDA;
      control_mi = VELOCIDAD_BUSQUEDA;
      opnente_det = 1;
    } else {  //OPONENTE AL CENTRO --  LO PERDI CERCANO-- ES EXTRAÑO -- BUSCO AL LADO -- NO DE FRENTE PUEDO SALIRME AL BORDE
      control_md = VELOCIDAD_BUSQUEDA;
      control_mi = -VELOCIDAD_BUSQUEDA;
      opnente_det = 100;
    }
    */

  }

  ///////////////////////////////////////////////////////////////////////

  else  //NO OPONENTE - NO PISO
  {

    myOLED.print("                    ", LEFT, 24);
    myOLED.print("NO OPONENTE - NO PISO", LEFT, 24);

    if (bandera_inicio == 1) {

      digitalWrite(LED1, HIGH);
    }


    else {


      digitalWrite(LED1, LOW);

      detecto_oponente = 0;

      //bandera_inicio = 0; // AQI NOP, NO HA ENCONTRADO ENEMIGO

   
if (ultimo==0)  //El robot recuerda que vio al oponente con su sensor derecho
{DerechaLento();}
else if (ultimo==1)  //El robot recuerda que vio al oponente con su sensor izquierdo
{IzquierdaLento();}

    }
  }

  controlarMotores(control_mi, control_md);

  myOLED.setFont(TinyFont);
  myOLED.print("     ", LEFT, 32);
  myOLED.print("     ", RIGHT, 32);
  myOLED.printNumI(control_mi, LEFT, 32);
  myOLED.printNumI(control_md, RIGHT, 32);
  myOLED.update();
}


/////////////////////////////////////////////////////////////////
///FUNCIONES LOCALES
/////////////////////////////////////////////////////////////////

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
void controlarMotores(int velIzq, int velDer) {
  ledcWrite(0, velIzq > 0 ? velIzq : 0);
  ledcWrite(1, velIzq < 0 ? -velIzq : 0);
  ledcWrite(2, velDer > 0 ? velDer : 0);
  ledcWrite(3, velDer < 0 ? -velDer : 0);
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



int Detectar_Ubicacion(void) {
  int SensorState;
  int Oponente = 0;
  int num_sensores = 0;
  //SENSORES

  SensorState = digitalRead(izquierdo);  //CAMBIO A DIGITAL
  if (SensorState == 1) {
    Oponente = -200;
    num_sensores++;
  }


  SensorState = digitalRead(Dizquierdo);
  if (SensorState == 1) {
    Oponente = Oponente - 100;
    num_sensores++;
  }


  SensorState = digitalRead(  Dderecho);
  if (SensorState == 1) {
    Oponente = Oponente + 100;
    num_sensores++;
  }

  SensorState = digitalRead(derecho);
  if (SensorState == 1) {
    Oponente = Oponente + 200;
    num_sensores++;
  }

  SensorState = digitalRead(SENSOR_IN_C);
  if (SensorState == 1) {
    //Oponente = Oponente + 200;
    //num_sensores++;
  }

  myOLED.print("oponente", LEFT, 40);
  myOLED.printNumI(Oponente, RIGHT, 40);
  myOLED.update();
  myOLED.print("sensores", LEFT, 48);
  myOLED.printNumI(num_sensores, RIGHT, 48);



  if (num_sensores) {
    return Oponente / num_sensores;
  } else {
    return -1;
  }
}
void Avanzar() {
  
  control_md =  800;
  control_mi =  800;
}

void Retroceder() {
 
  control_md =  -800;
  control_mi =  -800;
}

void RetrocederDerecha() {

  control_md =  -800;
  control_mi =  -600;
}

void RetrocederIzquierda() {

  control_md =  -600;
  control_mi =  -800;
}

void Derecha() {
 
  control_md =  -800;
  control_mi =   800;
}

void DerechaLento() {

  control_md =  -600;
  control_mi =   600;
}

void Izquierda() {

  control_md =  800;
  control_mi = -800;
}

void IzquierdaLento() {

   control_md =  600;
  control_mi =   -600;
  }

void Parar() {

   control_md =  0;
  control_mi =  -0;
}
