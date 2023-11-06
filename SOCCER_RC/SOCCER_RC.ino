
#include <Bluepad32.h>



const int IN1_IZQUIERDA = 26;  // Pin de dirección IN1 para motor izquierdo
const int IN2_IZQUIERDA = 27;  // Pin de dirección IN2 para motor izquierdo
const int IN1_DERECHA = 32;    // Pin de dirección IN1 para motor derecho
const int IN2_DERECHA = 33;    // Pin de dirección IN2 para motor derecho
const int Olvidar = 13;
// propiedades PWM
const int frecuencia = 5000;
const int IN1_IZQ = 0;
const int IN2_IZQ = 2;
const int IN1_DER = 3;
const int IN2_DER = 4;
const int resolucion = 10;
const int velMIN = 0;
const int MINpwm = 150;
const int deadband = 50;
const int Aceleracion = 250;
int VelMI, VelMD;
bool BitOff=1;

//variables usadas
int mapaxisX = 0;
int valorThrottle;
int valorBrake;
int valorAxisX;
int bateria;

ControllerPtr myControllers[BP32_MAX_CONTROLLERS];

// Arduino setup function. Runs in CPU 1
void setup() {
  // Initialize serial
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect.
    // You don't have to do this in your game. This is only for debugging
    // purposes, so that you can see the output in the serial console.
    ;
  }
  pinMode(Olvidar, INPUT);
  String fv = BP32.firmwareVersion();
  Serial.print("Firmware version installed: ");
  Serial.println(fv);


  ledcSetup(IN1_IZQ, frecuencia, resolucion);
  ledcSetup(IN2_IZQ, frecuencia, resolucion);
  ledcSetup(IN1_DER, frecuencia, resolucion);
  ledcSetup(IN2_DER, frecuencia, resolucion);



  //ledcAttachPin(IN1_IZQUIERDA, IN1_IZQ);
  ledcAttachPin(IN2_IZQUIERDA, IN2_IZQ);
  //ledcAttachPin(IN1_DERECHA,  IN1_DER);
  ledcAttachPin(IN2_DERECHA, IN2_DER);

  pinMode(IN1_IZQUIERDA, OUTPUT);
  //pinMode(IN2_IZQUIERDA, OUTPUT);
  pinMode(IN1_DERECHA, OUTPUT);
  //pinMode(IN2_DERECHA, OUTPUT);
  controlarMotores(velMIN, velMIN);
  // To get the BD Address (MAC address) call:


  const uint8_t* addr = BP32.localBdAddress();
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
  // a "device factory reset", or similar.
  // Calling "forgetBluetoothKeys" in setup() just as an example.
  // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
  // But might also fix some connection / re-connection issues.
  //  BP32.forgetBluetoothKeys();
  int buttonState = digitalRead(Olvidar);
  if (buttonState == true) {

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
      Serial.print("CALLBACK: Controller is disconnected from index=");
      controlarMotores(0, 0);
      Serial.println(i);
      myControllers[i] = nullptr;
      foundGamepad = true;
      break;
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

  int MapBateria = map(bateria, 0, 255, 0, 100);
  // Invierte el mapeo de valorThrottle
  int mapThrottle = map(valorThrottle, 0, 1020, 1023, MINpwm);  // Rango ajustado a 0 a 1023

  int mapBrake = map(valorBrake, 0, 1020, 1023, MINpwm);  // Rango ajustado a -1023 a 1023

  if (abs(valorAxisX) < deadband) {
    // Si el valor del eje X está dentro del rango del deadband, establecerlo a cero
    mapaxisX = 0;
  } else {
    // Si está fuera del rango del deadband, aplicar el mapeo normal
    mapaxisX = map(valorAxisX, -550, 550, -1023, 1023);
  }


  // Ajusta mapBrake y mapaxisX en función de mapThrottle
  if (valorThrottle > valorBrake) {
    mapaxisX = mapaxisX * abs(mapThrottle) / 1023;
    VelMI = mapThrottle - mapaxisX;  //+ mapBrake;  // Aquí restamos mapaxisX "GIRO" SE MUEVE HACIA LA DERECHA
    VelMD = mapThrottle + mapaxisX;  //+ mapBrakeX;  // Aquí sumamos mapaxisX "GIRO" SE MUEVE HACIA LA IZQUIERDA

    if (VelMI > 1023) {
      VelMI = VelMI - (mapThrottle * 2) - (abs(mapaxisX) / 1.4);
    }
    if (VelMD > 1023) {
      VelMD = VelMD - (mapThrottle * 2) - (abs(mapaxisX) / 1.4);
    }


  } else if (valorBrake > valorThrottle) {
    // Si se aplica el brake con fuerza (ajusta el valor según tu necesidad), el vehículo se mueve en reversa
    mapaxisX = mapaxisX * abs(mapBrake) / 1023;
    VelMI = mapBrake + mapaxisX;  // Aquí restamos mapaxisX "GIRO" SE MUEVE HACIA LA DERECHA
    VelMD = mapBrake - mapaxisX;  // Aquí sumamos mapaxisX "GIRO" SE MUEVE HACIA LA IZQUIERDA


    if (VelMI > 1023) {
      VelMI = (VelMI - (mapBrake * 2) - (abs(mapaxisX) / 1.4));
    }
    if (VelMD > 1023) {
      VelMD = (VelMD - (mapBrake * 2) - (abs(mapaxisX) / 1.4));
    }
    VelMI = -VelMI;
    VelMD = -VelMD;

  }


  else if (valorThrottle == 0 && valorBrake == 0) {
    // En este caso, Throttle es igual a Brake, puedes tomar medidas adicionales si es necesario.
    VelMI = velMIN;
    VelMD = velMIN;
  }


  controlarMotores(VelMI, VelMD);
  // Serial.println("Velocidad izquierda: " + String(VelMI) + ", Velocidad derecha: " + String(VelMD) + ", mapaxisX: " + String(mapaxisX) + ",brake: " + String(mapBrake));
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
    ledcWrite(IN2_IZQ, 1023);//eliminar si se cambia de driver PWM/DIR
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
    ledcWrite(IN2_DER, 1023);//eliminar si se cambia de driver PWM/DIR
  }
}



// Arduino loop function. Runs in CPU 1
void loop() {
  // This call fetches all the controller info from the NINA (ESP32) module.
  // Just call this function in your main loop.
  // The controllers pointer (the ones received in the callbacks) gets updated
  // automatically.
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
