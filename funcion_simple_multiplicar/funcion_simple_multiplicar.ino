/* Define la función "multiplicar" 
a la que se le pasarán los 2 números
que se deseen multiplicar devolviendo
un valor entero (int). */

void setup(){}
void loop()
{
int i =2;
 int j =3; int k;
k = multiplicar(i, j); //llama a la función 
                          //multiplicación pasándole los
                          //parámetros "i" y "j"
}


int multiplicar (int x, int y) //función multiplicar
{
int resultado; //declara la variable donde se almacena el resultado
resultado = x * y; //ejecuta la operación de multiplicar
return resultado; //devuelve el resultado de la multiplicación
}
