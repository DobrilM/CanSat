#include <SPI.h>
#include <RH_RF95.h>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
/*
    Needed libs:
  -Adafruit BMP3XX Library (by Adafruit)
  -RadioHead (by Mike McCauley)
  -dependencies of those two (already installed automatically)
*/
#define RFM95_CS    8
#define RFM95_INT   3
#define RFM95_RST   4
#define RF95_FREQ   433.0  // MHz !!CHANGE BEFORE LAUNCH!!

#define BMP_CS 10

#define PRESSURE_SEA 1008.3 // hPa !!CHANGE BEFORE LAUNCH!!

RH_RF95 rf95(RFM95_CS, RFM95_INT);
Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  SPI.begin(); 
  pinMode(BMP_CS, OUTPUT);
  digitalWrite(BMP_CS, HIGH);

  if (!bmp.begin_SPI(BMP_CS)) {
    Serial.println("Cant find bmp");
    while(1);
  }
  Serial.println("bmp is running");

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("rf doesnt initialize");
    while(1);
  }

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("Frequenty cannot be set");
    while(1);
  }

  rf95.setTxPower(4, false); //power as low as needed (2 - 20 input) (interferes with other sources)

}

void loop() {
  if (!bmp.performReading()) {
    Serial.println("BMP388 not reading");
    return;
  }

  float temp = bmp.temperature;
  float pressure = bmp.pressure / 100.0;   //hPa
  float altitude = 44330.0 * (1.0 - pow(pressure / PRESSURE_SEA, 0.1903));

  char message[64];
  sprintf(message, "%.1f;%.2f;%.2f", temp, pressure, altitude);

  rf95.send((uint8_t*)message, strlen(message));
  rf95.waitPacketSent();
  delay(500);
}
