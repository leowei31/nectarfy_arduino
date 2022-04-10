#include "max6675.h"
#include <dht.h>
dht DHT;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1); //RX, TX

// initialize pins 
#define DHT11_PIN 13

int soPin1 = 4;
int csPin1 = 5;
int sckPin1 = 6;

int soPin2 = 7; 
int csPin2 = 8;
int sckPin2 = 9;

int soPin3 = 10;
int csPin3 = 11;
int sckPin3 = 12;

int pinOut = 3;

float median_temp;
int count_nan;

float temp_from_Therm1;
float temp_from_Therm2;
float temp_from_Therm3;

MAX6675 Module1(sckPin1, csPin1, soPin1);

MAX6675 Module2(sckPin2, csPin2, soPin2);

MAX6675 Module3(sckPin3, csPin3, soPin3);


void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(3,OUTPUT);
    mySerial.begin(9600);
}

void loop() {
// read from DHT sensor
DHT.read11(DHT11_PIN);

double temp = DHT.temperature;
double humid = DHT.humidity;


// printing the temperature and the humidity to the serial monitor
//Serial.print("Temperature From DHT: ");
//Serial.println(temp);
//Serial.print("Humidity: ");
//Serial.println(humid);


count_nan = 0;
// read temperature from thermocouple and print it to serial monitor
temp_from_Therm1 = Module1.readCelsius();
//Serial.print("Temperature From Thermocouple #1: ");
//Serial.println(temp_from_Therm1);
if (isnan(temp_from_Therm1)){
  temp_from_Therm1 = 100;
  count_nan = count_nan + 1;
}


temp_from_Therm2 = Module2.readCelsius();
//Serial.print("Temperature From Thermocouple #2: ");
//Serial.println(temp_from_Therm2);
if (isnan(temp_from_Therm2)){
  temp_from_Therm2 = 100;
  count_nan = count_nan + 1;
}


temp_from_Therm3 = Module3.readCelsius();
//Serial.print("Temperature From Thermocouple #3: ");
//Serial.println(temp_from_Therm3);
if (isnan(temp_from_Therm3)){
  temp_from_Therm3 = 100;
  count_nan = count_nan + 1;
}

// sorting the three different temperature from the thermocouples and setting the median_temp to the median of the three values
if (temp_from_Therm1 >= temp_from_Therm2 && temp_from_Therm1 <= temp_from_Therm3){
  median_temp = temp_from_Therm1;
}else if(temp_from_Therm1 >= temp_from_Therm3 && temp_from_Therm1 <= temp_from_Therm2){
  median_temp = temp_from_Therm1;
}else if (temp_from_Therm2 >= temp_from_Therm1 && temp_from_Therm2 <= temp_from_Therm3){
  median_temp = temp_from_Therm2;
}else if (temp_from_Therm2 >= temp_from_Therm3 && temp_from_Therm2 <= temp_from_Therm1){
  median_temp = temp_from_Therm2;
}else {
  median_temp = temp_from_Therm3;
}

if (count_nan >= 2){
  median_temp = min(min(temp_from_Therm1, temp_from_Therm2), temp_from_Therm3);
}
// sending the median temperature and the humidity measured via bluetooth to the user's mobile app
//
//Serial.print("Median");
//Serial.print(median_temp);
//mySerial.print("T:");
//mySerial.println(median_temp);
//mySerial.print("H:");
//mySerial.println(humid);

Serial.print("T:");
Serial.println(median_temp);
Serial.print("H:");
Serial.println(humid);

if (temp_from_Therm2 > 30){
  digitalWrite(pinOut, LOW);
}

if (temp_from_Therm2 < 25){
  digitalWrite(pinOut, HIGH);
}

// send a low signal if the temperature is above 30, turning off the heater, and send a high signal if the temperature is below 25, turning on the heater
if (median_temp > 30){
  digitalWrite(pinOut, LOW);
}else if (median_temp < 25){
  digitalWrite(pinOut, HIGH);
}

delay(2000);

}
