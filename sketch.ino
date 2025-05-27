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
    Serial.print(".");
  }
  Serial.println("\nConectado!");
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

// Função para medir a distância com HC-SR04 e calcular tempo de leitura
float medirNivelAgua(unsigned long &tempoLeituraSensor) {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  unsigned long inicio = millis();
  long duration = pulseIn(ECHO_PIN, HIGH);
  unsigned long fim = millis();
  tempoLeituraSensor = fim - inicio;

  float distancia = duration * 0.034 / 2; // Corrigida a fórmula de medição
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

  unsigned long tempoTotalInicio = millis(); // Marca o tempo total do ciclo

  unsigned long tempoLeituraSensor = 0;
  float nivelAgua = medirNivelAgua(tempoLeituraSensor);

  Serial.print("Nível da água: ");
  Serial.print(nivelAgua);
  Serial.println(" cm");

  Serial.print("Tempo de leitura do sensor: ");
  Serial.print(tempoLeituraSensor);
  Serial.println(" ms");

  // Envia os dados para o MQTT
  char msg[10];
  dtostrf(nivelAgua, 4, 2, msg);
  client.publish(topic, msg);

  // Alerta sonoro se o nível estiver abaixo de 10 cm
  if (nivelAgua > 10) {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Buzzer: Desligado");
  } else {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Buzzer: Ligado");
    delay(500);
  }

  unsigned long tempoTotalFim = millis();
  unsigned long tempoTotal = tempoTotalFim - tempoTotalInicio;

  Serial.print("Tempo total até publicação + buzzer: ");
  Serial.print(tempoTotal);
  Serial.println(" ms");
  Serial.println("-----------------------------");

  delay(2000); // Mede a cada 2 segundos
}
