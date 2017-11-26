 // Currently copied from lab. Needs to be modded for project


// Use the library Softwareserial to use pins 2 and 3 of the arduino for serial comunication with the bluetooth unit
// pins 0 and 1 are not use to be able to lead the program and read the program output on the Arduino serial monitor

#include<SoftwareSerial.h>
#include <Sparkfun_DRV2605L.h>
#include <Wire.h>

SFE_HMD_DRV2605L HMD;
const int analogInPin = A0;  // Analog input pin that the sensor is attached to
const int analogOutPin = 9; // Analog output pin that the Haptic Motor Driver is attached to

int bluetoothTx = 2;
int bluetoothRx = 3;

int sensorValue = 0;        // value read from the sensor
int outputValue = 0;        // value output to the PWM (analog out)


// store voltages from thumb and index pressure sensors

int pressureThumb = 0;
float pressureThumbVolt = 0.0;

int pressureIndex = 0;
float pressureIndexVolt = 0.0;

// Declare string
String thumbVoltStr;
String indexVoltStr;

// indicates that pin 2 of the Arduino is connected to the Tx pin of the bluetooth unit and pin 3 is connected to the Rx pin of the bluetooth unit

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {


// startup serial connection to computer
Serial.begin(9600);

// Setup Bluetooth serial connection by programming the unit to communicate at 9600 bauds
  HMD.begin();
  
  HMD.Mode(0x03); //PWM INPUT 
  HMD.MotorSelect(0x0A);
  HMD.Library(7); //change to 6 for LRA motors 
  
  bluetooth.begin(115200);
  bluetooth.print("$");
  bluetooth.print("$");
  bluetooth.print("$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

}

void loop() {

/*
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());  
  }
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
  }
  // and loop forever and ever!
*/




  // Read pressure sensor voltages
  // Thumb = A0
  // Index = A1

   // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  if(sensorValue < 3)
    analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);
  
  pressureThumb = analogRead(A0);
  pressureThumbVolt = float(pressureThumb)*3.0/1023.0;
  thumbVoltStr = String(pressureThumbVolt);

  pressureIndex = analogRead(A1);
  pressureIndexVolt = float(pressureIndex)*5.0/1023.0;
  indexVoltStr = String(pressureIndexVolt);

  // transmit the string to the bluetooth unit

  bluetooth.println(thumbVoltStr);
  bluetooth.println("\t");
  bluetooth.println(indexVoltStr + "\r\n");

  // display the string on the serial monitor

  Serial.println(thumbVoltStr);
  // Serial.println(indexVoltStr);

  // small delay between data transmissions

  delay(100);

}
