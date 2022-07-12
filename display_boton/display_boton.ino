// pines para el display
const int a = 40;  
const int b = 42;
const int c = 50;
const int d = 46;
const int e = 30;
const int g = 34;

// para identificar el estado del boton
//int state_boton1 = LOW; 
//int state_boton2 = LOW;
//int state_boton3 = LOW;

const int boton_piso1 = 10;
const int boton_piso2 = 11;
const int boton_piso3 = 12;


void setup() {
    // botones
  pinMode (boton_piso1,INPUT);
  pinMode (boton_piso2,INPUT);
  pinMode (boton_piso3,INPUT);

   //pines displays
  pinMode (a,OUTPUT);
  pinMode (b,OUTPUT);
  pinMode (c,OUTPUT);
  pinMode (d,OUTPUT);
  pinMode (e,OUTPUT);
  pinMode (g,OUTPUT);

Serial.begin(9600);
  

}

void loop() {
state_boton1 = digitalRead(boton_piso1);
state_boton2 = digitalRead(boton_piso2);
state_boton3 = digitalRead(boton_piso3);

Serial.println(state_boton1);
Serial.println(state_boton2);
Serial.println(state_boton3);

if(state_boton1 = LOW){
        digitalWrite (b,HIGH);
        digitalWrite (c,HIGH);
        digitalWrite (d,HIGH);
        
        digitalWrite (a,LOW);
        digitalWrite (e,LOW);
        digitalWrite (g,LOW);
}
if(state_boton2 = LOW){

        digitalWrite (a,HIGH);
        digitalWrite (b,HIGH);
        digitalWrite (d,HIGH);
        digitalWrite (e,HIGH);
        digitalWrite (g,HIGH);
        digitalWrite (c,LOW);
}

if(state_boton3 = LOW){

        digitalWrite (a,HIGH);
        digitalWrite (b,HIGH);
        digitalWrite (c,HIGH);
        digitalWrite (d,HIGH);
        digitalWrite (g,HIGH);   
        digitalWrite (e,LOW);
  }

  else{
        digitalWrite (a,LOW);
        digitalWrite (b,LOW);
        digitalWrite (c,LOW);
        digitalWrite (d,LOW);
        digitalWrite (g,LOW);   
        digitalWrite (e,LOW);
    }


}
