
//Libreria 
#include <Barreraino.h>
barrera Robot;//Declaracion del objeto
unsigned long previusMillis=0;
long intervalo;

#define LED_A 2
#define LED_B 13
#define LED_C 9
#define BOTON 6
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

void setup()
{
    //Carga la configuraciones de las entradas o salidas
 Robot.unoBarrera();
  //Configuracion de la consola serial
  Serial.begin(9600);
    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_C, OUTPUT);
}

void loop()
{
  if(Robot.Boton1()){
Serial.print("ON:  ");
Serial.println("presionaste el boton 1 ");
  loop_led_c();}

  if(Robot.Boton2()){
Serial.print("ON:  ");
Serial.println("presionaste el boton 2 ");
loop_led_b();}

 loop_led_a();
  

    
}

void loop_led_a()
{
    static long ultimo_cambio = 0;
    static int Estado_LED = OFF;

    long hora = millis();

    if (hora - ultimo_cambio > 1000) {
        ultimo_cambio = hora;

      Estado_LED = !Estado_LED;
        digitalWrite(LED_A, Estado_LED);
        
        }
    }


void loop_led_b()
{
    static long ultimo_cambio = 0;
    static int Estado_LED = OFF;

    long hora = millis();

    if (hora - ultimo_cambio > 250) {
        ultimo_cambio = hora;

        Estado_LED = !Estado_LED;
        digitalWrite(LED_B, Estado_LED);
    }
}

void loop_led_c()
{
  static long ultimo_cambio = 0;
    static int Estado_LED = OFF;

    long hora = millis();

    if (hora - ultimo_cambio > 250) {
        ultimo_cambio = hora;

        Estado_LED = !Estado_LED;
        digitalWrite(LED_C, Estado_LED);
    }
}
