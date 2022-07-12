// PANTALLA_AUTO_TEMP 
// Copyright (C)2016 BENEGAS ANIBAL. All right reserved
// E-mail: benegasanibal@gmail.com
// 
// Este programa necesita las siguientes librerias
// UTFT.h
//
/*
// FALTANTES:
/////////////    HACER QUE SI LA TEMPERATURA ANTIGUA DEL MOTOR ES IGUAL A LA ANTERIOR 
/////////////    ESTA NO REFRESQUE LA PANTALLA PARA EVITAR EL DESTELLO DEL NUMERO
    
    HACER QUE EL TERMOMETRO TRABAJE EN FUNCION DE LA TEMPERATURA MEDIDA
    
    DAR LA POSICION DE LAS DEMAS TEMPERATURAS (EXTERIOR, RADIADOR)
    
    HACER UN PEQUEÑO OSCILOSCOPIO DE LA TEMPERATURA DEL MOTOR
    
    COLOCAR EL SIMBOLO DE EL VENTILADOR DEL ELECTRO PARA INDICAR QUE ESTA FUNCIONANDO
    Y DAR SU SALIDA PARA LAS DOS VELOCIDADES QUE ESTE POSEE
    
    COLOCAR LAS ALARMAS CORRESPONDIENTES A CADA SITUACION Y SUS CORRESPONDIENTES SALIDAS
*/

#include <UTFT.h>
#include <URTouch.h>
#include <UTFT_Buttons.h>

//*** Declare which fonts we will be using   ******************
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];
extern uint8_t SevenSegNumFont[];
//extern uint8_t BigFont_45[];


// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Recuerde cambiar los parametros para su pantalla!
UTFT          myGLCD(SSD1289,38,39,40,41);

URTouch       myTouch(6,5,4,3,2);
UTFT_Buttons  myButtons(&myGLCD, &myTouch);


//***   DEFINICIONES   *************************
#define senTemp_1 A0 // Sensor temperatura motor     = Analogo Pin 0
#define senTemp_2 A1 // Sensor temperatura exterior  = Analogo Pin 1
#define senTemp_3 A2 // Sensor temperatura radiador  = Analogo Pin 2
#define elec_vel_Alta 13 // pin de salida del ventilador del electro
#define elec_vel_Baja 12 // pin de salida del ventilador del electro
#define lcd_power 11 // 


//***   VARIABLES   ****************************************
long tempSensor_1 = 0;
long tempSensor_2 = 0;
long tempSensor_3 = 0;

int tempMotor = 0; 
int tempExterior = 0;
int tempRadiador = 0;

int tempMotAnt = 0;
int tempExtAnt = 0;
int tempRadAnt = 0;
int but1, pressed_button;
int avanza_x;
int avanza_x_disp;
int pun_Matriz = 0;
int power;

//***   SETUP   ********************************************
void setup()
{
  myGLCD.InitLCD();                // INICIO EL LCD
  myGLCD.setFont(BigFont);         // DETERMINO LA FUENTE
  myGLCD.clrScr();                 // BORRO LA PANTALLA
  
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  
  myButtons.setTextFont(SmallFont);
  myButtons.setSymbolFont(Dingbats1_XL);
  
  but1 = myButtons.addButton( 200, 174, 114, 16, "ELECTRO");
  myButtons.drawButtons();
  
  pinMode(elec_vel_Alta, OUTPUT);
  pinMode(elec_vel_Baja, OUTPUT);
  pinMode(lcd_power, INPUT);
  
//---   DIBUJAR LAYER   -------------------------
  layerTemp();
  led_apagado(); 
  mostrarValorMotor();
  mostrarValorRad();
  oscil_Temp();
}


//***   LOOP   **********************************************
void loop()
{
/*    //power = digitalRead(lcd_power);
    power=0;
    if ( power = 0){
      myGLCD.lcdOff();
    } else if (power = 1){
      myGLCD.lcdOn();
    } else {
    }*/
    
    getTemps();
    oscil_Temp();
    // temperatura motor
    if(tempMotor != tempMotAnt) {
    mostrarValorMotor();
    }
    else {
    }
    
    // temperatura radiador
    if(tempRadiador != tempRadAnt) {
    mostrarValorRad();
    }
    else {
    }
    
    delay(100);
}

/* |------------------------------------------------------|
   |   LAYER PARA POSICION DE DIGITOS                     |
   |   myGLCD.setColor(VGA_YELLOW);                       |
   |   myGLCD.drawRect(210,7,242,57);   // digito 1       |
   |   myGLCD.drawRect(242,7,274,57);   // digito 2       |
   |   myGLCD.drawRect(274,7,306,57);   // digito 3       |
   |                                                      |
   |   myGLCD.drawRect(125,65,141,81);  // digito 4       |
   |   myGLCD.drawRect(125,85,141,101); // digito 5       |
   |------------------------------------------------------|
*/

//***   MOTOR   ************************************************
void mostrarValorMotor()
  {
    long pos_1 = 274;
    long pos_2 = 242;
    long pos_3 = 210;
  
      myGLCD.setColor(VGA_BLACK);      // borra los digitos temperatura motor
      myGLCD.fillRect(210,7,306,57);
      
      if((tempMotor < 40)){            // identifica el color a ser 
         myGLCD.setColor(VGA_GREEN);} // displayer temperatura motor
         else
         {
         if((tempMotor >= 40) && (tempMotor < 95)){
           myGLCD.setColor(VGA_YELLOW);
           }
           else 
           { myGLCD.setColor(VGA_RED);
           }
         }
      
      // COLOCA EN POSICION LOS DIGITOS DE LA TEMPERATURA DEL MOTOR
      myGLCD.setFont(SevenSegNumFont);  // SELECCIONA LA FUENTE PARA LA TEMPERATURA DEL MOTOR
      if((tempMotor < 10)){             // 
         myGLCD.printNumI(tempMotor, pos_1, 7);
       } // 
         else
         {
         if((tempMotor >= 10) && (tempMotor <= 99)){
           myGLCD.printNumI(tempMotor, pos_2, 7);
         }
           else 
           { 
           myGLCD.printNumI(tempMotor, pos_3, 7);
           }
         }
         if ((tempMotor >= 40)){
           
             term_Hg();
         }

//---   GUARDO LA TEMPERATURA ACTUAL COMO ANTERIOR   ---------      
      tempMotAnt = tempMotor;      
           
      return;
  }
  
//***   RADIADOR   *******************************************
void mostrarValorRad()
  {
    long pos_1r = 298;
    long pos_2r = 282;
    long pos_3r = 266;
      
      myGLCD.setColor(VGA_BLACK);      // borra los digitos temperatura motor
      myGLCD.fillRect(266,155,306,171);
      
      if((tempRadiador < 40)){            // identifica el color a ser 
         myGLCD.setColor(VGA_GREEN);} // displayer temperatura motor
         else
         {
         }
         if((tempRadiador >= 40) && (tempRadiador < 60)){
           myGLCD.setColor(VGA_YELLOW);}
           else 
           { 
             myGLCD.setColor(VGA_RED);
           }
               
      // COLOCA EN POSICION LOS DIGITOS DE LA TEMPERATURA DEL RADIADOR
      myGLCD.setFont(BigFont);  // SELECCIONA EL TAMAÑO DE FUENTE PARA LA TEMPERATURA DEL MOTOR
      if((tempRadiador < 10)){            // 
         myGLCD.printNumI(tempRadiador, pos_1r, 155);
       } // 
         else
         {
         if((tempRadiador >= 10) && (tempRadiador <= 99)){
           myGLCD.printNumI(tempRadiador, pos_2r, 155);
         }
           else 
           { 
           myGLCD.printNumI(tempRadiador, pos_3r, 155);
           }
         }
      tempRadAnt = tempRadiador;
      get_Sal_Elec();
      return;
  }
  
//***   SALIDA DE FUNCIONAMIENTO DE ELECTRO   *************
void get_Sal_Elec(){
  
  if (tempRadiador <= 40){
    digitalWrite(elec_vel_Baja, LOW);
    digitalWrite(elec_vel_Alta, LOW);
    led_apagado();
  } else if ((tempRadiador > 40) && (tempRadiador < 60)) {
    digitalWrite(elec_vel_Baja, HIGH);
    digitalWrite(elec_vel_Alta, LOW);
    led_enc_vel_1();
  } else {
    digitalWrite(elec_vel_Baja, LOW);
    digitalWrite(elec_vel_Alta, HIGH);
    led_enc_vel_2();
  }
  
}

//***   LED APAGADO   **************************************
void led_apagado() {
  
  //---  LED DEL ELECTRO   ----------------------------------------

      myGLCD.setColor(0,0,200);
      myGLCD.setBackColor(0,0,200);
      myGLCD.setFont(SmallFont);
      myGLCD.fillRoundRect(200,155,246,171);
      myGLCD.setColor(VGA_WHITE);
      myGLCD.drawRoundRect(200,155,246,171);
      myGLCD.print("OFF",212,157);
      myGLCD.setBackColor(VGA_BLACK);
  return;
}

//***   LED ENCENDIDO VELOCIDAD 1 BAJA   *******************
void led_enc_vel_1() {
  
  //---  LED DEL ELECTRO   ----------------------------------------

      myGLCD.setColor(225,110,0);
      myGLCD.setBackColor(225,110,0);
      myGLCD.setFont(SmallFont);
      myGLCD.fillRoundRect(200,155,246,171);
      myGLCD.setColor(VGA_WHITE);
      myGLCD.drawRoundRect(200,155,246,171);
      myGLCD.print("OFF",212,157);
      myGLCD.setBackColor(VGA_BLACK);
  return;
}

//***   LED ENCENDIDO VELOCIDAD 2 ALTA   *******************
void led_enc_vel_2() {
  
  //---  LED DEL ELECTRO   ----------------------------------------

      myGLCD.setColor(0,200,0);
      myGLCD.setBackColor(0,200,0);
      myGLCD.setFont(SmallFont);
      myGLCD.fillRoundRect(200,155,246,171);
      myGLCD.setColor(VGA_WHITE);
      myGLCD.drawRoundRect(200,155,246,171);
      myGLCD.print("OFF",212,157);
      myGLCD.setBackColor(VGA_BLACK);
  return;
}

//***   getTemps   ****************************************
void getTemps(){ 
  tempSensor_1 = analogRead(senTemp_1);
  tempSensor_2 = analogRead(senTemp_2);
  tempSensor_3 = analogRead(senTemp_3);
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRect(280,200,312,230);
  tempMotor    = map(tempSensor_1,  0, 1023, 0, 110);
  tempRadiador = map(tempSensor_2, 20, 1023, 0, 110);
  tempExterior = map(tempSensor_3,  0, 1023, 0, 50);
  
  //---   DEBUG   ---
  /*
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(VGA_RED);
  myGLCD.printNumI(tempSensor_1, 280, 202);
  myGLCD.printNumI(tempSensor_2, 280, 212);
  myGLCD.printNumI(tempSensor_3, 280, 222);
  */
  return;
}

//***   BOTON ACTIVADO   ***********************************
void buttonPressed(){
     
  while(myTouch.dataAvailable() == true)
  {
    pressed_button = myButtons.checkButtons();
      if (pressed_button == but1)
      { 
        if(elec_vel_Alta == 0)
        {
          digitalWrite(elec_vel_Alta, HIGH);}
          else
          {
            digitalWrite(elec_vel_Alta,LOW);
          }
      }
      myButtons.drawButtons();
    }
    return;
}

//***   ALTURA MERCURIO   ***********************************
void term_Hg(){
  
    int term_Mercurio;
    
      //---   REALIZO LOS CALCULOS   ----------------------
      // map(value, fromLow, fromHigh, toLow, toHigh)
      term_Mercurio = map(tempMotor, 40, 110, 160, 20);
      
      //---   UN DEBUG PARA TENER LOS VALORES DE LOS CALCULOS
      myGLCD.setFont(SmallFont);
      myGLCD.printNumI(term_Mercurio, 130, 202);
      
      //---   DIBUJO EL MERCURIO   ------------------------
          myGLCD.setColor(VGA_BLUE);
          myGLCD.fillRect(51,159,69,term_Mercurio);  // Rectangulo de temperatura
          myGLCD.setColor(VGA_BLACK);
          myGLCD.fillRect(51,20,69,(term_Mercurio - 1));
      return;
}

//***   OSCILOSCOPIO   ************************************
void oscil_Temp() {
  
  avanza_x = avanza_x + 1;
  if (avanza_x == 178){
    avanza_x = 0;
  }
  
  pun_Matriz = map(tempMotor, 0, 110, 139, 71);
  avanza_x_disp = map(avanza_x, 0, 178, 131, 309);
  
  // LINEA QUE REFRESCA EL OSCILOSCOPIO
  myGLCD.setColor(VGA_BLACK);
  myGLCD.drawLine((avanza_x_disp + 1), 71,(avanza_x_disp + 1),139);
  
  // LINEA QUE INDICA LA POSICION DEL CURSOR
  myGLCD.setColor(VGA_BLUE);
  myGLCD.drawLine((avanza_x_disp + 2), 71,(avanza_x_disp + 2),139);
  
  // REFRESCA LINEAS DE MAXIMO Y MINIMO
  myGLCD.setColor(VGA_RED);
  myGLCD.drawPixel(avanza_x_disp, 81);
  myGLCD.setColor(VGA_GREEN);
  myGLCD.drawPixel(avanza_x_disp, 115);
  
  // REFRESCA LINEA QUE FORMA LA MATRIZ
  myGLCD.setColor(VGA_AQUA);
  myGLCD.drawPixel(avanza_x_disp, pun_Matriz);
  
  // DEBUG
  /*
  myGLCD.setFont(SmallFont);
  myGLCD.printNumI(avanza_x, 130,212);
  myGLCD.printNumI(avanza_x_disp, 130, 222);*/

  return;
  
/*
  VALOR MINIMO PARA Y: 139
  VALOR MAXIMO PARA Y: 71
  
  VALOR MINIMO PARA X: 131
  VALOR MAXIMO PARA X: 309
  // HORIZONTALES DE ARRIBA HACIA ABAJO
  myGLCD.drawLine(130,80,310,80);    // LINEA 1 
  myGLCD.drawLine(130,100,310,100);  // LINEA 2
  myGLCD.drawLine(130,120,310,120);  // LINEA 3
  myGLCD.drawLine(130,140,310,140);  // LINEA 4
    
  // VERTICALES DE IZQUIERDA A DERECHA
  myGLCD.drawLine(130,70,130,140);   // LINEA 1
  myGLCD.drawLine(190,70,190,140);   // LINEA 2
  myGLCD.drawLine(250,70,250,140);   // LINEA 3
  myGLCD.drawLine(310,70,310,140);   // LINEA 4
*/
  

//   --------------------------------------------------------------- 
//  |  dibujo un pequeño rectangulo donde lo quiero                 |
//  |  myGLCD.setColor(VGA_YELLOW);                                 |
//  |  myGLCD.fillRect(150,70,300,140); //posicion del osciloscopio |
//   ---------------------------------------------------------------  
}

//***   DIBUJAR LAYER TEMPERATURA   ***********************
void layerTemp()
{
  myGLCD.setColor(VGA_BLUE);
  myGLCD.drawLine(0,0,319,0);        // RECUADRO EXTERIOR
  myGLCD.drawLine(0,1,319,1);
  
  myGLCD.drawLine(0,0,0,239);
  myGLCD.drawLine(1,0,1,239);
  
  myGLCD.drawLine(0,239,319,239);
  myGLCD.drawLine(0,238,319,238);
  
  myGLCD.drawLine(319,0,319,239);
  myGLCD.drawLine(318,0,318,239);
  
  myGLCD.drawLine(120,0,120,239);    // LINEA CENTRAL VERTICAL
  myGLCD.drawLine(121,0,121,239);
  
  /*myGLCD.drawLine(272,195,272,239);  // LINEA BAJA VERTICAL
  myGLCD.drawLine(273,195,273,239);*/
  
  myGLCD.drawLine(120,60,319,60);    // LINEA 1 HORIZONTAL
  myGLCD.drawLine(120,61,319,61);
    
  myGLCD.drawLine(120,150,319,150);  // LINEA 2 HORIZONTAL
  myGLCD.drawLine(120,151,319,151);
  
  myGLCD.drawLine(120,195,319,195);  // LINEA 3 HORIZONTAL
  myGLCD.drawLine(120,196,319,196);
  
  //--- LINEAS OSCILOSCOPIO   -----------------------------
  // HORIZONTALES DE ARRIBA HACIA ABAJO
  myGLCD.setColor(VGA_RED);
  myGLCD.drawLine(130,81,310,81);    // LINEA 1
  myGLCD.setColor(VGA_GREEN);
  myGLCD.drawLine(130,115,310,115);  // LINEA 2
  myGLCD.setColor(VGA_BLUE);
  //myGLCD.drawLine(130,120,310,120);  // LINEA 3
  myGLCD.drawLine(130,140,310,140);  // LINEA 4
    
  // VERTICALES DE IZQUIERDA A DERECHA
  myGLCD.drawLine(130,70,130,140);   // LINEA 1
  //myGLCD.drawLine(190,70,190,140);   // LINEA 2
  //myGLCD.drawLine(250,70,250,140);   // LINEA 3
  myGLCD.drawLine(310,70,310,140);   // LINEA 4
    
//---   LAYOUT TERMOMETRO   -------------------------------------

// ESTA ES LA GRAFICA QUE DIBUJA EL TERMOMETRO
// EL CODIGO DEL SIMULADOR DE MERCURIO ESTA EN LA FUNCION
//               void mostrarValorMotor();

  //   BULBO
  myGLCD.setColor(VGA_BLUE);        // DIBUJO EL BULBO DEL TERMOTRO
  myGLCD.fillCircle(60,185,20);     // JUNTO CON LA SALIDA HACIA EL
//myGLCD.fillRect(49,160,71,170);   // CAPILAR
  //   EXTREMO FINAL
  myGLCD.setColor(VGA_WHITE);       // DIBUJO UN CIRCULO EN COLOR
  myGLCD.drawCircle(60,19,10);      // BLANCO CON UN DOBLE CIRCULO
  myGLCD.drawCircle(60,19,11);      // Y LUEGO LO DEJO COMO SEMICIRCULO
  myGLCD.drawCircle(60,185,20);     // BORRANDO LA PARTE INFERIOR DEL
  myGLCD.setColor(VGA_BLACK);       // MISMO CON UN RECTANGULO EN NEGRO
  myGLCD.fillRect(49,19,71,30);     
  
  myGLCD.setColor(VGA_BLUE);
  myGLCD.fillRect(49,160,71,170);

  myGLCD.setColor(VGA_WHITE);       // DIBUJO LAS LINEAS LATERALES DEL
  myGLCD.drawLine(50,19,50,167);    // CAPILAR PARA SER REPRESENTADO
  myGLCD.drawLine(49,19,49,168);    // TODO EL TERMOTRO COMPLETO
  myGLCD.drawLine(70,19,70,167);
  myGLCD.drawLine(71,19,71,168);
    
//---   DRAGWING ETIQUETAS   ---------------------------------------  
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("TEMP.",27,210);
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.setFont(SmallFont);
  myGLCD.print("TEMPERAT.",125,7);
  myGLCD.print("MOTOR",125,27);  
  myGLCD.print("TEMPERAT.",125,157);
  myGLCD.print("RADIADOR",125,177);

}  
