
#include<SoftwareSerial.h>
#include<SPI.h>
#include<Wire.h>

int CS = 10;

int pinIn = A0;
int pinInput = 0;

void setup() {
  pinMode(CS, OUTPUT);
  
  Serial.begin(9600);
  SPI.begin();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE2));

}

void loop() {
  digitalWrite(CS, LOW);
  Serial.println(SPI.transfer(Wire.available()));
  delay(1000);
  digitalWrite(CS, HIGH);
  Serial.println(SPI.transfer(Wire.available()));
  delay(1000);
  

}
