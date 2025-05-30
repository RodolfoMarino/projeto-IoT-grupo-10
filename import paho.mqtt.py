import paho.mqtt.client as mqtt
import time
import json

# Configuração do broker MQTT
broker = "broker.hivemq.com"
porta = 1883
topico = "sensor/nivel_agua"
client_id = "SimuladorWokwiBridge"

# Criação do cliente MQTT
client = mqtt.Client(client_id=client_id, protocol=mqtt.MQTTv311)
client.connect(broker, porta, 60)

print("Conectado ao broker MQTT!")

try:
    while True:
        # Entradas simuladas baseadas no que aparece no Wokwi
        nivel_agua = float(input("Digite o valor de nível da água (cm): "))
        tempo_leitura = float(input("Digite o tempo de leitura do sensor (ms): "))
        tempo_total = float(input("Digite o tempo total até publicação + buzzer (ms): "))

        mensagem = json.dumps({
            "nivel_agua": nivel_agua,
            "tempo_leitura_sensor_ms": tempo_leitura,
            "tempo_total_ms": tempo_total,
            "alerta": "Buzzer Ligado" if nivel_agua < 10 else "Buzzer Desligado"
        })

        client.publish(topico, mensagem)
        print("Publicado:", mensagem)

        time.sleep(2)

except KeyboardInterrupt:
    client.disconnect()
    print("Desconectado.")
