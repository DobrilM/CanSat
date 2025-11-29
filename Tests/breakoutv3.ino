#include <Adafruit_GPS.h>

#define GPSECHO false //true for raw gps data

#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);

uint32_t timer = millis();

void setup() {
  // put your setup code here, to run once:
  GPS.begin(9600);           
  Serial.begin(115200);

  //define the output format and rate
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); 
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   

  // Enable SBAS
  GPS.sendCommand("$PMTK313,1*2E");
  GPS.sendCommand("$PMTK301,2*2E");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  GPS.read();

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;

    if (GPS.fix) {
      Serial.print(GPS.latitudeDegrees, 6);
      Serial.print(";");
      Serial.print(GPS.longitudeDegrees, 6);
      Serial.print(";");
      Serial.print(GPS.satellites);
      Serial.print(";");
      Serial.println(GPS.fixquality);
    }
  }
}
