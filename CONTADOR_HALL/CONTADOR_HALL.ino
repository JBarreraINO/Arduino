int LED = 13;
int Bot = A0;
int valor = 0;
int contador = 0;
int estadoanteriorboton = 0;
int pulsador=A1;
void setup()
{
Serial.begin(9600); // Configura velocidad de transmisión a 9600
pinMode(LED, OUTPUT); // inicializa como salida digital el pin 13
pinMode(Bot, INPUT); // inicializa como entrada digital el 7
pinMode(13, OUTPUT); // inicializa como entrada digital el 7
pinMode(pulsador, INPUT); // inicializa como entrada digital el 7
}
 
void loop()
{
valor = digitalRead(Bot); // lee el valor de la entrad digital pin 7
digitalWrite(LED, valor);
if(valor != estadoanteriorboton){
 
if(valor == 0){
contador++;
Serial.print(contador);
Serial.write(10);
Serial.write(13);
if (contador == 1000) {
contador = 0;
}
}
}
estadoanteriorboton = valor;

if (digitalRead(pulsador)==LOW)
{
  digitalWrite(13,HIGH);
 // Serial.println("boton-arriba");
  
  }

if (digitalRead(pulsador)==HIGH)
{
    //Serial.println("boton-abajo");
  digitalWrite(13,LOW);
  }




}
