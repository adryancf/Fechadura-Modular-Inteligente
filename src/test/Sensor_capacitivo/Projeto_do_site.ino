
#define sensor A0

bool BaixaUmid = 0, AltaUmid = 0;

byte UmidPercent = 0, umidade = 0, ValorAnterior = 0;

int ValorAnalog = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Inicializando Sistema...");
  delay(1000);
 
  pinMode(sensor, INPUT); //Configura o Pino do Sensor como Entrada

  ValorAnterior = analogRead(sensor); //Captura um primeiro valor de referencia inicial para a variavel ValorAnterior
}

void loop()
{
  //Le o valor do pino A0 do sensor
  ValorAnalog = analogRead(sensor); //Leitura do Valor Analógico do Sensor

  UmidPercent = map(ValorAnalog, 0, 1023, 0, 100); //Mapeando o valor entre 0 e 100
  umidade = 100 - UmidPercent;

  if ( (umidade > (ValorAnterior) + 1) || (umidade < (ValorAnterior) - 1))
  {

    if (umidade < 60 && BaixaUmid == 0)
    {
      BaixaUmid = 1;
      AltaUmid = 0;
      MensUmidBaixa();
    }

    if (umidade >= 60 && AltaUmid == 0)
    {
      MensUmidNormal();
      AltaUmid = 1;
      BaixaUmid = 0;
    }

    ValorAnterior = umidade;
  }

}

void MensUmidBaixa() //Funcao para enviar mensagem de alerta Umidade Baixa
{
  Serial.println("Umidade Baixa");
  Serial.print("Valor:");
  Serial.println(umidade);
  Serial.println("====================");
  delay(1000);
  
}

void MensUmidNormal()//Funcao para enviar mensagem de alerta Umidade Normal
{
  Serial.println("Umidade Normal");
  Serial.print("Valor:");
  Serial.println(umidade);
  Serial.println("====================");
  delay(1000);
}
