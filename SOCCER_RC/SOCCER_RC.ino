
#include <Bluepad32.h>



const int IN1_IZQUIERDA = 27;  // Pin de dirección IN1 para motor izquierdo DIR
const int IN2_IZQUIERDA = 26;  // Pin de dirección IN2 para motor izquierdo PWM
const int IN1_DERECHA = 32;    // Pin de dirección IN1 para motor derecho DIR
const int IN2_DERECHA = 33;    // Pin de dirección IN2 para motor derecho PWM

const int Olvidar = 13;
// propiedades PWM
const int frecuencia = 5000;
const int IN1_IZQ = 0;
const int IN2_IZQ = 2;  //pwm
const int IN1_DER = 3;
const int IN2_DER = 4;
const int resolucion = 10;
const int velMIN = 0;
const int ledConected=2;


const int Aceleracion = 250;
const int minThrottle = 0;
const int maxThrottle = 1020;
const int minBrake = 0;
const int maxBrake = 1020;
//VARIABLES DE MANDO
float factorFiltro = 0.7;  // Ajusta el factor de filtro según tus necesidades
float factorFiltroX = 0.9;  // Ajusta el factor de filtro según tus necesidades
 int valorThrottleFiltrado,valorThrottleFiltradox;
const int deadbandThreshold = 20;
//TIPO DE CONTROL EN DRIVER : 1 PARA TLE5205, 0 PARA DRV8876
bool BitOff = 0;

//variables usadas
int mapaxisX = 0;
int valorThrottle;
int valorBrake;
int valorAxisX;
int bateria;
int MINpwm = 20;
int MAXpwm = 1023;
int VelMI, VelMD;
ControllerPtr myControllers[BP32_MAX_CONTROLLERS];

// Arduino setup function. Runs in CPU 1
void setup() {
  // Initialize serial
  Serial.begin(115200);
  pinMode(Olvidar, INPUT);
  pinMode(ledConected,OUTPUT);
  if (BitOff == true) {
    int temp = MINpwm;
    MINpwm = MAXpwm;
    MAXpwm = temp;
    delay(100);
    Serial.println("bit de control: " + String(BitOff) + ",MINpwm: " + String(MINpwm) + ",Maxpwm: " + String(MAXpwm));
  }

  String fv = BP32.firmwareVersion();
  Serial.print("Firmware version installed: ");
  Serial.println(fv);


  ledcSetup(IN1_IZQ, frecuencia, resolucion);
  ledcSetup(IN2_IZQ, frecuencia, resolucion);
  ledcSetup(IN1_DER, frecuencia, resolucion);
  ledcSetup(IN2_DER, frecuencia, resolucion);



  ledcAttachPin(IN1_IZQUIERDA, IN1_IZQ);
  ledcAttachPin(IN2_IZQUIERDA, IN2_IZQ);
  ledcAttachPin(IN1_DERECHA,  IN1_DER);
  ledcAttachPin(IN2_DERECHA, IN2_DER);

  pinMode(IN1_IZQUIERDA, OUTPUT);
  //pinMode(IN2_IZQUIERDA, OUTPUT);
  pinMode(IN1_DERECHA, OUTPUT);
  //pinMode(IN2_DERECHA, OUTPUT);
  controlarMotores(velMIN, velMIN);


  const uint8_t *addr = BP32.localBdAddress();
  Serial.print("BD Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(addr[i], HEX);
    if (i < 5)
      Serial.print(":");
    else
      Serial.println();
  }

  // BP32.pinMode(27, OUTPUT);
  // BP32.digitalWrite(27, 0);

  // This call is mandatory. It setups Bluepad32 and creates the callbacks.
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // "forgetBluetoothKeys()" should be called when the user performs


  // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
  // But might also fix some connection / re-connection issues.
  //  BP32.forgetBluetoothKeys();
  int buttonState = digitalRead(Olvidar);
  if (buttonState == false) {

    BP32.forgetBluetoothKeys();
    Serial.print("dispositivo olvidado");
  }
}

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.print("CALLBACK: Controller is connected, index=");
      digitalWrite(ledConected,HIGH);
      Serial.println(i);
      myControllers[i] = ctl;
      foundEmptySlot = true;
      break;
    }
  }
  if (!foundEmptySlot) {
    Serial.println(
      "CALLBACK: Controller connected, but could not found empty slot");
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundGamepad = false;
  controlarMotores(0, 0);
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      digitalWrite(ledConected, LOW);
      Serial.print("CALLBACK: Controller is disconnected from index=");
      controlarMotores(0, 0);
      Serial.println(i);
      myControllers[i] = nullptr;
      foundGamepad = true;
      //break;
    }
  }

  if (Olvidar == true) {
    BP32.forgetBluetoothKeys();
  }

  if (!foundGamepad) {
    Serial.println(
      "CALLBACK: Controller disconnected, but not found in myControllers");
    VelMI = velMIN;
    VelMD = velMIN;
  }
}

void processGamepad(ControllerPtr gamepad) {

  // int VelMI = velMIN, VelMD = velMIN;
  valorThrottle = gamepad->throttle();
  valorBrake = gamepad->brake();
  valorAxisX = gamepad->axisX();
  bateria = gamepad->battery();
  //APLICO DEADBAND
  valorThrottle = applyDeadband(valorThrottle, deadbandThreshold);
  valorBrake = applyDeadband(valorBrake, deadbandThreshold);
  valorAxisX = applyDeadband(valorAxisX, deadbandThreshold);
  //APLICO FILTRO
 
 // int valorBrakeFiltrado = valorBrake;
  //valorThrottle= aplicarFiltro(valorThrottle, valorThrottleFiltrado, factorFiltro);
     //valorAxisX =aplicarFiltro(valorAxisX, valorThrottleFiltradox, factorFiltroX);
  
  //valorBrake= aplicarFiltro(valorBrake, valorBrakeFiltrado, factorFiltro);


  int MapBateria = map(bateria, 0, 255, 0, 100);
  int mapThrottle = map(valorThrottle, minThrottle, maxThrottle, MINpwm, MAXpwm);  // Rango ajustado a 0 a 1023// si se cambia de driver debe invertir la señal min por max
  int mapBrake = map(valorBrake, minBrake, maxBrake, MINpwm, MAXpwm);              // Rango ajustado a -1023 a 1023
 int  mapAxisX = map(valorAxisX, -550, 550, -1023, 1023);

// Calcular mezcla diferencial
int  VelMI = mapThrottle + mapAxisX;
int VelMD = mapThrottle - mapAxisX;
  
  //Serial.println("Velocidad izquierda: " + String(VelMI) + ", Velocidad derecha: " + String(VelMD) + ", mapaxisX: " + String(mapaxisX) + ",brake: " + String(mapBrake) + ",Throttle: " + String(mapThrottle));
  // Asegura que los valores estén dentro del rango -1023 a 1023
  VelMI = constrain(VelMI, -1023, 1023);
  VelMD = constrain(VelMD, -1023, 1023);

  controlarMotores(VelMI, VelMD);
  //Serial.println("Velocidad izquierda: " + String(VelMI) + ", Velocidad derecha: " + String(VelMD) + ", mapaxisX: " + String(mapaxisX) + ",brake: " + String(mapBrake) + ",Throttle: " + String(mapThrottle));
}
void controlarMotores(int velocidadMotorIzquierda, int velocidadMotorDerecha) {
  // Control de la dirección para el motor izquierdo
  if (velocidadMotorIzquierda > 0) {
    digitalWrite(IN1_IZQUIERDA, LOW);  // Gira CW
    ledcWrite(IN2_IZQ, abs(velocidadMotorIzquierda));

  } else if (velocidadMotorIzquierda < 0) {
    digitalWrite(IN1_IZQUIERDA, HIGH);  // Gira CCW
    ledcWrite(IN2_IZQ, abs(velocidadMotorIzquierda));
  } else if (velocidadMotorIzquierda == 0) {
    digitalWrite(IN1_IZQUIERDA, BitOff);  // Detén el motor izquierdo
    digitalWrite(IN2_IZQUIERDA, BitOff);
    if (BitOff == true) { ledcWrite(IN2_IZQ, 1023); }  
    else if (BitOff == false) {
      ledcWrite(IN2_IZQ, BitOff);
    }
  }


  // Control de la dirección para el motor derecho
  if (velocidadMotorDerecha > 0) {
    digitalWrite(IN1_DERECHA, LOW);  // Gira hacia adelante
                                     //digitalWrite(IN2_DERECHA, LOW);
    ledcWrite(IN2_DER, abs(velocidadMotorDerecha));
  } else if (velocidadMotorDerecha < 0) {
    //digitalWrite(IN2_DERECHA, HIGH);
    digitalWrite(IN1_DERECHA, HIGH);  // Gira hacia atrás

    ledcWrite(IN2_DER, abs(velocidadMotorDerecha));
  } else if (velocidadMotorDerecha == 0) {
    digitalWrite(IN1_DERECHA, BitOff);  // Detén el motor derecho
    digitalWrite(IN2_DERECHA, BitOff);
    if (BitOff == true) { ledcWrite(IN2_DER, 1023); }  
    else if (BitOff == false) {
      ledcWrite(IN2_DER, BitOff);
    }
  }
}

int applyDeadband(int value, int deadbandThreshold) {
  if (abs(value) < deadbandThreshold) {
    // Si el valor está dentro del rango del "deadband", establecerlo a cero
    return 0;
  } else {
    // Si está fuera del rango del "deadband", devuelve el valor original
    return value;
  }
}
int aplicarFiltro(int valorActual, int &valorFiltrado, float factor) {
  valorFiltrado = (1.0 - factor) * valorFiltrado + factor * valorActual;
  return valorFiltrado;
}


// Arduino loop function. Runs in CPU 1
void loop() {

  BP32.update();

  // It is safe to always do this before using the controller API.
  // This guarantees that the controller is valid and connected.
  for (int i = 0; i < BP32_MAX_CONTROLLERS; i++) {
    ControllerPtr myController = myControllers[i];

    if (myController && myController->isConnected()) {
      if (myController->isGamepad())
        processGamepad(myController);
    }
  }
}
