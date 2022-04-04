#include "max6675.h"
#include <dht.h>
dht DHT;
#define DHT11_PIN 13
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0,1); //RX, TX

int soPin = 4;
int csPin = 5;
int sckPin = 6;

int soPin2 = 7; 
int csPin2 = 8;
int sckPin2 = 9;

int soPin3 = 10;
int csPin3 = 11;
int sckPin3 = 12;

int pinOut = 3;

MAX6675 Module(sckPin, csPin, soPin);

MAX6675 Module2(sckPin2, csPin2, soPin2);

MAX6675 Module3(sckPin3, csPin3, soPin3);

void setup() {
// put your setup code here, to run once:
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(3,OUTPUT);
//    mySerial.begin(19200);

}

void loop() {
// put your main code here, to run repeatedly:

//Serial3.print(9);
DHT.read11(DHT11_PIN);

double temp = DHT.temperature;
double humid = DHT.humidity;

Serial.print("Temperature From DHT: ");
Serial.println(temp);
Serial.print("Humidity: ");
Serial.println(humid);

float temp_from_Therm = Module.readCelsius();
Serial.print("Temperature From Thermocouple #1: ");
Serial.println(temp_from_Therm);

float temp_from_Therm2 = Module2.readCelsius();
Serial.print("Temperature From Thermocouple #2: ");
Serial.println(temp_from_Therm2);

float temp_from_Therm3 = Module3.readCelsius();
Serial.print("Temperature From Thermocouple #3: ");
Serial.println(temp_from_Therm3);


Serial3.print("T:");
Serial3.println(temp_from_Therm);
Serial3.print("H:");
Serial3.println(humid);

if (temp_from_Therm2 > 30){
  digitalWrite(pinOut, LOW);
}

if (temp_from_Therm2 < 25){
  digitalWrite(pinOut, HIGH);
}

delay(2000);
//Serial3.print("123");

//if (Serial3.available()){
//    Serial.println("Reading from bluetooth");
//    Serial.write(Serial.read());
//}

//if (Serial3.available()){
//    Serial.println("Reading from bluetooth");
//    Serial.write(Serial.read());
//}
//
//if (Serial.available()){
//    Serial.println("Writing to bluetooth");
//    Serial3.write(Serial.read());
//} 


}
