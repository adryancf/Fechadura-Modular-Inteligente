

#include <IOXhop_FirebaseESP32.h>
#include <Ticker.h>
#include <DHT.h>

// WiFi
#define FIREBASE_HOST "https://horta-auto-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ksFwAONJ6OfquLBJzQ5dilNfosfF0PX3CbzJIOlE"
#define WIFI_SSID "POCOM3"
#define WIFI_PASSWORD "acf454545"



#define DHT_PIN 13
#define DHTTYPE DHT22
#define LAMP_PIN 18
#define SOLO 4
// Publique a cada 5 min
#define PUBLISH_INTERVAL 1000

int ValorAnalog = 0;
int umidade = 0;

DHT dht(DHT_PIN, DHTTYPE);
float humidity;     float humidity_atual;
float temperature;  float temperature_atual;

Ticker ticker;

bool publishNewState = true;


void publish(){
  publishNewState = true;
}

void setupPins(){

  pinMode(LAMP_PIN, OUTPUT);
  pinMode (SOLO, INPUT);
  
  digitalWrite(LAMP_PIN, LOW);

  dht.begin();  
}

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

void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setBool("lamp", false);
  //Firebase.setBool("presence", false);
}

void setup() {
  Serial.begin(9600);

  setupPins();
  setupWifi();    

  setupFirebase();

  // Registra o ticker para publicar de tempos em tempos
  ticker.attach_ms(PUBLISH_INTERVAL, publish);
}

void loop() {

  // Apenas publique quando passar o tempo determinado
  if(publishNewState){

    readSensor();
    //readSolo ();
    }

    //bool lampValue = Firebase.getBool("lamp");
    //digitalWrite(LAMP_PIN, lampValue ? HIGH : LOW);

    delay(500);
}

void readSensor(){

      
      humidity =    dht.readHumidity();
      temperature = dht.readTemperature();

        if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Falha ao ler DHT!!");
        }
            else if (humidity_atual != humidity || temperature_atual != temperature) {
            humidity_atual = humidity;  temperature_atual = temperature;
      
            Firebase.pushFloat("temperature", temperature);
            Firebase.pushFloat("humidity", humidity);    
            publishNewState = false;
            
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

void readSolo(){

  ValorAnalog = analogRead(SOLO); //Leitura do Valor Analógico do Sensor

  umidade = map(ValorAnalog, 4095, 2300, 0, 100);      //Mapeando o valor entre 0 e 100
     
        Firebase.pushFloat("umidade", umidade);    
        publishNewState = false;
            
              Serial.print ("A umidade do sensor é:");
              Serial.print(umidade);
              Serial.println (" %");
              Serial.print ("Valor da leitura:");
              Serial.println (ValorAnalog);
}



 
  
