#define BUZZER_PIN 3  // Conecta el buzzer al pin 8
#include "pitches.h"
// Notas musicales (frecuencias en Hz)
#define NOTE_B5  988
#define NOTE_E6  1319
#define NOTE_G6  1568
#define NOTE_FS6 1480
#define NOTE_E6  1319
#define NOTE_G6  1568

// Melodía de Victoria de Super Mario
int melody[] = {
  NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_G6, 
  NOTE_C6, NOTE_D6, NOTE_E6,
  NOTE_F6, NOTE_F6, NOTE_F6, NOTE_F6, NOTE_F6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6,
  NOTE_E6, NOTE_D6, NOTE_D6, NOTE_E6, NOTE_D6, NOTE_G6
};

// Duración de las notas: 4 = negra, 8 = corchea, etc.
int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 4, 4
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Reproduce la melodía
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(BUZZER_PIN, melody[i], noteDuration);
    
    // Pequeña pausa entre notas
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
  
  delay(2000);  // Espera 2 segundos antes de repetir
}
