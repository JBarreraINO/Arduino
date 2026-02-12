

float KP=0.016;  //  proportional component coefficient
float KD=0.3;   //  derivative component coefficient

float PWM_MOTORS =50;
int PWM_IMPELLER=2000;

bool INVERT_SENSOR_READS =false;  //  white line and black background if false (true = black line)

#define MOTORS_PWM_TIME_MS 50  //  time until wheel motors gets base PWM in milliseconds
#define IMP_PWM_TIME_MS 250     //  time until impeller motor gets base PWM in milliseconds

//  =====================================
//  A D V A N C E D   P A R A M E T E R S
//  =====================================

bool isConsoleMode = false;
bool areMotorsEnabled = true;

//  TIME
#define CONTROL_LOOP_PERIOD_US 750
#define START_IMPELLER_RAMP_TIME_MS 1000
#define STOP_BRAKE_TIME_MS 85
#define OFFLINE_INNER_OFF_TIME_MS 100

//  PWM
int OFFLINE_OUTTER_PWM =115;
int OFFLINE_INNER_PWM =-115;

//  OTHERS
int SENSOR_THRESHOLD_PERCENT =15;

//  ===============================
//  G L O B A L   V A R I A B L E S
//  ===============================

//  global sensor variables
#define TOTAL_SENSORS 16
int sensorValues[TOTAL_SENSORS];
unsigned int maxSensorValues[TOTAL_SENSORS];
unsigned int minSensorValues[TOTAL_SENSORS];
byte sensorThreshold[TOTAL_SENSORS];

//  global time variables
unsigned long startTime;
unsigned long currentTime;
unsigned long elapsedTime;
unsigned long offlineStartTime;

//  global run controller variables
bool isOnLine;
bool isRunning;

int motPWMDecrement = 180;
int impPWMDecrement = 255;

bool lastDetectedSide;

unsigned long previousLooptime_uS;

int error;
int previousError;
int deltaError;
int valPWMA;
int valPWMB;
int valPWMImp;
String inputData = "";
void setup() {
  readEEpromValues();
  SerialES();
  cli();  //  disable global interrupts
  consoleInit();
  UIInit();
  sensorsInit();
  motorsInit();
  sei();  //  enable global interrupts

  //  debug mode trigger
  /*
  if (readButton_2()) {
    confirmAnimation(500, 1);
    debugMode();
  }
*/
  bootAnimation();  //  boot display animation

  //  ===================
  //  I D L E   S T A T E
  //  ===================

  while (!readButton_2());

  calibrateSensors();
  delay(250);

  if (isConsoleMode) {
    //  sensors testing trigger
    while (!readButton_2()) {
    };
    setLED_0(1);
    delay(250);
    setLED_0(0);

    //  sensors testing infinite loop
    while (1) {
      if (readButton_2()) {
        readCalibratedSensors();
      } else {
        readRawSensors();
      }
      printSensorValues();
    }
  }

  runningLoop();
}

void loop() {
}

void debugMode() {
  bool imp_flag = false;

  while (1) {
    //  motor test
    if (readButton_2()) {
      motorTest();
    }

    //  impeller test
    if (readButton_2()) {
      if (!imp_flag) {
        imp_flag = true;
        impellerRamp();
        setLED_2(1);
      } else {
        imp_flag = false;
        setImpellerPWM(0);
        setLED_2(0);
        delay(250);
      }
    }
  }
}