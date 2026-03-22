
const int sensor = 4;


void setup()
{
  Serial.begin(9600);
  Serial.println("Inicializando Sistema...");
  delay(500);
 
  pinMode(sensor, INPUT); //Configura o Pino do Sensor como Entrada

}

void loop()
{
  
  int Umidade = analogRead(sensor); //Leitura do Valor Analógico do Sensor

  Serial.print("Valor:");
  Serial.println(Umidade);
  Serial.println("====================");

  delay(500);

}
