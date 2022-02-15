#include "max6675.h"
#include <dht.h>

dht DHT;

#define DHT11_PIN 7

int soPin = 4;
int csPin = 5;
int sckPin = 6;

MAX6675 Module(sckPin, csPin, soPin);

void setup() {
// put your setup code here, to run once:
    Serial.begin(9600);
    Serial3.begin(9600);
}

void loop() {
// put your main code here, to run repeatedly:

//  int chk = DHT.read11(DHT11_PIN);

//  Serial.print("Temperature From DHT: ");
//  Serial.println(DHT.temperature);
//  Serial.print("Humidity: ");
//  Serial.println(DHT.humidity);
  if (Serial3.available()){
      Serial.println("Reading from bluetooth");
      Serial.write(Serial3.read());
  }
//
//  if (Serial.available()){
//    Serial.println("Writing to bluetooth");
//    Serial3.write(Serial.read());
//  }  
  float temp = Module.readCelsius();
  Serial.print("Temperature From Thermocouple: ");
  Serial.println(temp);
  Serial3.print(temp);

  Serial.println();
  delay(2000);


}
