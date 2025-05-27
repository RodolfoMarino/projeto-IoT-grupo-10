#include <WiFi.h>
#include <PubSubClient.h>


// Configuração do MQTT
const char* mqtt_server = "broker.hivemq.com"; // Pode-se usar outro broker MQTT
const char* topic = "sensor/nivel_agua";

WiFiClient espClient;
PubSubClient client(espClient);

// Definição dos pinos
#define TRIGGER_PIN 5  // Pino do Trigger do HC-SR04
#define ECHO_PIN 18     // Pino do Echo do HC-SR04
#define BUZZER_PIN 19   // Pino do buzzer

// Função para conectar ao Wi-Fi
void setup_wifi() {
  Serial.print("Conectando ao Wi-Fi...");
WiFi.begin("Wokwi-GUEST", ""); //(wifi ssid, password)
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
  }
  Serial.println("Conectado!");
}

// Função para conectar ao MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s...");
      delay(5000);
    }
  }
}

// Função para medir a distância com HC-SR04
float medirNivelAgua() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distancia = 400 * 0.034 / 2; // 0.034 cm/μs é a velocidade do som no ar 

  return distancia;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float nivelAgua = medirNivelAgua();
  Serial.print("Nível da água: ");
  Serial.print(nivelAgua);
  Serial.println(" cm");

  // Envia os dados para o MQTT
  char msg[10];
  dtostrf(nivelAgua, 4, 2, msg);
  client.publish(topic, msg);

  // Alerta sonoro se o nível estiver abaixo de 10 cm
  if (nivelAgua > 10) {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.print("LOW");
  } else {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.print("HIGH");
    delay(500);
    //digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000); // Mede a cada 2 segundos
}
