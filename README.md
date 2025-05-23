# projeto-IoT-grupo-10
Monitoramento Inteligente do Consumo de Água Residencial

O projeto utiliza a plataforma ESP32, que se destaca pela conectividade Wi-Fi e
compatibilidade com o protocolo MQTT, permitindo a transmissão dos dados em tempo
real. Para a medição do nível de água, foi utilizado um sensor ultrassônico HC-SR04, cuja
tecnologia de eco permite aferir a distância da superfície do líquido ao sensor com alta
precisão.

A comunicação dos componentes foi estabelecida por meio de conexões digitais
e, para garantir o envio das informações à nuvem, o protocolo MQTT foi utilizado em
conjunto com um broker de mensagens. O código-fonte foi desenvolvido na IDE do
Arduino, empregando as bibliotecas adequadas para controle da rede Wi-Fi, aquisição de
dados e envio de mensagens ao servidor. A seguir, detalham-se os materiais utilizados e
os métodos adotados para a implementação do sistema.

2.1. Microcontrolador ESP32
O microcontrolador ESP32 foi escolhido como unidade central de processamento do
projeto devido à sua robustez, eficiência energética e capacidade de comunicação sem
fio. Ele possui conectividade Wi-Fi integrada, permitindo a transmissão dos dados
coletados pelos sensores para um servidor remoto utilizando o protocolo MQTT. Além
disso, sua compatibilidade com a IDE Arduino facilita o desenvolvimento e a depuração
do código.
O ESP32 opera com uma tensão de 3.3V e oferece múltiplos pinos de entrada e
saída, como pode ser observado na Figura 1, possibilitando a integração com sensores e
atuadores de maneira eficiente. Sua arquitetura baseada em um processador dual-core
Xtensa LX6 permite a execução de múltiplas tarefas simultaneamente, assegurando a
estabilidade do sistema durante a coleta e o envio de dados.

2.2. Sensor Ultrassônico HC-SR04
O sensor ultrassônico HC-SR04 foi utilizado para medir o nível da água no reservatório.
Esse sensor é amplamente empregado em aplicações que exigem medição de distância,
pois funciona emitindo pulsos ultrassônicos e calculando o tempo que leva para o eco
retornar após refletir na superfície da água. Com base nessa medida, é possível determinar
a altura do líquido no reservatório e, consequentemente, monitorar seu nível em tempo
real.
A escolha desse sensor se deve à sua alta precisão para distâncias curtas (de 2 a
400 centímetros), sua facilidade de uso com microcontroladores e seu baixo custo. O HCSR04 opera com uma tensão de 5V, porém, como o ESP32 trabalha com 3.3V, foi
necessário o uso de um divisor de tensão para garantir a integridade dos sinais
transmitidos ao microcontrolador.

2.3. Buzzer Ativo
Para fornecer alertas sonoros em caso de níveis críticos de água, foi utilizado um buzzer
ativo. Esse componente gera um som audível sempre que recebe um sinal HIGH (3.3V)
do ESP32, servindo como um alerta para os usuários em situações de risco, como um
nível de água excessivamente baixo.
O buzzer foi escolhido por ser um atuador simples e eficaz para indicar eventos
importantes no sistema. Sua instalação e controle são diretos, sendo necessário apenas
um pino digital do ESP32 para sua ativação ou desativação.

2.4. Conexão MQTT
A comunicação entre o ESP32 e um servidor remoto foi implementada utilizando o
protocolo MQTT (Message Queuing Telemetry Transport), que permite a troca de
mensagens entre dispositivos IoT de forma leve e eficiente. A biblioteca PubSubClient
foi empregada para gerenciar a conexão do ESP32 com o broker MQTT, garantindo a
transmissão dos dados coletados pelo sensor ultrassônico para um painel de
monitoramento.
