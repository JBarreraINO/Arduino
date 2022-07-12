// More information at: https://www.aeq-web.com

int PWM_PIN1 = 44; //Define Digital PIN
int PWM_PIN2 = 5; //Define Digital PIN
int PWM_PIN3 = 6; //Define Digital PIN

void setup() {
  pinMode(PWM_PIN1, INPUT);
  pinMode(PWM_PIN2, INPUT);
  pinMode(PWM_PIN3, INPUT);
  Serial.begin(115200);
}

void loop() {
  int pwm1 = pulseIn(PWM_PIN1, HIGH); //Read PWM Pulse
  int pwm2 = pulseIn(PWM_PIN2, HIGH); //Read PWM Pulse
  int pwm3 = pulseIn(PWM_PIN3, HIGH); //Read PWM Pulse
  Serial.print("PWM CH1: ");
  Serial.print(pwm1);
  Serial.print(" PWM CH2: ");
  Serial.print(pwm2);
  Serial.print(" PWM CH3: ");
  Serial.println(pwm3);

}
