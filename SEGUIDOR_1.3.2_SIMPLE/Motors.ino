
#include <Servo.h>

Servo esc;  // Objeto para el ESC
#define INH 12
#define INB1 6
#define INB2 9
#define INA1 5
#define INA2 10
#define PWMC 11

#define t_wakeup_uS 5
#define t_stdby_uS 100

void motorsInit() {

    // Configuración Timer1 (D9, D10) en Fast PWM 8 bits, prescaler 64 (~976 Hz)
 // TCCR1A = _BV(WGM10) | _BV(COM1A1) | _BV(COM1B1); 
 //TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);    
  //  motor drivers inhibit
  pinMode(INH, OUTPUT);

  // motor A driver
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);

  //  motor B driver
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);

  //  impeller
 // pinMode(PWMC, OUTPUT);
  esc.attach(11, 1000, 2000);  // rango seguro 1000-2000us
  esc.writeMicroseconds(1000);
 delay(300);

  // Paso 1: mandar señal máxima

  digitalWrite(INH, 0);
  digitalWrite(INA1, 0);
  digitalWrite(INA2, 0);
  digitalWrite(INB1, 0);
  digitalWrite(INB2, 0);
  digitalWrite(PWMC, 0);
}

void enableMotorDrivers() {
  digitalWrite(INH, 1);
  delayMicroseconds(t_wakeup_uS);
}

void disableMotorDrivers() {
  digitalWrite(INH, 0);
  digitalWrite(INA1, 0);
  digitalWrite(INA2, 0);
  digitalWrite(INB1, 0);
  digitalWrite(INB2, 0);
  delayMicroseconds(t_stdby_uS);
}

void setImpellerPWM(int _pwm) {
  if (!areMotorsEnabled) return;
  //analogWrite(PWMC, _pwm > 0 && _pwm <= 255 ? _pwm : 0);
esc.writeMicroseconds(_pwm >= 1000 && _pwm <= 2000 ? _pwm : 1000);

}




void setPWM_MotorA(int _pwm) {
 // if (!areMotorsEnabled) return;

  if (_pwm < 0) {
    digitalWrite(INA2, 0);
    analogWrite(INA1, abs(_pwm));
  } else if (_pwm > 0) {
    digitalWrite(INA2, 1);
    analogWrite(INA1, 255 - abs(_pwm));
  } else {
    digitalWrite(INA1, 0);
    digitalWrite(INA2, 0);
  }
}

void setPWM_MotorB(int _pwm) {
 // if (!areMotorsEnabled) return;

  if (_pwm < 0) {
    digitalWrite(INB2, 1);
    analogWrite(INB1, 255 - abs(_pwm));
  } else if (_pwm > 0) {
    digitalWrite(INB2, 0);
    analogWrite(INB1, abs(_pwm));
  } else {
    digitalWrite(INB1, 0);
    digitalWrite(INB2, 0);
  }
}

void motorTest() {
  delay(500);

  int ON_TIME_MS = 400;
  int OFF_TIME_MS = 1000;
  int MOTOR_PWM_TEST = 60;

  enableMotorDrivers();

  // motor A
  setLED_0(1);
  setPWM_MotorA(MOTOR_PWM_TEST);
  delay(ON_TIME_MS);
  setLED_0(0);
  setPWM_MotorA(0);
  delay(OFF_TIME_MS);
  setLED_0(1);
  setPWM_MotorA(-MOTOR_PWM_TEST);
  delay(ON_TIME_MS);
  setLED_0(0);
  setPWM_MotorA(0);
  delay(OFF_TIME_MS);

  // motor B
  setLED_1(1);
  setPWM_MotorB(MOTOR_PWM_TEST);
  delay(ON_TIME_MS);
  setLED_1(0);
  setPWM_MotorB(0);
  delay(OFF_TIME_MS);
  setLED_1(1);
  setPWM_MotorB(-MOTOR_PWM_TEST);
  delay(ON_TIME_MS);
  setLED_1(0);
  setPWM_MotorB(0);
  delay(OFF_TIME_MS);

  disableMotorDrivers();
}