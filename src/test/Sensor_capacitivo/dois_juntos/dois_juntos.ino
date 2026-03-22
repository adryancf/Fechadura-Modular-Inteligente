#include <DHT.h>

#define sensor 4
#define DHT_PIN 13
#define DHTTYPE DHT22

int umidade = 0;
int ValorAnalog = 0;

DHT dht(DHT_PIN, DHTTYPE);

float humidity, temperature; 
 

void setup()
{
  Serial.begin(9600);
  Serial.println("Inicializando Sistema...");
  delay(500);
  
  pinMode(sensor, INPUT); //Configura o Pino do Sensor como Entrada

  //ValorAnterior = analogRead(sensor); 
}
   
void loop()
{
  
  ValorAnalog = analogRead(sensor); //Leitura do Valor Analógico do Sensor

  umidade = map(ValorAnalog, 4095, 2300, 0, 100);          //Mapeando o valor entre 0 e 100
  //umidade = 100 - UmidPercent;                              // Invertendo os valores para melhor compreensão

  Serial.print ("A umidade do sensor é:");
  Serial.println(umidade);
  Serial.print ("Valor da leitura:");
  Serial.println (ValorAnalog);

  delay(500); 
  
      humidity =    dht.readHumidity();
      temperature = dht.readTemperature();
          
                Serial.print("Temp.");  
                Serial.print(temperature);
                Serial.print("°");
                Serial.println("C");
          
                Serial.print("Umid.");
                Serial.print(humidity);
                Serial.println("%");
                Serial.println("====================");
         
  delay(500);
  

    /*if ( (umidade > (ValorAnterior) + 1) || (umidade < (ValorAnterior) - 1)) */  // Essa Linha so serve caso eu não queira que o ESP leia repetidamente. 

    /*if (umidade < 40)
    {
      Serial.print("O sensor esta com:");
      Serial.print(umidade);
      Serial.println("% de umidade");
      Serial.println("====================");
      Serial.println("Pouca Água");
      Serial.println("====================");
    }

    else if (umidade >= 60)
    {
      Serial.print("O sensor esta com:");
      Serial.print(umidade);
      Serial.println("% de umidade");
      Serial.println("====================");
      Serial.println("Umidade Normal");
      Serial.println("====================");
      
    }

    else if (umidade >= 75)
    {
      Serial.print("O sensor esta com:");
      Serial.print(umidade);
      Serial.println("% de umidade");
      Serial.println("====================");
      Serial.println("Muita água");
      Serial.println("====================");
      
    }

  */
  //ValorAnterior = umidade;
  delay(500);

}
