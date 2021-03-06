# PA_Redes_2

Código para coletar informações de temperatura, umidade e luminosidade de um ambiente usando a placa ESP32. Esses dados são enviados via MQTT para a plataforma ThingsBoard, para que possam ser monitorados remotamente.

## Pré-requisitos

### Software

* [ThingsBoard](https://thingsboard.io/docs/user-guide/install/installation-options/?ceInstallType=onPremise)
  * [OpenJDK 11](https://adoptium.net/?variant=openjdk11)
  * [PostgreSQL](https://www.postgresql.org/download/)
* [Arduino IDE](https://www.arduino.cc/en/software)
  * DHT.h
  * PubSubClient.h
  * WiFi.h

### Hardware

* ESP32
* Sensor DHT
* Sensor LDR

## Instruções

### Links úteis

* [Como instalar e rodar o ThingsBoard \(em inglês)](https://thingsboard.io/docs/user-guide/install/windows/)
* [Como inserir um novo dispositivo no ThingsBoard \(em inglês)](https://thingsboard.io/docs/user-guide/ui/devices/)
* [Como instalar o Arduino IDE e configurá-lo para uso com o ESP32](https://www.usinainfo.com.br/blog/programar-esp32-com-a-ide-arduino-tutorial-completo/)

### Sugestão de circuito

<p align="center">
  <img width="459" height="284" src="Exemplo_circuito.png">
</p>

### Código

O programa possui alguns parâmetros importantes:

| Parâmetro | Descrição |
| --- | --- |
| **delay** | Intervalo entre amostragens. Valores abaixo de 2000ms não são recomendados |
| **ssid** | SSID da rede |
| **wifiPassword** | Senha da rede wifi |
| **clientID** | ID do dispositivo no Thingsboard |
| **token** | Token ou nome de usuário do dispositivo no Thingsboard |
| **mqttPassword** | Senha do dispositivo no Thingsboard (opcional) |
| **address** | Endereço da máquina hospedeira do servidor do Thingsboard |
| **port** | Porta dedicada para o servidor do Thingsboard |

Eles devem ser ajustados antes de enviar o código para a placa.
