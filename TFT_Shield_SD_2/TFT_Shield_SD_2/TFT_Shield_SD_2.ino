/*This code is meant for the 2.4" TFT LCD touch screen shield with UNO board
 * It creates a little slide show of images that changes depending on where you pressed on the screen
 * The images are read from SD card
 * Refer to SurtrTech.com for more details
 */

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>                      
#include <SPFD5408_TouchScreen.h>    //Touch screen functions library


#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif


//The parameters bellow depends on your shield so make sure the pins are correct
#define YP A3  // must be an analog pin, use "An" notation!   
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//Don't forget if your touch function doesn't work check the values above it may be (A1 A2 7 6) resp

// Calibrate values you may want to run the calibration code first and set those points
#define TS_MINX 176
#define TS_MINY 159
#define TS_MAXX 921
#define TS_MAXY 884
#define MINPRESSURE 10
#define MAXPRESSURE 1000


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define SD_CS 10    // Set the chip select line to whatever you use

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);

char x[]="x1.bmp";
/*Here in this code I declared the names as an Array
 * So I can do modifications if I want to scroll through
 * Make sure you images have a number like "1" so you can increase it or decrease 
 * to go to the next image
 */

void setup()
{
 
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  tft.begin(identifier);
  if (!SD.begin(SD_CS)) {
  progmemPrintln(PSTR("failed!"));
  return;
  }
  tft.setRotation(1); //To do a 90° rotation of the screen
  bmpDraw(x, 0, 0);   //we draw the first image which is x -> "x1.bmp" as we declared
}

void loop()
{
if(x[1]<49)     //So we don't go to some strange values I add here a reset of the values
x[1]=49;        //If we're already in the first picture we stay there, same for the last
if(x[1]>52)     //"1" in char is "49" and "4" is "52" I wrote them in this format so I can manipulate them
x[1]=52;

  
  TSPoint p = ts.getPoint();       //checking if the user touched the screen

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { //p.z means the pressure value so if the touch wants to be detected
                                               // it pressure should be in this range (it's enough)

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());    //x and y positions of the touch so the program know the postion where the user has pressed
    
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());;

//The screen is rotated like in setRotation(1) so now I'm playing on Y axis only
//And here I got like two big rectangles on the sides of the screen that are considered as buttons
//You can add conditions on x to make small buttons

    if(p.y > 0 && p.y < 100 ){   
    Serial.println("Left");    //I did this to show on serial monitor that I pressed left
    x[1]=x[1]-1;               //here we change the name of the file we want to read x[]="x1.bmp" and x[1] is the 1 in the name and x[0] is x
    bmpDraw(x, 0, 0);          //So what I do is just increase it to make it 2 or decrease it to make it 0 (refer to the first "if" to see the solution for this case as 0 doesn't exist)
    delay(300);                //Then I draw the image which now has a different name depending on which side I pressed
    }                          //Adding a little delay so the touch detection wont bounce

     else if(p.y >200 && p.y <320){
     Serial.println("Right");
     x[1]=x[1]+1;
     bmpDraw(x, 0, 0);
     delay(300);
    }
  }
  

}


#define BUFFPIXEL 20        //Printing speed 20 is meant to be the best, you can go to 60 but using too much RAM

//drawing function no touchy :D
void bmpDraw(char *filename, int x, int y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  progmemPrint(PSTR("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    progmemPrintln(PSTR("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    progmemPrint(PSTR("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    progmemPrint(PSTR("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    progmemPrint(PSTR("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      progmemPrint(PSTR("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        progmemPrint(PSTR("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if(lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        } 
        progmemPrint(PSTR("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) progmemPrintln(PSTR("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

// Copy string from flash to serial port
// Source string MUST be inside a PSTR() declaration!
void progmemPrint(const char *str) {
  char c;
  while(c = pgm_read_byte(str++)) Serial.print(c);
}

// Same as above, with trailing newline
void progmemPrintln(const char *str) {
  progmemPrint(str);
  Serial.println();
}

