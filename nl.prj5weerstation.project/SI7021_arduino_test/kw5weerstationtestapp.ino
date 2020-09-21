#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>

Weather sensor;

float humidity = 0;
float tempf = 0;

int weatherDelay = 1000000;
int dt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SDA, OUTPUT);
  pinMode(SCL,INPUT);

  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, LOW);

  sensor.begin();  
}

void loop() {
  // put your main code here, to run repeatedly:
  dt = millis();
  weatherDelay -= dt;
  if(weatherDelay <= 0) {
    getWeather();
    printInfo();
    weatherDelay = 1000000;
  }
  delay(1);
}

void getWeather()
{
  // Measure Relative Humidity from the HTU21D or Si7021
  humidity = sensor.getRH();

  // Measure Temperature from the HTU21D or Si7021
  tempf = sensor.getTemp();
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement with getTemp() instead with readTemp()
}
//---------------------------------------------------------------
void printInfo()
{
//This function prints the weather data out to the default Serial Port

  Serial.print("Temp:");
  Serial.print(tempf);
  Serial.print("C, ");

  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.println("%");
}
