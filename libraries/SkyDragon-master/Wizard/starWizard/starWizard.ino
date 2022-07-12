/*StarWizard

Ejemplo 1

Conexiones Necesarias:
*Wizard
  -Parlante D0
*Bateria 74.V
*Cable MicroUSB

Objetivo:
*Reproducir una melodia con Wizard
*/
//Definicion de tonos
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
//Ubicacion de los pines
const int buzzerPin = 0; // Buzzer, Digital Pin 0

void setup()
{
  //Configuracion de pines
  pinMode(buzzerPin, OUTPUT); // Digital Pin 0
}

void loop()
{

  //Primera melodia
  PrimeraMelodia();

  //Segunda melodia
  SegundaMelodia();

  //Variant 1
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);

  delay(500);

  //Repite la segunda seccion
  SegundaMelodia();

  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  

  delay(650);
}

void beep(int note, int duration)
{
  //Reproduce tono en el buzzer
  tone(buzzerPin, note, duration);
  delay(duration);

  //Detiene la reproduccion
  noTone(buzzerPin);

  delay(50);
}

void PrimeraMelodia()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);
}

void SegundaMelodia()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);

  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  

  delay(350);
}
/*
Wizard es una tarjeta electronica diseñada para robotica general
contiene las siguientes conexiones:
	*Entradas
		-Boton D14
		-Sensor Bateria A1
		- 7 pines digitales (A11,D16,A0,A9,A6,D7,A8), los A puenden ser analogos
		-Receptor D1 TX
	*Salidas
		-Motor MA(D5-D6)
		-Motor MB(D10-D11)
		-Parlante D0 RX
*/
