#include <Adafruit_Sensor.h>
#include "DHT.h"

const int DHTPIN   =  4;                                 

#define DHTTYPE DHT22      


// Define Variáveis do DHT
DHT dht(DHTPIN, DHTTYPE);
float humidity;     float humidity_atual;
float temperature;  float temperature_atual;

void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {


  humidity =    dht.readHumidity();
  temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler DHT!!");
  }
  else if (humidity_atual != humidity || temperature_atual != temperature) {
      humidity_atual = humidity;  temperature_atual = temperature;
      Serial.print("Temp.");  
      Serial.print(temperature);
      Serial.print("°");
      Serial.println("C");

      Serial.print("Umid.");
      Serial.print(humidity);
      Serial.println("%");
      Serial.println("====================");
    }
    
}
