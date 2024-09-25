#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C address and size
dht DHT;

#define DHT11_PIN 8 // Digital pin connected to DHT11
#define DHTTYPE DHT11 // DHT 11

Servo myservo;
int cangle = 180;
int angle = cangle;

void setup() {
  lcd.begin(); 
  lcd.setCursor(0, 0);
  lcd.print((char)223); lcd.print((char)223); 
  lcd.print("Rain Shield");
  lcd.print((char)223); lcd.print((char)223);
  delay(3000);
  
  myservo.attach(9); 
  myservo.write(cangle);
}

void loop() {
  int d = DHT.read11(DHT11_PIN); // Reading from DHT11 sensor
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");

  float temp = DHT.temperature;
  float humi = DHT.humidity;

  // If temperature is high and humidity is low, deactivate rain shield
  if (temp > 35 && cangle != 180 && humi < 76) {
    for (int angle = cangle; angle <= 180; angle++) {
      myservo.write(angle);
      delay(15);
    }
    lcd.setCursor(0, 0);
    lcd.print("Rain Shield ");
    lcd.setCursor(0, 1);
    lcd.print("Deactivated ");
    cangle = 180;
    delay(2000);
  } 
  // If temperature is lower and humidity is high, activate rain shield
  else if (temp <= 35 && cangle != 0 && humi >= 76) {
    for (int angle = cangle; angle >= 0; angle--) {
      myservo.write(angle);
      delay(15);
    }
    lcd.setCursor(0, 0);
    lcd.print("Rain Shield ");
    lcd.setCursor(0, 1);
    lcd.print("Activated ");
    cangle = 0;
    delay(2000);
  }
  
  delay(500);
}
