#ifndef xmotion_h 
#define xmotion_h	
		

class XMotionClass{ 
	public: 
		XMotionClass(); 
		void SETUP(); 
		void Forward(byte speed, int time);
		void Backward(byte speed, int time);
		void Right0(byte speed, int time);
		void Left0(byte speed, int time);
                void StopMotors(int time);
		void ArcTurn(byte LeftSpeed, byte RightSpeed, int Time);
                void MotorControl(int LeftSpeed, int RightSpeed);
		int Trimpot(); 
                float VoltageIn(); 
		void ToggleLeds(int Time);
                void LipoCutOff(int Cell);
                void CounterLeds(int Time, int countx);
		byte mode();
		bool GetButton();
		void UserLed1(int Time);
        void UserLed2(int Time);
};



extern XMotionClass xmotion; 
#endif