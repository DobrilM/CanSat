#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 8
#define RFM95_INT 3
#define RFM95_RST 4
#define RF95_FREQ 433.1

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  if (!rf95.init()) {
    Serial.println("rf doesnt init");
    while(1);
  }
  if(!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("Freq cannot be set");
    while(1);
  }
  rf95.setTxPower(2, false);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  char message[64] = "TESTTESTTEST";
  rf95.send((uint8_t*)message, strlen(message));
  rf95.waitPacketSent();
  
  Serial.println("Message sent!");
  digitalWrite(LED_BUILTIN, LOW);
  

  delay(1000);
}
