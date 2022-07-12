/*Test Motores

Ejemplo 5 

Desarrollado por Barrera.ino

Objetivo:
*Se moveran los motores MA y MB 
*/
#include <BarreraTB6612.h>
 motores Control;

void setup() {
  

}

void loop() {
 // tenemos en cuenta el valor del pwm 0-255
 // poner un pwm negativo representara la inversion de giro del motor 
 // al poner un valor de pwm muy bajo los motores pueden no girar

 
Control.Motor(55,155);//con esta funcion podemos controlar motor B y motor A respectivamente (motor B,Motor A)
//Control.Motoriz(70);// Controla el motor B de manera independiente
//Control.Motorde(170);// Controla el motor A de manera independiente
//Control.freno(false, true, 25);//con esta funcion podemos frenar  motor A y motor B(motor B,Motor A,valor de freno) 
                                  //debemos poner en true el motor que queremos frenar tener en cuenta que el freno
                                  //debe ser proporcional al pwm
}
