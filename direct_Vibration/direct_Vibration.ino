#include<SoftwareSerial.h>

const int analogInPin = A0;  // Analog input pin that the sensor is attached to
const int analogOutPin = 9; // Analog output pin that the Haptic Motor Driver is attached to

int bluetoothTx = 2;  // Set Bluetooth Transmission to DIO pin 2
int bluetoothRx = 3;  // Set Bluetooth Receiving to DIO pin 3

int sensorValue = 0;        // value read from the sensor
double outputValue = 0;        // value output to the PWM (analog out)


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
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  analogWrite(analogOutPin, analogRead(A0));
  

}
