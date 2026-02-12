#include <EEPROM.h>
char buffer[128];
char *token;

float velocidad, Kpn, Kdn, Kde, xu;
int reversa, frente, turbina, line_data, modulo_on, allow, potenciometro, memoria_on;
float Kpne, Ki, frecuencia, linealE;


void Write(int addr, const char *data, int len) {
  EEPROM.put(addr, data);   // Guarda la cadena completa
}

// Leer cadena completa de EEPROM
void Read(int addr, char *data, int len) {
  EEPROM.get(addr, data);   // Recupera la cadena
  data[len] = '\0';         // Aseguramos terminador nulo
}
bool esNumero(const char *cadena) {

  for (size_t i = 0; cadena[i] != '\0'; ++i) {
    if (cadena[i] < '0' || cadena[i] > '9') {
      return false;
    }
  }
  return true;
}

void SerialES() {
  Serial.begin(115200);
  while (!readButton_2()) {

    if (Serial.available()>0) {
      String len = Serial.readStringUntil('\n');  
      len.trim();
      len.toCharArray(buffer, sizeof(buffer));
      token = strtok(buffer, ",");

      if (strcmp(buffer, "leer") == 0) {
 //pc.printf("%.3fA%.3fB%.3fC%.3fD%.3fE%dF%dG%dH%dI%dJ%dK%dL%.3fM%.3fN%0.3fO%0.3fP%dQ\n", velocidad, Kpn, Kdn, Kde, xu, reversa, frente, turbina, line_data, modulo_on, allow, potenciometro, Kpne, Ki, frecuencia, linealE, memoria_on);
 readEEpromValues();

  Serial.println(
    String(PWM_MOTORS)  + "A" +
    String(Kpn)         + "B" +
    String(Kdn)          + "C" +
    String(KD)         + "D" +
    String(SENSOR_THRESHOLD_PERCENT)          + "E" +
    String(OFFLINE_OUTTER_PWM)        + "F" +
    String(OFFLINE_INNER_PWM)         + "G" +
    String(PWM_IMPELLER)        + "H" +
    String(INVERT_SENSOR_READS)      + "I" +
    String(modulo_on)      + "J" +
    String(areMotorsEnabled)          + "K" +
    String(potenciometro)  + "L" +
    String(KP, 3)        + "M" +
    String(Ki, 3)          + "N" +
    String(frecuencia)  + "O" +
    String(linealE)     + "P" +
    String(memoria_on)     + "Q"
  );
       toggleLED_2();
      }

        if (token != NULL && esNumero(token)) {
        PWM_MOTORS = atof(token);  
       EEPROM.put(5, PWM_MOTORS);
      }

      // Obtener el siguiente token
      token = strtok(NULL, ",");

      if (token != NULL) {
       Kpn = atof(token);  
       EEPROM.put(10,  Kpn);
      }
      token = strtok(NULL, ",");

      if (token != NULL) {
     Kdn = atof(token);  
       EEPROM.put(15,  Kdn);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
       KD= atof(token);  
       EEPROM.put(20, KD);
      }


      token = strtok(NULL, ",");

      if (token != NULL) {
                 SENSOR_THRESHOLD_PERCENT = atof(token);  
                    EEPROM.put(25, SENSOR_THRESHOLD_PERCENT);
   
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
      OFFLINE_OUTTER_PWM = atof(token);  
                    EEPROM.put(30, OFFLINE_OUTTER_PWM);
      }


      token = strtok(NULL, ",");

      if (token != NULL) {
   OFFLINE_INNER_PWM= atof(token);  
                    EEPROM.put(35,OFFLINE_INNER_PWM);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
      PWM_IMPELLER= atof(token);  
                    EEPROM.put(40,PWM_IMPELLER);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
    INVERT_SENSOR_READS= atof(token);  
                    EEPROM.put(45,INVERT_SENSOR_READS);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
 modulo_on= atof(token);  
EEPROM.put(50,modulo_on);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
areMotorsEnabled= atof(token);  
EEPROM.put(55,areMotorsEnabled);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
    
 potenciometro= atof(token);  
EEPROM.put(60,potenciometro);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
   KP= atof(token);  
EEPROM.put(65,KP);
      }

      token = strtok(NULL, ",");

      if (token != NULL) {
   Ki= atof(token);  
EEPROM.put(70,Ki);
      }


      token = strtok(NULL, ",");

      if (token != NULL) {
       
   frecuencia= atof(token);  
EEPROM.put(75,KP);
      }
      token = strtok(NULL, ",");

      if (token != NULL) {
  linealE= atof(token);  
EEPROM.put(80,linealE);
      }


      token = strtok(NULL, ",");

      if (token != NULL) {
 
  
  memoria_on= atof(token);  
EEPROM.put(85,memoria_on);
      }

    }
  }
}

void readEEpromValues(){
EEPROM.get(5, PWM_MOTORS);
EEPROM.get(10,Kpn);
EEPROM.get(15,Kdn);
EEPROM.get(20,KD);
EEPROM.get(25,SENSOR_THRESHOLD_PERCENT);
EEPROM.get(30,OFFLINE_OUTTER_PWM);
EEPROM.get(35,OFFLINE_INNER_PWM);
EEPROM.get(40,PWM_IMPELLER);
EEPROM.get(45,INVERT_SENSOR_READS);
EEPROM.get(50,modulo_on);
EEPROM.get(55,areMotorsEnabled);
EEPROM.get(60,potenciometro);
EEPROM.get(65,KP);
EEPROM.get(70,Ki);
EEPROM.get(75,KP);
EEPROM.get(80,linealE);
EEPROM.get(85,memoria_on);
}
