
# 🌊 Monitoramento de Enchentes: Sistema Inteligente com ESP32 e Node-RED ☔

## 📑 Descrição do Projeto

Este projeto é um sistema de **Monitoramento de Enchentes** que acompanha, em tempo real, condições ambientais que podem indicar risco de inundações. Utilizando um **ESP32** como dispositivo de borda (**Edge Computing**), ele coleta dados de:

- **Nível da água** (sensor ultrassônico)
- **Umidade do solo**
- **Volume de chuva** (simulado por um potenciômetro)

Os dados são enviados via **MQTT** para um broker, sendo processados e visualizados em um **dashboard interativo no Node-RED**. Este projeto demonstra como **IoT e Edge Computing** podem ser aplicados para prever riscos e auxiliar na gestão de emergências.

## 🎯 Objetivos

- ⚠️ **Detecção Precoce:** Identificar condições de risco antes que se tornem críticas.
- 🔍 **Monitoramento em Tempo Real:** Acompanhar os parâmetros ambientais constantemente.
- 📊 **Visualização Clara:** Exibir dados de forma intuitiva em um dashboard.
- 🚨 **Alertas Automatizados:** Emitir alertas visuais quando os níveis de risco são atingidos.
- 🌐 **Aplicação de IoT e Edge Computing:** Utilizar tecnologias atuais para resolver problemas reais.

## 🔥 Funcionalidades

- 📏 **Medição de Nível da Água:** Via sensor ultrassônico.
- 🌱 **Medição de Umidade do Solo:** Através de sensor capacitivo ou resistivo.
- 🌧️ **Simulação de Volume de Chuva:** Controlado por um potenciômetro.
- 🧠 **Edge Computing:** O ESP32 processa dados localmente, aplicando lógicas de alerta.
- 🔗 **Comunicação via MQTT:** Envio eficiente de dados.
- 🖥️ **Dashboard Node-RED:** Monitoramento visual dos dados.
- 🚦 **Alertas Visuais:** LED no ESP32 e notificações no dashboard.
- 🔧 **Saída Serial:** Para monitoramento e depuração.

## 🧰 Requisitos do Sistema

### 🔌 Hardware
- ✅ ESP32 DevKit C (ou equivalente)
- ✅ Sensor Ultrassônico HC-SR04
- ✅ Sensor de Umidade do Solo
- ✅ Potenciômetro (simulação de chuva)
- ✅ LED (alerta)
- ✅ Protoboard e jumpers
- ✅ Fonte de energia (USB ou externa)

### 💻 Software
- **Arduino IDE**
- **Node-RED** (local ou cloud: https://flowfuse.com ou https://nodered.org/)
- **Broker MQTT** (ex.: https://broker.hivemq.com ou local como Mosquitto)

### 📦 Bibliotecas Arduino IDE
- `WiFi.h` (conexão Wi-Fi)
- `PubSubClient.h` (protocolo MQTT)
- `ArduinoJson.h` (serialização JSON)

### 📦 Paletas Node-RED
- `node-red-dashboard` (para criar o dashboard)

## 🔧 Instruções de Uso

### 🛠️ Passo 1: Montagem do Hardware

| Componente               | ESP32                                |
|--------------------------|--------------------------------------|
| **HC-SR04**              | VCC → 5V / 3.3V<br>GND → GND<br>Trig → D13<br>Echo → D14 |
| **Umidade do Solo**      | VCC → 3.3V<br>GND → GND<br>A0 → A34 |
| **Potenciômetro (Chuva)**| VCC → 3.3V<br>GND → GND<br>Pino Central → A32 |
| **LED (Alerta)**         | Ânodo → D22 (via resistor 220Ω)<br>Cátodo → GND |

### 💻 Passo 2: Código no Arduino IDE

1. Abra a Arduino IDE.
2. Insira o código do ESP32.
3. Configure o Wi-Fi:

```cpp
const char* ssid = "SEU_SSID_WIFI";
const char* password = "SUA_SENHA_WIFI";
// No Wokwi → ssid = "Wokwi-GUEST", password = "";
```

4. Configure o broker MQTT:

```cpp
const char* mqtt_broker = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32_FloodMonitor";
const char* mqtt_topic_publish = "sensor/monitoramento_enchente";
```

5. Selecione **"ESP32 Dev Module"** como placa.
6. Faça o upload do código.

### 🔗 Passo 3: Configuração no Node-RED

1. Abra Node-RED (geralmente: http://localhost:1880).
2. Instale a paleta `node-red-dashboard`:

> Menu → Manage palette → Install → Pesquisar por `node-red-dashboard`

3. Configure os nós:

- **mqtt in**: 
  - Broker: `broker.hivemq.com`
  - Tópico: `sensor/monitoramento_enchente`
- **function**: Processamento dos dados recebidos.
- **ui_gauge**: 
  - Nível da Água
  - Umidade do Solo
  - Volume de Chuva
- **ui_text**: Status do Alerta
- **ui_chart**: Histórico de Nível da Água

4. Clique em **"Deploy"** para rodar o fluxo.

### 🔍 Passo 4: Teste e Monitoramento

- 🏗️ **No Wokwi:** Use sliders para simular valores dos sensores.
- ⚙️ **No físico:** Observe a atualização no Dashboard e no LED de alerta.
- 🔗 Dashboard → http://localhost:1880/ui (ou endereço do seu servidor)

## 🗺️ Diagrama do Sistema

> *(Insira aqui o link do diagrama no Draw.io, Excalidraw ou uma imagem do projeto)*

## 📊 Dashboard Node-RED

> *(Insira uma captura de tela do dashboard funcionando)*

## 🔁 Fluxo do Node-RED

> *(Insira uma captura do fluxo Node-RED ou link para o JSON do fluxo)*

## 🔗 Captura de Tela e Link do Projeto

- 🌐 Projeto no Wokwi: [Clique aqui](https://wokwi.com/projects/429612764102574081)
- 🖼️ Captura de Tela: *(Adicione aqui)*

## 🎥 Vídeo do Projeto

> *(Adicione o link do vídeo demonstrativo no YouTube ou outra plataforma)*

## 👥 Integrantes do Projeto

- Luiz Gustavo Araújo de Lima e Silva — RM560110  
