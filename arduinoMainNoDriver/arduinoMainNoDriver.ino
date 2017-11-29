// Use the library Softwareserial to use pins 2 and 3 of the arduino for serial comunication with the bluetooth unit
// pins 0 and 1 are not use to be able to lead the program and read the program output on the Arduino serial monitor

#include<SoftwareSerial.h>

const int analogInPin = A0;  // Analog input pin that the sensor is attached to
const int analogOutPin = 9; // Analog output pin that the Haptic Motor Driver is attached to

int bluetoothTx = 2;
int bluetoothRx = 3;

int sensorValue = 0;        // value read from the sensor
double outputValue = 0;        // value output to the PWM (analog out)


// store voltages from thumb and index pressure sensors

int pressureThumb = 0;
float pressureThumbVolt = 0.0;

int pressureIndex = 0;
float pressureIndexVolt = 0.0;

// Declare string
String thumbVoltStr;
String indexVoltStr;

int incomingByte = 0; 

// indicates that pin 2 of the Arduino is connected to the Tx pin of the bluetooth unit and pin 3 is connected to the Rx pin of the bluetooth unit

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {


// startup serial connection to computer
Serial.begin(9600);

// Setup Bluetooth serial connection by programming the unit to communicate at 9600 bauds  
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

}

void loop() {

  // Read pressure sensor voltages
  // Thumb = A0
  // Index = A1

  
  pressureThumb = analogRead(A0);
  pressureThumbVolt = float(pressureThumb)*5.0/1023.0;
  thumbVoltStr = String(pressureThumbVolt);

  pressureIndex = analogRead(A1);
  pressureIndexVolt = float(pressureIndex)*5.0/1023.0;
  indexVoltStr = String(pressureIndexVolt);

  // transmit the string to the bluetooth unit

  bluetooth.println(thumbVoltStr + "," + indexVoltStr);

  delay(1);

  if (bluetooth.available()) {
    sensorValue = bluetooth.read();                               // Read in Bluetooth
    // outputValue = map(sensorValue, 0, 1023, 0, 255);              // Map read values to 255
    analogWrite(analogOutPin, sensorValue);                       // Write the mapped value to the out pin 9
    Serial.println(sensorValue);
  }
  // display the string on the serial monitor

  // Serial.println(thumbVoltStr);
  // Serial.println(indexVoltStr);

  // small delay between data transmissions

  delay(1);

}
