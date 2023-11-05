
#include <Bluepad32.h>



const int IN1_IZQUIERDA = 26;  // Pin de dirección IN1 para motor izquierdo
const int IN2_IZQUIERDA = 27;  // Pin de dirección IN2 para motor izquierdo
const int IN1_DERECHA = 32;    // Pin de dirección IN1 para motor derecho
const int IN2_DERECHA = 33;    // Pin de dirección IN2 para motor derecho

// propiedades PWM
const int frecuencia = 5000;
const int IN1_IZQ = 0;
const int IN2_IZQ = 2;
const int IN1_DER = 3;
const int IN2_DER = 4;
const int resolucion = 8;

ControllerPtr myControllers[BP32_MAX_CONTROLLERS];

// Arduino setup function. Runs in CPU 1
void setup() {
  // Initialize serial
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect.
    // You don't have to do this in your game. This is only for debugging
    // purposes, so that you can see the output in the serial console.
    ;
  }

  String fv = BP32.firmwareVersion();
  Serial.print("Firmware version installed: ");
  Serial.println(fv);

  
  ledcSetup(IN1_IZQ, frecuencia, resolucion);
  ledcSetup(IN2_IZQ, frecuencia, resolucion);
  ledcSetup( IN1_DER, frecuencia, resolucion);
  ledcSetup(IN2_DER, frecuencia, resolucion);



  ledcAttachPin(IN1_IZQUIERDA, IN1_IZQ);
  ledcAttachPin(IN2_IZQUIERDA, IN2_IZQ);
  ledcAttachPin(IN1_DERECHA,  IN1_DER);
  ledcAttachPin(IN2_DERECHA, IN2_DER);

  pinMode(IN1_IZQUIERDA, OUTPUT);
  //pinMode(IN2_IZQUIERDA, OUTPUT);
  pinMode(IN1_DERECHA, OUTPUT);
  //pinMode(IN2_DERECHA, OUTPUT);

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
  BP32.forgetBluetoothKeys();
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

      // Optional, once the gamepad is connected, request further info about the
      // gamepad.
      ControllerProperties properties = ctl->getProperties();
      char buf[80];
      sprintf(buf,
              "BTAddr: %02x:%02x:%02x:%02x:%02x:%02x, VID/PID: %04x:%04x, "
              "flags: 0x%02x",
              properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
              properties.btaddr[3], properties.btaddr[4], properties.btaddr[5],
              properties.vendor_id, properties.product_id, properties.flags);
      Serial.println(buf);
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

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.print("CALLBACK: Controller is disconnected from index=");
      Serial.println(i);
      myControllers[i] = nullptr;
      foundGamepad = true;
      break;
    }
  }

  if (!foundGamepad) {
    Serial.println(
      "CALLBACK: Controller disconnected, but not found in myControllers");
  }
}

void processGamepad(ControllerPtr gamepad) {
  // There are different ways to query whether a button is pressed.
  // By query each button individually:
  //  a(), b(), x(), y(), l1(), etc...





  int valorThrottle = gamepad->throttle();
  int valorBrake = gamepad->brake();
  int mapThrottle = map(valorThrottle, 0, 1020, 0, 255);
  int mapBrake = map(valorBrake, 0, 1020, 0, 255);
   //ledcWrite(IN1_IZQ, mapBrake );
  
  controlarMotores(mapBrake,mapThrottle);


  // You can query the axis and other properties as well. See
  // Controller.h For all the available functions.
}
void controlarMotores(int velocidadMotorIzquierda, int velocidadMotorDerecha) {
  // Control de la dirección para el motor izquierdo
  if (velocidadMotorIzquierda > 0) {
    digitalWrite(IN1_IZQUIERDA, LOW);  // Gira CW
  
    
    ledcWrite(IN2_IZQ, abs(velocidadMotorIzquierda));
    //ledcWrite(IN1_IZQ, abs(velocidadMotorIzquierda) );
  

  } else if (velocidadMotorIzquierda < 0) {
    digitalWrite(IN1_IZQUIERDA, HIGH);  // Gira CCW
     ledcWrite(IN2_IZQ, abs(velocidadMotorIzquierda));
  } else {
    digitalWrite(IN1_IZQUIERDA, HIGH);  // Detén el motor izquierdo
    digitalWrite(IN2_IZQUIERDA, HIGH);
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
  } else {
    digitalWrite(IN1_DERECHA, HIGH);  // Detén el motor derecho
    digitalWrite(IN2_DERECHA, HIGH);
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
