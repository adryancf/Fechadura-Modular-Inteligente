/* https://www.usinainfo.com.br/blog/projeto-sensor-de-umidade-do-solo-arduino-com-alerta-por-sms/ -----> base do código */

#define sensor 15

byte UmidPercent = 0, umidade = 0, 
int ValorAnalog = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Inicializando Sistema...");
  delay(500);
  
  pinMode(sensor, INPUT); //Configura o Pino do Sensor como Entrada

  ValorAnterior = analogRead(sensor); 
}
   
void loop()
{
  
  ValorAnalog = analogRead(sensor); //Leitura do Valor Analógico do Sensor

  UmidPercent = map(ValorAnalog, 297, 614, 0, 100);          //Mapeando o valor entre 0 e 100
  umidade = 100 - UmidPercent;                              // Invertendo os valores para melhor compreensão

    /*if ( (umidade > (ValorAnterior) + 1) || (umidade < (ValorAnterior) - 1)) */  // Essa Linha so serve caso eu não queira que o ESP leia repetidamente. 

    if (umidade < 60)
    {
      Serial.print("O sensor esta com:");
      Serial.print(umidade);
      Serial.println("% de umidade")
      Serial.println("====================");
      Serial.print("Baixa umidade");
      Serial.println("====================");
    }

    else if (umidade >= 60)
    {
      Serial.print("O sensor esta com:");
      Serial.print(umidade);
      Serial.println("% de umidade")
      Serial.println("====================");
      Serial.print("Umidade Normal");
      Serial.println("====================");
      
    }

  //ValorAnterior = umidade;
  delay(500);

}

  
