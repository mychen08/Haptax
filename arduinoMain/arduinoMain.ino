// Currently copied from lab. Needs to be modded for project


// Use the library Softwareserial to use pins 2 and 3 of the arduino for serial comunication with the bluetooth unit
// pins 0 and 1 are not use to be able to lead the program and read the program output on the Arduino serial monitor

#include<SoftwareSerial.h>

int bluetoothTx = 2;
int bluetoothRx = 3;

// to display the potentiometer voltage converted into a string of charcters

String Number_in_string;

// to store pot voltage as the output of the A/D conversion and as a voltage between 0 and 5 V

int pot = 0;
float pot_voltage = 0.0;

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


  // read the pot voltage from pin A0 and convert into a voltage
  pot = analogRead(A0);
  pot_voltage = float(pot)*5.0/1023.0;

  // convert the pot voltage into a string

  Number_in_string = String(pot_voltage);

  // transmit the string to the bluetooth unit

  bluetooth.println(Number_in_string);

  // display the string on the serial monitor

  Serial.println(Number_in_string);

  // small delay between data transmissions

  delay(20);

}
