

bool stopBrakeEnabled = false;

void runInit() {
  enableMotorDrivers();

  //  start times
  elapsedTime = 0;
  startTime = millis();
  currentTime = startTime;
  offlineStartTime = startTime;

  previousLooptime_uS = micros();
}

void runningLoop() {
  
while (!readButton_2());  

// Enciende la turbina antes de esperar el GO
delay(2000);                     // tiempo de estabilización
impellerRamp();                  // rampa de encendido





  //  start trigger
  while (!readGo());
 setImpellerPWM(PWM_IMPELLER);
  setLED_2(1);
  setLEDS(1);

  isRunning = readGo();
  stopBrakeEnabled = isRunning;

  runInit();

  while (isRunning) {
    if (micros() - previousLooptime_uS >= CONTROL_LOOP_PERIOD_US) {
      previousLooptime_uS = micros();

      //  get current time
      currentTime = millis();

      //  get delta time
      elapsedTime = currentTime - startTime;

      controlLoop();
    }

    //  off triggers
    if ( readButton_2()) {
      isRunning = false;
    }

    if (!readGo()) {
      isRunning = false;
    }
  }
  //  stop running
  stopRobot();
}

void controlLoop() {
  //  motor increase PWM method
  
  if (motPWMDecrement) {
    if (elapsedTime >= MOTORS_PWM_TIME_MS) {
      motPWMDecrement = 0;
    } else motPWMDecrement = PWM_MOTORS - (PWM_MOTORS * elapsedTime / MOTORS_PWM_TIME_MS);
  }

  //  impeller increase PWM method
  if (impPWMDecrement) {
    if (elapsedTime >= IMP_PWM_TIME_MS) {
      impPWMDecrement = 0;
    } else impPWMDecrement = PWM_IMPELLER - (PWM_IMPELLER * elapsedTime / IMP_PWM_TIME_MS);
  }

  //  get position and error
  unsigned int position = getLinePosition();
  error = position - (TOTAL_SENSORS - 1) * 1000 / 2;

  //  get delta error
  deltaError = error - previousError;
  previousError = error;  //  update previous error

  //  if is online and position is no equal to the limits, calculate control signal and PWM values
  if (isOnLine && position && position != (TOTAL_SENSORS - 1) * 1000) {
    //  check last detected side
    if (sensorValues[0] || sensorValues[1]) lastDetectedSide = 0;
    if (sensorValues[TOTAL_SENSORS - 2] || sensorValues[TOTAL_SENSORS - 1]) lastDetectedSide = 1;

    //  compute control signal
    long controlSignal = (error * KP) + ((long)(deltaError)*KD);

    //  constrain controlSignal;
    if (controlSignal > 1000) controlSignal = 1000;
    else if (controlSignal < -1000) controlSignal = -1000;

    //  get motor PWM values
    valPWMA = PWM_MOTORS + controlSignal - motPWMDecrement;
    valPWMB = PWM_MOTORS - controlSignal - motPWMDecrement;
    valPWMImp = PWM_IMPELLER - impPWMDecrement;

    //  constrain motor PWM values
    if (valPWMA > 255) valPWMA = 255;
    else if (valPWMA < -255) valPWMA = -255;

    if (valPWMB > 255) valPWMB = 255;
    else if (valPWMB < -255) valPWMB = -255;

    //  update last time online
    offlineStartTime = currentTime;

  } else {
    //  ===============================
    //    O F F L I N E   M E T H O D
    //  ===============================

    //  get offline time
    unsigned long offlineElapsedTime = currentTime - offlineElapsedTime;

    //  set motors PWM values in function of last detected side before out
    if (!lastDetectedSide) {
      valPWMA = offlineElapsedTime < OFFLINE_INNER_OFF_TIME_MS ? OFFLINE_INNER_PWM : 0;
      valPWMB = OFFLINE_OUTTER_PWM;
    } else {
      valPWMA = OFFLINE_OUTTER_PWM;
      valPWMB = offlineElapsedTime < OFFLINE_INNER_OFF_TIME_MS ? OFFLINE_INNER_PWM : 0;
    }
  }

  //  update motors PWM
  setPWM_MotorA(valPWMA);
  setPWM_MotorB(valPWMB);
  //setImpellerPWM(valPWMImp);
}

void stopRobot() {
  setLEDS(0);

  if (stopBrakeEnabled) {
    //  instant brake
    setPWM_MotorA(-PWM_MOTORS);
    setPWM_MotorB(-PWM_MOTORS);
    delay(STOP_BRAKE_TIME_MS);
  }

  //  motors off
  setPWM_MotorA(0);
  setPWM_MotorB(0);
  disableMotorDrivers();
  delay(STOP_BRAKE_TIME_MS * 4);

  //  impeller off
  setImpellerPWM(0);

  //  standby
  while (1) {
    setLED_0(1);
    setLED_1(1);
    delay(50);
    setLED_0(0);
    setLED_1(0);
    delay(1000);
  }
}
/*
void impellerRamp() {
  int impRampSpeed = 0;
  startTime = millis();  //  impeller PWM ramp start time

  while (impRampSpeed != PWM_IMPELLER) {
    currentTime = millis();

    if (currentTime - startTime >= START_IMPELLER_RAMP_TIME_MS) {
      impRampSpeed = PWM_IMPELLER;
    } else {
      impRampSpeed = PWM_IMPELLER * (currentTime - startTime) / START_IMPELLER_RAMP_TIME_MS;
    }
    setImpellerPWM(impRampSpeed);
  }
}*/


void impellerRamp() {
  int impRampSpeed = 1000;  // siempre empezar desde 1000us
  unsigned long startTime = millis();
  int target = PWM_IMPELLER - 100;
  if (target < 1000) target = 1000;   // nunca menos del mínimo

  while (impRampSpeed < target) {
    unsigned long currentTime = millis();

    // Calcular cuánto tiempo ha pasado
    unsigned long elapsed = currentTime - startTime;

    if (elapsed >= START_IMPELLER_RAMP_TIME_MS) {
      // Ya terminó la rampa → fijar en destino
      impRampSpeed = target;
    } else {
      // Escalar linealmente entre 1000 y PWM_IMPELLER
      impRampSpeed = 1000 + ( (target - 1000) * elapsed / START_IMPELLER_RAMP_TIME_MS );
    }

    // Limitar a rango válido (1000–2000us)
    if (impRampSpeed < 1000) impRampSpeed = 1000;
    if (impRampSpeed > 2000) impRampSpeed = 2000;

    // Enviar al ESC
    setImpellerPWM(impRampSpeed);

  }
}