#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(10,11); // RX, TX

DFRobotDFPlayerMini myDFPlayer;

char command;
int pausa = 0;

void setup()
{
  //Comunicacao serial com o modulo
  mySoftwareSerial.begin(9600);
  //Inicializa a serial do Arduino
  Serial.begin(115200);

  //Verifica se o modulo esta respondendo e se o
  //cartao SD foi encontrado
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Initializing DFPlayer module ... Wait!"));
  
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true);
  }
  
  Serial.println();
  Serial.println(F("DFPlayer Mini module initialized!"));

  //Definicoes iniciais
  myDFPlayer.setTimeOut(500); //Timeout serial 500ms
  myDFPlayer.volume(25); //Volume 5
  myDFPlayer.EQ(0); //Equalizacao normal
  
  menu_opcoes();
}

void loop()
{
 
  //Waits for data entry via serial
  while (Serial.available() > 0)
  {
    command = Serial.read();

     if ((command >= '1') && (command <= '9'))
    {
      Serial.print("Music reproduction");
      Serial.println(command);
      command = command - 48;
      myDFPlayer.play(command);
      menu_opcoes();
    }
   
    //Reproduction
    
    //Stop
    if (command == 's')
    {
      myDFPlayer.stop();
      Serial.println("Music Stopped!");
      menu_opcoes();
    }
    
    //Pausa/Continua a musica
    if (command == 'p')
    {
      pausa = !pausa;
      if (pausa == 0)
      {
        Serial.println("Continue...");
        myDFPlayer.start();
      }
      if (pausa == 1)
      {
        Serial.println("Music Paused!");
        myDFPlayer.pause();
      }
      menu_opcoes();
    }
    
    //Increases volume
    if (command == '+')
    {
      myDFPlayer.volumeUp();
      Serial.print("Current volume:");
      Serial.println(myDFPlayer.readVolume());
      menu_opcoes();
    }
     if (command == '<')
    {
      myDFPlayer.previous(); 
      Serial.println("Previous:");
      Serial.print("Current track:");
      Serial.println(myDFPlayer.readCurrentFileNumber()-1); 
      menu_opcoes();
    }
     if (command == '>')
    {
     myDFPlayer.next(); 
      Serial.println("next:");
      Serial.print("Current track:");
      Serial.println(myDFPlayer.readCurrentFileNumber()+1); 
      menu_opcoes();
    }
    
    //Decreases volume
    if (command == '-')
    {
      myDFPlayer.volumeDown();
      Serial.print("Current Volume:");
      Serial.println(myDFPlayer.readVolume());
      menu_opcoes();
    }
     
  }  
}

void menu_opcoes()
{
  Serial.println();
  Serial.println(F("=================================================================================================================================="));
  Serial.println(F("Commands:"));
  Serial.println(F(" [1-3] To select the MP3 file"));
  Serial.println(F(" [s] stopping reproduction"));
  Serial.println(F(" [p] pause/continue music"));
  Serial.println(F(" [+ or -] increases or decreases the volume"));
  Serial.println(F(" [< or >] forwards or backwards the track"));
  Serial.println();
  Serial.println(F("================================================================================================================================="));
}
