#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h> 

#define TRIGGER_PIN 13
#define ECHO_PIN 14
#define MAX_DISTANCE 200

#define SOIL_MOISTURE_PIN 34
#define RAIN_POT_PIN 32

#define LED_PIN 22

#define LIMIAR_NIVEL_AGUA_ALTA 180
#define LIMIAR_UMIDADE_SOLO_SATURADO 2500
#define LIMIAR_CHUVA_FORTE 2000

const char* ssid = "Wokwi-GUEST"; 
const char* password = ""; 

const char* mqtt_broker = "broker.hivemq.com"; 
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32_FloodMonitor"; 
const char* mqtt_topic_publish = "sensor/monitoramento_enchente"; 

WiFiClient espClient;
PubSubClient client(espClient);

// Medir Distancia
long measureDistanceCm() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distanceCm = duration / 58;

  if (distanceCm == 0 || distanceCm > MAX_DISTANCE) {
    return MAX_DISTANCE;
  }
  return distanceCm;
}

// Conectar WI-FI
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Reconectar ao Broker
void reconnect_mqtt() {
  // Loop até estar conectado
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT Broker...");
    // Tenta conectar
    if (client.connect(mqtt_client_id)) {
      Serial.println("conectado");
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

// Envia dados via MQTT
void sendDataViaMQTT(float nivel_agua, int umidade_solo, int volume_chuva, const String& status_alerta) {
  if (!client.connected()) {
    reconnect_mqtt();
  }

  StaticJsonDocument<256> doc; 
  doc["nivel_agua"] = nivel_agua;
  doc["umidade_solo"] = umidade_solo;
  doc["volume_chuva"] = volume_chuva;
  doc["status_alerta"] = status_alerta;

  String jsonString;
  serializeJson(doc, jsonString); 

  Serial.print("Publicando dados MQTT no topico '");
  Serial.print(mqtt_topic_publish);
  Serial.print("': ");
  Serial.println(jsonString);

  // Publica no tópico MQTT
  if (client.publish(mqtt_topic_publish, jsonString.c_str())) {
    Serial.println("Dados MQTT publicados com sucesso!");
  } else {
    Serial.println("Falha ao publicar dados MQTT.");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);

  Serial.println("--- Sistema de Monitoramento de Enchentes (MQTT) ---");
  Serial.println("Ajuste os sliders dos sensores para simular condicoes!");
  Serial.println("----------------------------------------------------------");

  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  reconnect_mqtt(); 
}

void loop() {
  // Garante que o MQTT esteja sempre conectado
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  unsigned int distancia_cm = measureDistanceCm();
  float nivel_agua_cm = (distancia_cm >= MAX_DISTANCE) ? 0 : (MAX_DISTANCE - distancia_cm);

  int umidadeSolo = analogRead(SOIL_MOISTURE_PIN);
  int volumeChuva = analogRead(RAIN_POT_PIN);

  // Lógica de Alerta 
  bool riscoEnchente = false;
  String statusAlerta = "Seguro"; 

  if (nivel_agua_cm >= LIMIAR_NIVEL_AGUA_ALTA) {
    Serial.println("    -> CONDICAO: Nivel da agua atingiu limiar critico!");
    riscoEnchente = true;
  }

  if (umidadeSolo >= LIMIAR_UMIDADE_SOLO_SATURADO && volumeChuva >= LIMIAR_CHUVA_FORTE) {
    Serial.println("    -> CONDICAO: Solo saturado e chuva forte simultaneamente!");
    riscoEnchente = true;
  }

  if (riscoEnchente) {
    Serial.println("!!! ALERTA DE ENCHENTE: PERIGO IMINENTE !!!");
    digitalWrite(LED_PIN, HIGH);
    statusAlerta = "Alerta de Enchente"; 
  } else {
    Serial.println("Status: Ambiente seguro.");
    digitalWrite(LED_PIN, LOW);
  }

  sendDataViaMQTT(nivel_agua_cm, umidadeSolo, volumeChuva, statusAlerta);
  Serial.println("----------------------------------------------------------");
  delay(5000); 
}
