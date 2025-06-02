🌊 Monitoramento de Enchentes: Sistema Inteligente com ESP32 e Node-RED ☔
Descrição do Projeto
O Monitoramento de Enchentes é um sistema protótipo desenvolvido para acompanhar em tempo real as condições ambientais que podem levar a inundações. Utilizando um ESP32 como dispositivo de borda (Edge Computing), o projeto coleta dados de sensores de nível da água (ultrassônico), umidade do solo e volume de chuva (simulado por um potenciômetro).

Os dados são transmitidos via MQTT para um broker e, em seguida, processados e visualizados em um Dashboard interativo no Node-RED. Este projeto demonstra como a Internet das Coisas (IoT) e o Edge Computing podem ser aplicados para prever riscos e otimizar a gestão de emergências.

Objetivo
O principal objetivo do sistema de Monitoramento de Enchentes é fornecer informações cruciais para a prevenção e resposta a inundações, visando:

Detecção Precoce: Identificar condições de risco de enchente antes que se tornem críticas.
Monitoramento em Tempo Real: Oferecer uma visão constante dos parâmetros ambientais relevantes.
Visualização Clara: Apresentar os dados de forma intuitiva através de um dashboard interativo.
Alerta Automatizado: Disparar alertas visuais quando os limiares de risco são atingidos.
Demonstrar IoT e Edge Computing: Aplicar conceitos modernos de tecnologia em um problema real.
Funcionalidades
Medição de Nível da Água: Sensor ultrassônico mede a distância até a superfície da água, inferindo o nível.
Detecção de Umidade do Solo: Sensor lê a umidade do solo, indicando sua saturação.
Simulação de Volume de Chuva: Um potenciômetro simula a intensidade da precipitação.
Processamento de Borda (Edge Computing): O ESP32 processa os dados dos sensores e aplica lógicas de alerta básicas localmente antes de enviar os dados.
Comunicação MQTT: Transmissão de dados leve e eficiente para o broker MQTT.
Dashboard Interativo: Visualização em tempo real de todos os parâmetros e status de alerta no Node-RED.
Alertas Visuais: LED no ESP32 e mensagens no dashboard indicam risco de enchente.
Monitoramento Serial: Saída de dados via Monitor Serial para depuração e validação.
Requisitos do Sistema
Hardware:
ESP32 DevKit C (ou similar compatível)
Sensor Ultrassônico HC-SR04
Sensor de Umidade do Solo
Potenciômetro (para simulação de chuva)
LED (para indicação de alerta)
Protoboard e fios para conexões
Fonte de energia (via USB ou externa)
Software:
Arduino IDE
Node-RED instalado (ou versão online, ex: cloud.nodered.org para testes)
Broker MQTT (ex: broker.hivemq.com para testes, ou um local como Mosquitto)
Dependências (Arduino IDE):
WiFi.h (padrão para ESP32)
PubSubClient.h (para comunicação MQTT)
ArduinoJson.h (para serialização de dados JSON)
Dependências (Node-RED):
node-red-dashboard (paleta para criar o dashboard)
Instruções de Uso
Passo 1: Conexões de Hardware
Certifique-se de que o ESP32 e os sensores estejam conectados conforme o código. Um exemplo básico:

Sensor Ultrassônico HC-SR04:
VCC → 5V (ou 3.3V, dependendo do modelo do sensor e da placa) do ESP32
GND → GND do ESP32
Trig → Pino Digital 13 do ESP32
Echo → Pino Digital 14 do ESP32
Sensor de Umidade do Solo:
VCC → 3.3V do ESP32
GND → GND do ESP32
A0 (Saída Analógica) → Pino Analógico 34 do ESP32
Potenciômetro (Simulação de Chuva):
VCC → 3.3V do ESP32
GND → GND do ESP32
Pino Central → Pino Analógico 32 do ESP32
LED de Alerta:
Ânodo (perna longa) → Pino Digital 22 do ESP32 (via resistor de 220 Ohm)
Cátodo (perna curta) → GND do ESP32
Passo 2: Configuração do Código (Arduino IDE)
Abra a IDE do Arduino.
Copie e cole o código fornecido para o ESP32.
Ajuste as credenciais Wi-Fi:
C++

const char* ssid = "SEU_SSID_WIFI";
const char* password = "SUA_SENHA_WIFI";
(Para Wokwi, ssid = "Wokwi-GUEST" e password = "" funcionam automaticamente.)
Ajuste as configurações MQTT (se necessário):
C++

const char* mqtt_broker = "broker.hivemq.com"; // Ou o IP/endereço do seu broker
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32_FloodMonitor";
const char* mqtt_topic_publish = "sensor/monitoramento_enchente";
Selecione a placa ESP32 Dev Module (ou a sua placa ESP32 específica) e a porta COM correta.
Faça o upload do código para o ESP32.
Passo 3: Configuração do Node-RED
Abra seu Node-RED (geralmente em http://localhost:1880/).
Instale a paleta node-red-dashboard se ainda não tiver:
Menu (três linhas) -> Manage palette -> Install -> Procure por node-red-dashboard.
Importe o fluxo do Node-RED (se tiver um arquivo .json do fluxo) ou crie-o manualmente conforme as instruções anteriores:
Um nó mqtt in (conectado ao broker.hivemq.com e ao tópico sensor/monitoramento_enchente, com saída a parsed JSON object).
Um nó function para extrair e ramificar os dados.
Nós ui_gauge para Nível da Água, Umidade do Solo, Volume de Chuva.
Um nó ui_text para Status do Alerta.
Um nó ui_chart para Histórico de Nível da Água.
Certifique-se de que as saídas do nó function estejam conectadas corretamente aos respectivos widgets do dashboard.
Clique em "Deploy" para ativar o fluxo.
Passo 4: Testar o Sistema
Inicie a simulação no Wokwi ou ligue seu ESP32 físico.
Monitore a saída serial do ESP32 para verificar a conexão Wi-Fi e a publicação MQTT.
Acesse o dashboard do Node-RED no seu navegador (geralmente http://localhost:1880/ui).
No Wokwi: Ajuste os sliders dos sensores (distância, umidade do solo, potenciômetro) para simular diferentes condições.
Observe o dashboard se atualizar em tempo real, exibindo os valores dos sensores, o status do alerta e o histórico do nível da água. O LED no ESP32 também deve acender quando as condições de alerta forem atingidas.
Diagrama do Sistema
(Aqui você inseriria o diagrama que geramos para o seu projeto, ou um link para ele no Draw.io/diagrams.net)

(Exemplo: Substitua com o link real da sua imagem)

Dashboard no Node-RED
(Aqui você inseriria uma captura de tela do seu dashboard no Node-RED)

(Exemplo: Substitua com o link real da sua imagem)

Fluxo do Node-RED
(Aqui você inseriria uma captura de tela do seu fluxo no Node-RED)

(Exemplo: Substitua com o link real da sua imagem)

Captura de Tela do Projeto e Link
Link Wokwi: https://wokwi.com/projects/429612764102574081
Captura de Tela: (Exemplo: Substitua com uma captura de tela do seu Wokwi)
Vídeo do Projeto
(Aqui você inseriria o link para um vídeo demonstrativo do projeto, se tiver um. Mantenha o formato http://www.youtube.com/0 como placeholder se não tiver um link real ainda.)

Link para o Vídeo Demonstrativo (Exemplo: Substitua com o link real do seu vídeo)

Integrantes
Luiz Gustavo Araújo de Lima e Silva - RM560110
Arthur Silva - RM560771
Pedro Estevam - RM560642
Matheus Siroma - RM560248
