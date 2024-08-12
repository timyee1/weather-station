#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal_I2C.h>

#include <NRF24L01_W.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

const int CS = 7;
const int CSN = 8;
LiquidCrystal_I2C lcd(0x27, 16, 2);
NRF24L01_W radio(CS, CSN);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  // pinMode(CS, INPUT);
  // pinMode(CSN, INPUT);

  radio.begin();
  radio.setReceiveAddress("UCI23");
  radio.setTransmitAddress("UCI27");
  radio.setChannel(120);

}

void loop() {
  lcd.clear();

  digitalWrite(CSN, LOW);

  Serial.println(radio.available());
  if (radio.available() > 0) {
    WeatherReport incomingReport = radio.read();

    //temp reading
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(incomingReport.temperature);
    lcd.print("C");

    //humidity reading
    lcd.setCursor(0,1);
    lcd.print("Hum: ");
    lcd.print(incomingReport.humidity);
    lcd.print("%, ");

    //day or night
    if (incomingReport.light >= 50) {
      lcd.print("Day");
    }
    else {
      lcd.print("Night");
    }
  }

  delay(1000);

}
