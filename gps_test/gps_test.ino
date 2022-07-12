#include <NMEA0183.h>
#include <SoftwareSerial.h>
// matches Zihatec RS422/RS485 shield
SoftwareSerial gps(12,13);
NMEA0183 nmea;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  gps.begin(4800);
  Serial.println("NMEA0183 parser test");
}

void loop()
{
  if (gps.available())
  {
    char c = gps.read();
    if (nmea.update(c))
    {
      Serial.print("NMEA0183 sentence accepted (");
      Serial.print(nmea.getFields());
      Serial.print(" fields): ");
      Serial.write(nmea.getSentence());
      Serial.println();
    }
  }
}
