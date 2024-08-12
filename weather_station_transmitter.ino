#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal_I2C.h>

#include <NRF24L01_W.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

const int TH_SENSOR = 4;
const int LIGHT_SENSOR = A2;
const int CS = 7;
const int CSN = 8;
NRF24L01_W radio(CS, CSN);
DHT weatherSensor(TH_SENSOR, DHT11);

void setup() {
  Serial.begin(9600);

  pinMode(TH_SENSOR, INPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  // pinMode(CS, OUTPUT);
  // pinMode(CSN, OUTPUT);
  weatherSensor.begin();
  
  radio.begin();
  radio.setReceiveAddress("UCI27");
  radio.setTransmitAddress("UCI23");
  radio.setChannel(120);

}

void loop() {
  digitalWrite(CSN, LOW);

  int light = analogRead(LIGHT_SENSOR);
  int humidity = round(weatherSensor.readHumidity());
  int temperature = round(weatherSensor.readTemperature());

  WeatherReport report;
  report.temperature = temperature;
  report.humidity = humidity;
  report.light = light;
  Serial.println(radio.write(report));

  delay(1000);

}
