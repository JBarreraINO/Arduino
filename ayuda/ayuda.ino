#include <SoftwareSerial.h>
#include <ESP8266wifi.h>
#include <WiFiClient.h>

SoftwareSerial BT(1,2); //inicializando el BT
// Declaracion de variables globales
char DataBluetooth, DataBluetooth1 ;
const int releBT = 7;
const int releLM35 = 5;
int contconexion = 0;
int temp = 0;
int lm35 = A0;

//conf de WiFi
const char* ssid = "cacahuate"; //id de la red wifi
const char* pwd = "Beudqvenmcshgets_2020"; //clave de la red wifi
//const char* host = "192.168.1.2"; //host a donde se enviaran los datos


void setup(){
  //inicializando BT
  BT.begin(9600);
  //conexion serial en baudios
  Serial.begin(115200);
  delay (100);
  pinMode (releBT,  OUTPUT);
  pinMode (releLM35,  OUTPUT);
  digitalWrite (releBT, HIGH);
  digitalWrite (releLM35, HIGH);

  WiFi.begin (ssid, pwd);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(500);
    Serial.print(".");
    }
    if (contconexion <50) {
      //para usar con ip fija
      IPAddress ip(192,168,1,10); 
      IPAddress gateway(192,168,1,1); 
      IPAddress subnet(255,255,255,0); 
      WiFi.config(ip, gateway, subnet); 

      Serial.println();
      Serial.println("wifi conectado");
      Serial.println("direccion ip: ");
      Serial.println(WiFi.localIP());
      }
      else{
        Serial.println();
        Serial.println("Error de conexion");
        }
      }

void loop(){     
//----------------modulo bluetooth--------------------//
// Si hay datos disponibles en el módulo bluetooth HC-05
if(BT.available()>0){
  DataBluetooth = BT.read();
  Serial.print(DataBluetooth);
  
  if(DataBluetooth == 'A'){
    while(DataBluetooth == 'A'){
   releBTA();
   
   if (BT.available()>0) {    DataBluetooth1 = BT.read();
       Serial.print("I received: ");
    Serial.println(DataBluetooth1, DEC);
 if (DataBluetooth1=='B'){break;}
   }
    }
apagar();
      }


 if(DataBluetooth == 'C'){
    while(DataBluetooth == 'C'){
   sensorrele();
   
   if (BT.available()>0) {    DataBluetooth1 = BT.read();
       Serial.print("I received: ");
    Serial.println(DataBluetooth1, DEC);
 if (DataBluetooth1=='D'){break;}
   }
    }
 finreley();
      }




      
      
//----------------fin modulo bluetooth--------------------//

}
}
void sensorrele(){
  
  //---------------- modulo temperatura --------------------//
  temp = analogRead(lm35);
  temp = 3.3 * temp * 100.0 / 1024;
  float auxtemp = temp;
  Serial.println(temp);
  //  rele
  if (temp >= 51){
      const char* detalletemp = "sistema encendido";
      const char* estadotemp = "activo";
      digitalWrite(releLM35,HIGH);
      Serial.println (detalletemp);
      Serial.println (estadotemp);
     
    }
    else{
      const char* detalletemp = "sistema apagado";
      const char* estadotemp = "inactivo";
      digitalWrite(releLM35,LOW);
      Serial.println (detalletemp);
      Serial.println (estadotemp);
     
      }
       delay (1000);
  
//----------------fin modulo temperatura--------------------//
}

void finreley(){
}


void releBTA(){ digitalWrite(releBT,HIGH);
    Serial.println("");  
    Serial.println("Prender");  
    BT.println("e"); 
    Serial.println("");}

  void apagar(){
    
     digitalWrite(releBT,LOW);
      Serial.println("");  
      Serial.println("Apagar");  
      BT.println("a"); 
      Serial.println("");
    }
