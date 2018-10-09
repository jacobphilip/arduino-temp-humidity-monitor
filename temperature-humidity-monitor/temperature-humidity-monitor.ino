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
  float celsius, humidity, fahrenheit;
  
  //input
  int chk = DHT.read11(DHT11_PIN);

  celsius = DHT.temperature;
  humidity = DHT.humidity;

  //process
  fahrenheit = ((celsius * 9)/5) + 32;

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
  delay(2000);
}
