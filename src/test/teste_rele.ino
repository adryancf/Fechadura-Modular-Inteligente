#include <Adafruit_Sensor.h>
#include <DHT.h>

int DHTPIN   =  4; 
int rele = 18;                                

#define DHTTYPE DHT22      


// Define Variáveis do DHT
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(rele, OUTPUT);
  
}

void loop() {


  float humidity =    dht.readHumidity();
  float temperature = dht.readTemperature();

      
      Serial.print("Temp.");  
      Serial.print(temperature);
      Serial.print("°");
      Serial.println("C");

      Serial.print("Umid.");
      Serial.print(humidity);
      Serial.println("%");
      Serial.println("====================");

     
      digitalWrite(rele, HIGH);
      delay(1000);
      digitalWrite(rele, LOW);
      delay(1000);


    
}
