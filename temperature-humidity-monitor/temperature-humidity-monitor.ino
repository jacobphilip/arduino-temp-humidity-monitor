#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht DHT;

#define DHT11_PIN 7

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
  float celsius, humidity, fahrenheit, dewpoint;

  //input
  int chk = DHT.read11(DHT11_PIN);

  celsius = DHT.temperature;
  humidity = DHT.humidity;

  //process
  fahrenheit = ((celsius * 9)/5) + 32;
  
  //dewpoint formula from http://andrew.rsmas.miami.edu/bmcnoldy/Humidity.html
  dewpoint = (((243.04*(log(humidity/100)+((17.625*celsius)/(243.04+celsius)))/(17.625-log(humidity/100)-((17.625*celsius)/(243.04+celsius)))) * 9)/5) + 32;

  //TODO
  // if dewpoint >= 30 and air temperature <= 32 then start irrigation
  // 29 , 33
  // 27 , 34
  // 25 , 35
  // 24 , 37
  // 22 , 38
  // 20 , 39
  // 17 , 40

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
  Serial.print("Dewpoint = ");
  Serial.println(dewpoint);
  delay(2000);
}
