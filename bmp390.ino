#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <SPI.h>

#define BMP_CS   10
#define BMP_SCK  13
#define BMP_MISO 12
#define BMP_MOSI 11

Adafruit_BMP3XX bmp;
constexpr float hPaSea = 1004.3;
void setup() {
  Serial.begin(115200);

  Serial.println("BMP388 software SPI test");

  if (!bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {
    Serial.println("BMP388 not found!");
    while (1);
  }

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  if (!bmp.performReading()) {
    Serial.println("Reading failed");
    return;
  }
  float pressure = bmp.pressure/100;
  Serial.print(bmp.temperature);
  Serial.print(";");
  Serial.print(pressure);
  Serial.print(";");
  Serial.println(bmp.readAltitude(hPaSea));
  delay(1000);
}
