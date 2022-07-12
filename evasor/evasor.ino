

//girará en sentido horario hasta que esquive el obstáculo y siga su camino 

// Definición de variables y constantes relacionadas con el motor izquierdo
const int IN1 = 9;  // Pin digital 13 para controlar sentido giro motor izquierdo
const int IN2 = 8;  // Pin digital 12 para controlar sentido giro motor izquierdo

// Definición de variables y constantes relacionadas con el motor derecho
const int IN3 = 7;  // Pin digital 11 para controlar sentido giro motor izquierdo
const int IN4 = 6;  // Pin digital 10 para controlar sentido giro motor izquierdo
 const int EnA = 11; 
 const int EnB = 10; 
 const int velocidad=130;//de 0 a 255
// Este programa usará el sensor de ultrasonidos HCSR04 
// para medir la distancia a la que se encuentran
// diferentes obstáculos en centímetros y mostrarlo por el puerto serie.
const int triggerEmisor = 5;
const int echoReceptor = 4;
const int valorUmbral = 20;
long tiempoEntrada;  // Almacena el tiempo de respuesta del sensor de entrada
float distanciaEntrada;  // Almacena la distancia en cm a la que se encuentra el objeto
 
// Función que se ejecuta una sola vez al cargar el programa
void setup()
{
  // Se declaran todos los pines como salidas
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
   pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
 
  pinMode(triggerEmisor,OUTPUT); // El emisor emite por lo que es configurado como salida
  pinMode(echoReceptor,INPUT);   // El receptor recibe por lo que es configurado como entrada
  Serial.begin(9600); // Inicia el puerto de comunicaciones en serie
}
// Función que se repite de manera periódica
void loop()
{
  sensorUltrasonidos();
  // Si el valor de la distancia es menor que 5 cm se para y sigue recto en caso contrario
  if(distanciaEntrada>valorUmbral)
  {
 
    robotAvance();
  }
  else
  {
   robotRetroceso();
   delay(1000);
   robotDerecha();
   delay(1000);
  }
}
/*
 Función sensorUltrasonidos: para medir la longitud del pulso entrante. 
 Mide el tiempo que transcurrido entre el envío del pulso ultrasónico 
 y cuando el sensor recibe el rebote, 
 es decir: desde que el pin echo empieza a recibir el rebote, HIGH, 
 hasta que deja de hacerlo, LOW, la longitud del pulso entrante.
*/
void sensorUltrasonidos()
{
    // Se inicializa el sensor de infrasonidos
    digitalWrite(triggerEmisor,LOW);  // Para estabilizar
    delayMicroseconds(10);
 
    // Comenzamos las mediciones
    // Se envía una señal activando la salida trigger durante 10 microsegundos
    digitalWrite(triggerEmisor, HIGH);  // envío del pulso ultrasónico
    delayMicroseconds(10);
    tiempoEntrada=pulseIn(echoReceptor, HIGH); 
    distanciaEntrada= int(0.017*tiempoEntrada); // Fórmula para calcular la distancia en cm
    Serial.println("El valor de la distancia es ");
    Serial.println(distanciaEntrada);
    delay(200);
}
/*
  Función robotAvance: esta función hará que ambos motores se activen a máxima potencia
  por lo que el robot avanzará hacia delante
*/
void robotAvance()
{
  // Motor izquierdo
  // Al mantener un pin HIGH y el otro LOW el motor gira en un sentido
  analogWrite(EnA,velocidad); //velocidad
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  // Motor derecho
  // Al mantener un pin HIGH y el otro LOW el motor gira en un sentido
   analogWrite(EnB,velocidad);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
}
/*
  Función robotRetroceso: esta función hará que ambos motores se activen a máxima potencia 
  en sentido contrario al anterior por lo que el robot avanzará hacia atrás
*/
void robotRetroceso()
{
  // Motor izquierdo
  // Al mantener un pin LOW y el otro HIGH el motor gira en sentido contrario al anterior
   analogWrite(EnA,velocidad);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  // Motor derecho
  // Al mantener un pin LOW y el otro HIGH el motor gira en sentido contrario al anterior
   analogWrite(EnB,velocidad);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
}
/*
  Función robotDerecha: esta función acccionará el motor izquierdo y parará el derecho
  por lo que el coche girará hacia la derecha (sentido horario)
*/
void robotDerecha()
{
  //  Motor izquierdo
  // Se activa el motor izquierdo
  analogWrite(EnA,velocidad);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  // Motor derecho
  // Se para el motor derecho
  analogWrite(EnB,velocidad);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
}
/*
  Función robotIzquierda: esta función acccionará el motor derecho y parará el izquierdo
  por lo que el coche girará hacia la izquierda (sentido antihorario)
*/
void robotIzquierda ()
{
   //  Motor izquierdo
  // Se para el motor izquierdo
  analogWrite(EnA,velocidad);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  // Motor derecho
  // Se activa el motor derecho
  analogWrite(EnB,velocidad);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
}
/*
  Función robotParar: esta función parará ambos motores
  por lo que el robot se parará.
*/
void robotParar()
{
  // Motor izquierdo
  // Se para el motor izquierdo
  analogWrite(EnA,0);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  // Motor derecho
  // Se para el motor derecho
  analogWrite(EnA,0);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
}
