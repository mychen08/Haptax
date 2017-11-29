#include<SoftwareSerial.h>
int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

const int analogOutPin = 9; // Analog output pin that the Haptic Motor Driver is attached to
int incomingByte = 0;  // for incoming serial data

// store voltages from thumb and index pressure sensors

int pressureThumb = 0;
float pressureThumbVolt = 0.0;

int pressureIndex = 0;
float pressureIndexVolt = 0.0;

// Declare string
String thumbVoltStr;
String indexVoltStr;


void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

// Setup Bluetooth serial connection by programming the unit to communicate at 9600 bauds  
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
}

void loop() {

  for (int i = 0; i < 30; i += 1) {
  
    pressureThumb = analogRead(A0);
    pressureThumbVolt = float(pressureThumb)*5.0/1023.0;
    thumbVoltStr = String(pressureThumbVolt);
  
    pressureIndex = analogRead(A1);
    pressureIndexVolt = float(pressureIndex)*5.0/1023.0;
    indexVoltStr = String(pressureIndexVolt);
  
    // transmit the string to the bluetooth unit
  
    bluetooth.println(thumbVoltStr + "," + indexVoltStr);
    
  }
  // send data only when you receive data:
  if (bluetooth.available() > 0) {
    // read the incoming byte:
    incomingByte = bluetooth.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);

    analogWrite(analogOutPin, incomingByte); 
  }
}

