#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient MQTT(espClient);

#define DHTPIN 4    //Porta do sensor DHT
#define DHTTYPE DHT11   //Modelo do sensor DHT (DHT11, DHT21 ou DHT22)
#define LDRPIN 34   //Porta do sensor de luminosidade

DHT dht(DHTPIN, DHTTYPE);

const int delay = 2000;    //Intervalo de amostragem. Valores abaixo de 2000ms não são recomendados

const char* ssid = "";   //SSID da rede wifi
const char* wifiPassword =  "";   //Senha da rede wifi

const char* clientID = "";    //ID do dispositivo no Thingsboard
const char* token = "";    //Token ou nome de usuário do dispositivo no Thingsboard
const char* mqttPassword = "";   //Senha do dispositivo    //Senha do dispositivo no Thingsboard (opcional)

const char* address = "localhost";    //Endereço da máquina hospedeira do servidor do Thingsboard
const int port = 1883;    //Porta dedicada para o servidor do Thingsboard

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando à rede WiFi..");
  }
  Serial.println("Conectado!");
  
  MQTT.setServer(address, port);
  MQTT.connect(clientID, token, mqttPassword);

  dht.begin();

  pinMode(LDRPIN, INPUT);
}

void loop() {
  delay(delay);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int l = analogRead(LDRPIN);
  l = map(l, 0, 4095, 0, 100);  //Converte o valor de luminosidade para uma porcentagem 

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha ao ler o sensor DHT"));
    return;
  }
  
  String jsonString = "[{\"Temperatura\":" + String(t) + "}, {\"Humidade\":" + String(h) + "}, {\"Luminosidade\":" + String(l) + "}]";
  
  char jsonChar[jsonString.length()];
  jsonString.toCharArray(jsonChar, jsonString.length()+1);    
  
  MQTT.publish("v1/devices/me/telemetry", jsonChar);
  Serial.print(jsonChar);
  Serial.print("\n");
}
