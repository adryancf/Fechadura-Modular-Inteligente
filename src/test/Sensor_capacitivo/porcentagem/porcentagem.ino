#define sensor 4


void setup()
{
  Serial.begin(9600);
  Serial.println("Inicializando Sistema...");
  delay(500);
  
  pinMode(sensor, INPUT); //Configura o Pino do Sensor como Entrada

}
   
void loop()
{
  
  int umidade = analogRead(sensor); //Leitura do Valor Analógico do Sensor

    if (umidade >= 3200 && umidade <= 4095){
      Serial.print("O sensor esta com:");
      Serial.println(umidade);
      //Serial.println("% de umidade");
      Serial.println("====================");
      Serial.println("Pouca Água");
      Serial.println("====================");
    }

    else if (umidade <= 3199 && ){
      Serial.print("O sensor esta com:");
      Serial.println(umidade);
      //Serial.println("% de umidade");
      Serial.println("====================");
      Serial.println("Umidade Normal");
      Serial.println("====================");
      
    }

    else if (umidade <= 2700){
      Serial.print("O sensor esta com:");
      Serial.println(umidade);
      //Serial.println("% de umidade");
      Serial.println("====================");
      Serial.println("Muita água");
      Serial.println("====================");
      
    }

    else{

      Serial.println(umidade);
    }


  //ValorAnterior = umidade;
  delay(500);

}
