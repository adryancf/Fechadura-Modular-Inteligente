

#include <IOXhop_FirebaseESP32.h>
#include <Ticker.h>
#include <DHT.h>

// Set these to run example.
#define FIREBASE_HOST "https://horta-auto-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ksFwAONJ6OfquLBJzQ5dilNfosfF0PX3CbzJIOlE"
#define WIFI_SSID "CASA"
#define WIFI_PASSWORD "dri12445"

//Declaração dos pinos
#define DHT_PIN 4
#define DHTTYPE DHT22
#define SOLO_PIN 15


//Declaração de variáveis necessárias  do sensor capacitivo
byte UmidPercent = 0, umidade = 0, ValorAnterior = 0; 
int ValorAnalog = 0;

float humidity;     float humidity_atual;
float temperature;  float temperature_atual;


// Publique a cada 5 min
#define PUBLISH_INTERVAL 5000

DHT dht(DHT_PIN, DHTTYPE);
Ticker ticker;
bool publishNewState = true;

void publish(){
  publishNewState = true;
}

void setupPins(){

  dht.begin();  // Iniciaçização do Sensor DHT22
  
}

// Conexão com a rede Wi-Fi
void setupWifi(){
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    
  }
  
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
}

// Conexão com a Base de dados (Firebase)
void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}


void setup() {
  Serial.begin(9600);

  setupPins();
  setupWifi();    

  setupFirebase();

  // Registra o ticker para publicar de tempos em tempos
  ticker.attach_ms(PUBLISH_INTERVAL, publish);

  ValorAnterior = analogRead(SOLO_PIN); 
}


//Leitura do sensor capacitivo
void readSolo(){

  ValorAnalog = analogRead(SOLO_PIN); //Leitura do Valor Analógico do Sensor

  UmidPercent = map(ValorAnalog, 297, 614, 0, 100);          //Mapeando o valor entre 0 e 100
  umidade = 100 - UmidPercent;                              // Invertendo os valores para melhor compreensão
  
  if ( (umidade > (ValorAnterior) + 1) || (umidade < (ValorAnterior) - 1)){ // Evita leitura repetida 
      Serial.print(umidade);
      Serial.println("% de umidade");
      Serial.println("====================");
   
}
}
void loop(){

  // Apenas publique quando passar o tempo determinado
  if(publishNewState){
    Serial.println("Publish new State");

    // Obtem os dados do sensor DHT 
     humidity = dht.readHumidity();
     temperature = dht.readTemperature();
    
    //Imprime os valores no monitor serial
    Serial.println("Temp. ");
    Serial.println(temperature);
    Serial.println("Humidade. ");
    Serial.println(humidity);

    readSolo(); 
    
      if(!isnan(humidity) && !isnan(temperature)){


        // Manda para o firebase o DHT22
        Firebase.pushFloat("temperature", temperature);
        Firebase.pushFloat("humidity", humidity);    
        Firebase.pushFloat("Umidade do Solo", umidade);
        
        publishNewState = false;
    }

        
          
    else{
    Serial.println("Erro no envio!");
    }
 
  }
  delay(500);
}
