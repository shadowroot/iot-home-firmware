#include <Arduino.h>
#include <SoftwareSerial.h>

#define ESP8266_PROG_BAUDRATE 57600
#define TX_PIN 10
#define RX_PIN 11
#define EN_PIN 12

SoftwareSerial progSerial(RX_PIN, TX_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(ESP8266_PROG_BAUDRATE);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for Native USB only
  }
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);
  progSerial.begin(ESP8266_PROG_BAUDRATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (progSerial.available()){
    Serial.write(progSerial.read());
  }
  if (Serial.available()){
    progSerial.write(Serial.read());
  }
}