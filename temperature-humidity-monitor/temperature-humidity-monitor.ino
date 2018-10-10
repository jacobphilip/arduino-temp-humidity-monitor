#include "DHT.h"

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  delay(5000);
  
  float celsius, humidity, fahrenheit, heatIndexF, heatIndexC, dewpointF;
 
  //input
  celsius = dht.readTemperature();
  fahrenheit = dht.readTemperature(true);
  humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(celsius) || isnan(fahrenheit)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  heatIndexF = dht.computeHeatIndex(fahrenheit, humidity);
  // Compute heat index in Celsius (isFahreheit = false)
  heatIndexC = dht.computeHeatIndex(celsius, humidity, false);

  //process
  
  //dewpoint formula from http://andrew.rsmas.miami.edu/bmcnoldy/Humidity.html
  dewpointF = (((243.04*(log(humidity/100)+((17.625*celsius)/(243.04+celsius)))/(17.625-log(humidity/100)-((17.625*celsius)/(243.04+celsius)))) * 9)/5) + 32;
  
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

  //serial first
  Serial.print("Temperature = ");
  Serial.println(fahrenheit);
  Serial.print("Relative Humidity = ");
  Serial.println(humidity);
  Serial.print("Heat Index = ");
  Serial.println(heatIndexF);
  Serial.print("Dew Point = ");
  Serial.println(dewpointF);

  //lcd frame 1
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(fahrenheit);
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  delay(5000);

  //lcd frame 2
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Feels: ");
  lcd.print(heatIndexF);
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print("Dew Pt: ");
  lcd.print(dewpointF);
  lcd.print("F");
  

