#include "max6675.h"
#include <dht.h>
dht DHT;
#define DHT11_PIN 7

int soPin = 4;
int csPin = 5;
int sckPin = 6;

int pinOut = 3;

MAX6675 Module(sckPin, csPin, soPin);

void setup() {
// put your setup code here, to run once:
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(3,OUTPUT);

}

void loop() {
// put your main code here, to run repeatedly:

int chk = DHT.read11(DHT11_PIN);

double temp = DHT.temperature;
double humid = DHT.humidity;

Serial.print("Temperature From DHT: ");
Serial.println(temp);
Serial.print("Humidity: ");
Serial.println(humid);

float temp_from_Therm = Module.readCelsius();
Serial.print("Temperature From Thermocouple: ");
Serial.println(temp_from_Therm);

Serial3.print("Temperature:");
Serial3.println(temp);
Serial3.print("Humidity:");
Serial3.println(humid);

if (temp_from_Therm > 35){
  digitalWrite(pinOut, LOW)
} else {
  digitalWrite(pinOut, HIGH);
}

delay(2000);

//if (Serial3.available()){
//    Serial.println("Reading from bluetooth");
//    char inByte = 0;
//    inByte = (char)Serial.read();
//    Serial.print((char)inByte);
//}
//
//if (Serial.available()){
//    Serial.println("Writing to bluetooth");
//    Serial3.write(Serial.read());
//} 

}
