 #define MODULOSTART 14 // pin del star del arrancador
 
 void setup() {
    
  Serial.begin(9600);
  // put your setup code here, to run once:
pinMode(MODULOSTART, INPUT);
  int Analogpw = digitalRead(MODULOSTART);
  while (Analogpw == LOW) {
      Serial.print(" POWER : ");
      Serial.println(Analogpw);
      Analogpw = digitalRead(MODULOSTART);
  }
}

void loop() {
     int Analogpw = digitalRead(MODULOSTART);
    if(Analogpw == LOW )
   {
    // aqui ponemos funcion para que el robot este parado 
    //ejemplo  --> controlarMotores(0, 0); 
    // pone motores en 0
     
      while(1); //SE APAGA
   }
}
