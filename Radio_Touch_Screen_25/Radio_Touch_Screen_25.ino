
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
          
#include "MAX30105.h"            /
#include "heartRate.h"  
MAX30105 particleSensor;
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "incFile1.h"
#include <Adafruit_SSD1306.h>    // OLED Library
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


const byte RATE_SIZE = 4;        // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];           // Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;               // Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

bool BT3 = false;
byte StN = 0;          // Номер станции из массива биндов станций
int StFreq [] = {9190, 10340, 9640,9860,10090,9320,10450,10780,9910};

                    // 13 символов
char StName[][14] = { "  Humor FM   ", "    ROCKS    ", "Radio Mogilev", "Russkoe radio", "  Radius FM  ",
                    "   Pilot FM  ", "  Radio BA   ", "     Mir     ", "   Culture   "  };

// датчик температуры, давления и влажности

   
  // uint8_t pressureUnit(5);    




#include <TouchScreen.h>
// калибровка тачскрина
#define TS_MINX 84
#define TS_MINY 62
#define TS_MAXX 953
#define TS_MAXY 904

// Сила нажатия на дисплей
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Последним параметром указывается сопротивление между X+ и X-
// Для данных дисплеев 300 подойдет
uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

/* some RGB color definitions            */                                  
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */

#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define GREY    0x2108
// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
int pulsePin = 0;                   // Sensor de Pulso conectado al puerto A0
// Estas variables son volatiles porque son usadas durante la rutina de interrupcion en la segunda Pestaña

uint32_t runTime = -99999;       // time for next update
int reading = 0; // Value to be displayed
int d = 0; // Variable used for the sinewave test waveform
boolean alert = 0;
int8_t ramp = 1;

int p_X, p_Y, Vol;
byte P_X, P_Y, P_Button;

void setup(void) {
    Wire.begin();
     mlx.begin(); 
    pinMode(10, OUTPUT); //реле
    digitalWrite(10, HIGH); //Отключаем реле
    pinMode(13, OUTPUT);
    uint16_t ID = tft.readID(); //
    tft.begin(ID);
    tft.setRotation(1);    //Landscape
    tft.fillScreen(Black);
     tft.drawBitmap(0,0,BARRERA, 320, 240,BLACK, YELLOW);
    Serial.begin(115200);
 
 
    tft.fillCircle(160, 108, 4, White); //Точки между час и мин
    tft.fillCircle(160, 130, 4, White);
     
//    tft.fillCircle(265, 126, 2, LightGrey); //Точки между мин и сек
//    tft.fillCircle(265, 136, 2, LightGrey);
           
         tft.setTextSize(2);
         tft.setTextColor(Green, Black);
         tft.setCursor(71,210);
         tft.print("2");       
         tft.fillTriangle(64, 238, 255, 238, 255, 206, Black);  
         tft.drawTriangle(64, 238, 255, 238, 255, 206, Green);
   
         
          tft.setTextSize(2);
          tft.setCursor(8,70);          
          tft.drawRect(1,61,48,34,DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("BT1"); 
                 
          tft.setCursor(8,118);          
          tft.drawRect(1,109,48,34, DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("BT2"); 
       
          tft.setCursor(8,166);          
          tft.drawRoundRect(1,157,48,34,8, DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("FAN"); 
          
          tft.setCursor(8,214);          
          tft.drawRoundRect(1,205,48,34,8, DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("MUT");  

          tft.setCursor(276,70); 
          tft.drawRoundRect(271,109,48,34,8, DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("BT4");  

          tft.setCursor(276,118); 
          tft.drawRoundRect(271,61,48,34,8, DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("BT5");  
          
          tft.setCursor(276,166); 
          tft.drawRoundRect(271,157,48,34,8, DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("BT6");   

          tft.setCursor(276,214); 
          tft.drawRoundRect(271,205,48,34,8, DarkGrey);
          tft.setTextColor(DarkGrey, Black);
          tft.print("BAS");   
 particleSensor.begin(Wire, I2C_SPEED_FAST);    // Use default I2C port, 400kHz speed
  particleSensor.setup();                        // Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);     // Turn Red LED to low to indicate sensor is running

 }


void loop()
{
       // Отображаем Дату и время
        if(millis()%1000==0){ // если прошла 1 секунда
        tft.setTextColor(White, Black);
        tft.setTextSize(7);
        tft.setCursor(67, 92);           // выводим время - час
     
 //       tft.setCursor(160, 90);           // выводим :
 //       tft.print(":");  
        tft.setCursor(175, 92);           // выводим время - мин
       
       
        tft.setCursor(274,120);
        tft.setTextColor(LightGrey, Black);
        tft.setTextSize(3);
  //      tft.println(time.gettime("s"));
        tft.setTextColor(Yellow, Black);
        tft.setTextSize(2);
        tft.setCursor(72, 156);
       
//        tft.println(time.gettime("d.m.Y")); // выводим дату
        delay(1); // приостанавливаем на 1 мс, чтоб не выводить время несколько раз за 1мс
 // Отображаем данные с датчика BME-280
    
      tft.setTextColor(Orange, Black);
      tft.setTextSize(2);
      tft.setCursor(78, 60);
      tft.print("Bienvenido <3");
     tft.setTextSize(1);
      tft.setCursor(70, 180);
      tft.setTextColor(Olive, Black);
  
      tft.print("presiona una opcion ");       
        
        
        } // Конецблока вывода даты/времени

 
  digitalWrite(13, HIGH);
  // Считываем координаты нажатия
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

 
  // **************************** ОБРАБОТКА НАЖАТИЯ НА ТАЧСКРИН ********************************************
  // Если сила нажатия попадает в допустимый диапазон то начинаем обработку
 if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
  // Переводим координаты в размеры разрешения дисплея
  p.x = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
  p.y = map(p.y, TS_MINY, TS_MAXY, tft.width(), 0);

  // Преобразуем снятые координаты в координаты экрана
  p_X=320-p.y;
  p_Y=p.x;
  // Получаем координаты кнопок в поле 5х4
  P_X = p_X/64;
  P_Y = p_Y/48;
  P_Button = P_X*10+P_Y; // Формируем номер кнопки
int last;
 // Если попали в зону меню то очищаем экран
 //  if (p_X > tft.width()) {  tft.fillScreen(Black);   }
           
 //-------------- ОБРАБОТКА ВИРТУАЛЬНЫХ КНОПОК --------------
if(P_Button !=last){
switch ( P_Button ) {
    case 0: { // Если нажата кнопка "0"
          if (StN==0) StN=8;
          else --StN;
          StChange (StN);

    tft.fillTriangle(40, 8, 40, 38, 8,24 , Cyan);
     delay (300); // ждем 0,3 сек чтобы предотвратить повторное нажатие
    tft.fillTriangle(40, 8, 40, 38, 8,24 , Black);
    tft.drawTriangle(40, 8, 40, 38, 8,24 , Cyan);
            }   break;
    case 40: { // Если нажата кнопка "40"
           if (StN==8) StN=0;
           else ++StN;
           StChange (StN);
    tft.fillTriangle(280, 8, 280, 38, 310, 24, Cyan);
    delay (300); // ждем 0,3 сек чтобы предотвратить повторное нажатие
    tft.fillTriangle(280, 8, 280, 38, 310, 24, Black);    
    tft.drawTriangle(280, 8, 280, 38, 310, 24, Cyan);
             }   break;

    case 3: { // Если нажата кнопка "3"
   
   
     tft.reset();
 
   tft.setRotation(1); 
   tft.fillScreen(0x0000);
    tft.setCursor (75,78);
    tft.setTextSize (1);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("TEMPERATURA");
    
    tft.setCursor (75,66);
    tft.setTextSize (1);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("BARRERA.INO");

    tft.setCursor (242,20);
    tft.setTextSize (1);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("FAHRENHEIT");

    tft.setCursor (242,118);//heat index fahrenheit
    tft.setTextSize (3);
    tft.setTextColor (WHITE,BLACK);
    tft.print ("BPM");

    tft.setCursor (238,205);//heat index fahrenheit
    tft.setTextSize (2);
    tft.setTextColor (WHITE,BLACK);
    tft.println ("SP0%");
    
//Design Interface (lines)
    tft.fillRect(0,197,320,4,BLUE);
    tft.fillRect(0,236,320,4,BLUE);
    tft.fillRect(217,0,4,240,BLUE);
    tft.fillRect(217,98,320,4,BLUE);// your hand is a few inches from the sensor
  int xpos = 0, ypos = 5, gap = 4, radius = 52; //dibujo el metro
  xpos = 320/2 - 160, ypos = 0, gap = 100, radius = 105;
  ringMeter(mlx.readObjectTempC(),30,41, xpos,ypos,radius,"Grados",BLUE2RED); // metro analogo  
          
          }   
    
    
    
    
    case 4: { // Если нажата кнопка "4" включаем/отключаем громкость (MUTE)
   
  
          }   break;

  // --- Область ползунка громкости занимает 3 нижних кнопки ---
    case 14: { // Если нажата кнопка "13"
    Volume (p_X);   
            }   break;
    case 24: { // Если нажата кнопка "23"
    Volume (p_X);  
            }   break;
    case 34: { // Если нажата кнопка "33"
    Volume (p_X);   
            }   break;
  
   // --- Область ползунка громкости ---
    case 44: { // Если нажата кнопка "43"
    

    
            }   break;
}
                } //-------------- КОНЕЦ ОБРАБОТКИ ВИРТУАЛЬНЫХ КНОПОК --------------

last= P_Button;

  
  } // **************************** КОНЕЦ ОБРАБОТКИ НАЖАТИЯ НА ТАЧСКРИН ********************************************
  
 }



  void Volume (int Vol_p_X) //функция установки значения громкости и отображения информации о громкости на экране
   {
 //        tft.setContrast(12); 
         
        
         if (((Vol_p_X-64)/12) != Vol )
         {   
          
         Vol = ((Vol_p_X-64)/12);
         // Отображаем на экране значение громкости 
         tft.setTextSize(2);
         tft.setTextColor(Green, Black);
         tft.setCursor(71,210);
         tft.print(Vol); 
         if (Vol<10)tft.print(" ");
         tft.fillTriangle(64, 238, 255, 238, 255, 206, Black);  
         tft.drawTriangle(64, 238, 255, 238, 255, 206, Green);
         tft.fillTriangle( 64, 238, 63+((Vol+1)*12), 238,63+((Vol+1)*12), 238-((Vol+1)*2), Green);
         } 
   }
  
  void StChange (int St) //функция смены радиостанции и отображения информации о новой станции на экране
   {
   
      char s[12];
      tft.setTextColor(Cyan, Black);
      tft.setTextSize(4);
      tft.setCursor(68, 10);
      tft.print((St+1));
      tft.setTextSize(2);
      tft.setTextColor(Cyan, Black);
      tft.setCursor(120, 6);
     

      tft.println(s);
      tft.setTextSize(2);
      tft.setTextColor(Cyan, Black);
      tft.setCursor(106, 28);
      tft.println((StName[St]));
  //  tft.println(utf8rus(StName[St]));
    }




    
// #########################################################################
//  Draw the meter on the screen, returns x coord of righthand side
// #########################################################################
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
  
  x += r; y += r;   // Calculate coords of centre of ring
  int w = r / 3;    // Width of outer ring is 1/4 of radius 
  int angle = 150;  // Half the sweep angle of meter (300 degrees)
  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v
  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring
  // Variable to save "value" text colour from scheme and set default
  int colour = BLUE;
 
  // Draw colour blocks every inc degrees
  for (int i = -angle+inc/2; i < angle-inc/2; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      switch (scheme) {
        case 0: colour = RED; break; // Fixed colour
        case 1: colour = GREEN; break; // Fixed colour
        case 2: colour = BLUE; break; // Fixed colour
        case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
        case 4: colour = rainbow(map(i, -angle, angle, 70, 127)); break; // Green to red (high temperature etc)
        case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
        default: colour = BLUE; break; // Fixed colour
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      //text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, GREY);
    }
  }



  
  // Convert value to a string
  char buf[10];
  byte len = 5; if (value > 999) len = 9;
  dtostrf(value, len, 5, buf);
 
  // Set the text colour to default
  tft.setTextSize(1);

  if(value>9){
  tft.setTextColor(colour,BLACK);
  tft.setCursor(x-45,y-10);
  tft.setTextSize(4);
  tft.print((mlx.readObjectTempC()+3),1);
  
  }

  
  if(value<10){
  tft.setTextColor(colour,BLACK);
  tft.setCursor(x-25,y-10);tft.setTextSize(5);
  tft.print(buf);}

  tft.setTextColor(WHITE,BLACK);
  
  tft.setCursor(x-39,y+75);tft.setTextSize(2);
  tft.print(units); // Units display
  
  // Calculate and return right hand side x coordinate
  return x + r;
}

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits
  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;






  
}

// #########################################################################
// Return a value in range -1 to +1 for a given phase angle in degrees
// #########################################################################
float sineWave(int phase) {
  return sin(phase * 0.0174532925);
}





void estadoT()
{ 
  long f=mlx.readObjectTempF();long temp=mlx.readObjectTempC()+3;

    tft.setCursor (230,38);
    tft.setTextSize (3);
    tft.setTextColor (BLUE,BLACK);
    tft.print (mlx.readObjectTempF(),1); 
  
  
  if (mlx.readObjectTempC()+3>37.1){ 
    tft.setCursor (2,220);//Small celcius text
    tft.setTextSize (2);
    tft.setTextColor (YELLOW,BLACK);
    tft.println ("    FEBRICULA    ");
  }
 
if(temp >= 36 && temp <=37)
{  tft.setCursor (2,220);//Small celcius text
    tft.setTextSize (2);
    tft.setTextColor (GREEN,BLACK);
    tft.println ("    Estable    ");
   
}
if(temp <36)
{  tft.setCursor (2,220);//Small celcius text
    tft.setTextSize (2);
    tft.setTextColor (RED,BLACK);
    tft.println ("    Acercate   ");
   
}
tft.drawBitmap(285,165,cora, 20, 14,BLACK,RED);  }

















void bmp(){ long irValue = particleSensor.getIR();              // Reading the IR value it will permit us to know if there's a finger on the sensor or not

  if (irValue > 50000)
  {

    if (checkForBeat(irValue) == true)                  //If a heart beat is detected, call checkForBeat as frequent as possible to get accurate value
    {
      long delta = millis() - lastBeat;                 //Measure duration between two beats
      lastBeat = millis();
      beatsPerMinute = 60 / (delta / 1000.0);           //Calculating the BPM
      if (beatsPerMinute < 255 && beatsPerMinute > 20)  //To calculate the average we strore some values (4) then do some math to calculate the average
      {
        rates[rateSpot++] = (byte)beatsPerMinute;       //Store this reading in the array
        rateSpot %= RATE_SIZE;                          //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
   tone(44,1000);                                        //And tone the buzzer for a 100ms you can reduce it it will be better
    delay(100);
    noTone(44);      

 
      tft.setTextSize(3);
       tft.setCursor (242,100);//heat index fahrenheit
         tft.print(beatAvg);
      
      }
    }
  }
  else
  {

     tft.setTextSize(3);
 tft.setCursor (242,100);//heat index fahrenheit
   tft.print(0);
tft.setCursor (242,100);//heat index fahrenheit
    tft.setTextSize(1);
    tft.print("Place your finger in sensor and wait..");
  
     noTone(44);  
  }
}
