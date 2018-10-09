#include <dht.h>
#include <LiquidCrystal.h>
//TODO include relay library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht DHT;

//TODO define relay(s)

#define DHT11_PIN 7

//TODO define relay pin(s)

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  //TODO setup relays
}

/*
Relative Humidity: 90%.
Substrate Temperature: 84°F - 86°F. Thermal death limits have been established at 106°F.
Duration: 10-14 days.
CO2: 5000 - 10,000 ppm.
Fresh Air Exchanges: 0 per hour.
*/
void loop()
{
  float celsius, humidity, fahrenheit;

  float relativeHumidityTarget = 90;
  float temperatureLowerLimit = 84;
  float temperatureUpperLimit = 86;

  //input
  int chk = DHT.read11(DHT11_PIN);

  celsius = DHT.temperature;
  humidity = DHT.humidity;

  //process
  fahrenheit = ((celsius * 9)/5) + 32;

  if (fahrenheit < temperatureLowerLimit) {
    //TODO turn on heater
  } else if (fahrenheit > temperatureUpperLimit) {
    //TODO turn off heater
  }

  if (humidity < relativeHumidityTarget) {
    //TODO turn on humidifier
  } else if (humidity > relativeHumidityTarget) {
    //TODO turn off humidifier
  }

  //output
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(fahrenheit);
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  Serial.print("Temperature = ");
  Serial.print(fahrenheit);
  Serial.println("F");
  Serial.print("Relative Humidity = ");
  Serial.println(humidity);
  // pause 60 seconds
  delay(60000);
}
