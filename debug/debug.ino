//#include<SoftwareSerial.h>
//
//int bluetoothTx = 2;
//int bluetoothRx = 3;
//const int port = A0;
//String strTest = "hello world";
//
//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
//
//void setup() {
//  // put your setup code here, to run once:
//  bluetooth.begin(115200);
//  bluetooth.print("$$$");
//  delay(100);
//  bluetooth.println("U,9600,N");
//  bluetooth.begin(9600);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  bluetooth.println(analogRead(port));
//  Serial.println(analogRead(port));
//  delay(100);
//
////  Serial.println(strTest);
////  bluetooth.println(strTest);
//
//}

// Control the vibration of an ERM motor
// using PWM and a photoresistor. 

#include <Sparkfun_DRV2605L.h>
#include <Wire.h>

SFE_HMD_DRV2605L HMD;
const int analogInPin = A0;  // Analog input pin that the sensor is attached to
const int analogOutPin = 9; // Analog output pin that the Haptic Motor Driver is attached to

int sensorValue = 0;        // value read from the sensor
int outputValue = 0;        // value output to the PWM (analog out)


void setup() 
{
  HMD.begin();
  Serial.begin(9600);
  HMD.Mode(0x03); //PWM INPUT 
  HMD.MotorSelect(0x0A);
  HMD.Library(7); //change to 6 for LRA motors 

}
void loop() 
{

// // read the analog in value:
//  sensorValue = analogRead(analogInPin);
//  // map it to the range of the analog out:
//  outputValue = map(sensorValue, 0, 1023, 0, 255);
//  // change the analog out value:
//  analogWrite(analogOutPin, outputValue);

  analogWrite(9, HIGH);

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);
 }

