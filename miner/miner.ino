
double canal[9];
long unsigned int pos = 0;
int izqA = 11;
int izqB = 8;
int derA = 4;
int derB = 3;
int neutralh = 1500;//PUT YOUR HIGH NEUTRAL VALUE HERE. REPLACE 1500  =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int neutrall = 1420;//PUT YOUR LOW NEUTRAL VALUE HERE. REPLACE 1420  =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int maxval = 2000; //PUT YOUR MAX VALUE HERE   REPLACE 1870           =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~==~=~==~=~==~=~==~=~==~=~==~=~=
int minval = 980; // PUT YOUR MIN VALUE HERE           REPLACE 1050  =~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~
//==================INSERT VALUES HERE /\ ====================================================================================================
void setup()
{

  //pinMode (2,INPUT);
  //pinMode (3,INPUT);
  // pinMode (4,INPUT);
  pinMode (19, INPUT);
  pinMode (18, INPUT);
  //  pinMode (7,INPUT);
  // pinMode (8,INPUT);
  // pinMode (9,INPUT);// verificar canal no cambiar
  Serial.begin(250000);// put your setup code here, to run once:
  //canal[0] = pulseIn (2, HIGH);
  // canal[1]= pulseIn (3, HIGH);
  //canal[2] = pulseIn (4, HIGH);
  canal[3] = pulseIn (19, HIGH);
  canal[4] = pulseIn (18, HIGH);
  //  canal[5]= pulseIn (7, HIGH);
  //  canal[6]= pulseIn (8, HIGH);
  // canal[7]= pulseIn (9, HIGH);
  Serial.print(canal[0]);
  Serial.print("   -   ");
  Serial.print(canal[1]);
  Serial.print( "    -    ");
  Serial.print(canal[2]);
  Serial.print("  -  ");
  Serial.print(canal[3]);
  Serial.print( "  - ");
  Serial.print(canal[4]);
  Serial.print("  -  ");
  Serial.print(canal[5]);
  Serial.print( " -   ");
  Serial.print(canal[6]);
  Serial.print("  - ");
  Serial.print(canal[7]);
  Serial.println("   -  ");

}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.print(canal[0]);
  Serial.print("   -   ");
  Serial.print(canal[1]);
  Serial.print( "    -    ");
  Serial.print(canal[2]);
  Serial.print("  -  ");
  Serial.print(canal[3]);
  Serial.print( "  - ");
  Serial.print(canal[4]);
  Serial.print("  -  ");
  Serial.print(canal[5]);
  Serial.print( " -   ");
  Serial.print(canal[6]);
  Serial.print("  - ");
  Serial.print(canal[7]);
  Serial.println("   -  ");
  int sV1;    //These are all different speed values that will be mapped
  int sV2;
  int sV3;
  int sV4;
  int sV5;
  int sV6;




  int valorVelocidad = pulseIn(6, HIGH);
  int valorDireccion = pulseIn(5, HIGH);


  if (valorVelocidad >= 1400 && valorVelocidad <= 1530) {    //si los sticks son Neutral, Entonces quédate quieto hijo de puta

    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    delay(1);

   // Serial.println("neutro");//Comprueba de nuevo cada 50 micro segundos
  }


  if (valorVelocidad > 1530 && valorDireccion >= 1420 && valorDireccion <= 1500) { //Si el acelerador está hacia arriba y girando es neutral

    sV1 = map(valorVelocidad, 1500, 2000, 140, 255);      //Mide el valor de velocidad del pulso en los números que los motores pueden leer
    //El motor está ajustado a 140-255 en lugar de 0-255 para que el motor no se detenga si
    //Es alimentado a un nivel muy bajo de un nivel

    if (sV1 > 255) { //vea pana si el valor de la velocidad es superior a 255, póngalo a 255.                         .
      sV1 = 255;    //Esto evita que se sobrepase el motor si hay un pulso en el fallo
    }

    analogWrite (derB, 0); // Establece la velocidad de motor1 a la velocidadValor
    analogWrite(izqB, 0); // Establece la velocidad de motor2 a la velocidadValor
    analogWrite(derA, sV1); //Hace que el motor avance a la velocidad definida anteriormente
    analogWrite(izqA, sV1); //Hace que el motor avance a la velocidad definida anteriormente
    delay(1);            //Repetir cada 50 micro segundos

   // Serial.println("adelante");
  }


  if (valorDireccion > neutralh && valorVelocidad > neutralh) {     //El valor de velocidad es hacia adelante, la dirección es derecha

    sV2 = map(valorVelocidad, neutralh, maxval, 140, 255);    //Hacia la derecha adelante

    if (sV2 > 255) {
      sV2 = 255;
    }

    analogWrite(derB, sV2);
    analogWrite(izqB, 0);
    analogWrite(izqA, sV2);
    analogWrite(derA, 0);
   // Serial.println("Hacia la derecha adelante");
    delay(1);
  }

  if (valorDireccion < neutrall && valorVelocidad > neutralh) { //La velocidad es hacia adelante, la dirección es izquierda
    sV3 = map(valorVelocidad, neutralh, maxval, 140, 255);    //Izquierda hacia adelante

    if (sV3 > 255) {
      sV3 = 255;
    }
    analogWrite(derB, 0);
    analogWrite(izqB, sV3 );
    analogWrite(izqA, 0);
    analogWrite(derA, sV3);


   // Serial.println("izquierda  hacia adelante");

    delay(1);
  }

  if (valorVelocidad < neutrall && valorDireccion >= neutrall && valorDireccion <= neutralh) {      //La velocidad es inversa y el valor de dirección está centrado

    sV4 = map(valorVelocidad, neutrall, minval, 140, 255);      //REVERSA

    if (sV4 > 255) {
      sV4 = 255;
    }

    analogWrite (derB, sV4); // Establece la velocidad de motor1 a speedValue
    analogWrite(izqB, sV4); // Establece la velocidad de motor2 a speedValue
    analogWrite(derA, 0); //Hace que el motor avance a la velocidad definida anteriormente
    analogWrite(izqA, 0);

   // Serial.println("reversa");

    delay(1);
  }

  if (valorDireccion > neutralh && valorVelocidad < neutrall) {

    sV5 = map(valorVelocidad, neutralh, minval, 140, 255);  //Atrás a la derecha

    if (sV5 > 255) {
      sV5 = 255;
    }
    analogWrite (derB, sV5); // Establece la velocidad de motor1 a la  speedValue
    analogWrite(izqB, 0); // Establece la velocidad de motor2 a la  speedValue
    analogWrite(derA, 0); // Hace que el motor avance a la velocidad definida anteriormente
    analogWrite(izqA, sV5);

    Serial.println("atras a la derecha");

    delay(1);
  }


  if (valorDireccion < neutrall && valorVelocidad < neutrall) {

    sV6 = map(valorVelocidad, neutralh, minval, 140, 255);    //ATRÁS A LA IZQUIERDA

    if (sV6 > 255) {
      sV6 = 255;
    }

    analogWrite (derB, 0); //Establece la velocidad de motor1 a la  speedValue
    analogWrite(izqB, sV6); // Establece la velocidad de motor2 a la  speedValue
    analogWrite(derA, sV6); //Hace que el motor avance a la velocidad definida anteriormente
    analogWrite(izqA, 0);
  //  Serial.println("atras a la izquierda");

    delay(1);

  }












}
