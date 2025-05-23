# projeto-IoT-grupo-10

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
