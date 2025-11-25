#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>
//#include <SD.h> (for SD card)


SoftwareSerial toRadio(10, 11);
Adafruit_BMP280 bmp;
constexpr int pressureSea = 100830; // hPa !!CHANGE BEFORE LAUNCH!!
void setup() {
  // put your setup code here, to run once:
  toRadio.begin(9600);
  while(!Serial);
  if (!bmp.begin()) {
      Serial.println("You fucked up, try again :)");
  }
  //txtfile = SD.open("data.txt");
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float height = 44330 *(1.0 - pow(pressure / pressureSea, 0.1903));
/*
  //for SD card:
  txtfile.print(temp);
  txtfile.print(";");
  txtfile.print(pressure);
  txtfile.print(";");
  txtfile.print(height);
  txtfile.println();
  if (height < 3) {
    txtfile.close(); //opening and closing only needed once ()
  }
  //uses shitton of power, maybe only for geiger?
*/
  toRadio.print(temp);
  toRadio.print(";");
  toRadio.print(pressure);
  toRadio.print(";");
  toRadio.println(height);
  delay(500);
}
