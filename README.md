# 🌦️ Estación Meteorológica Inteligente con Control de Calefacción

Este proyecto presenta una **Estación Meteorológica Inteligente** basada en el microcontrolador **ESP8266**, diseñada para monitorear y visualizar datos ambientales en tiempo real, así como controlar un sistema de calefacción.  
La estación mide **temperatura, humedad y luminosidad**, proporcionando una interfaz web interactiva para el usuario.

---

## ✨ Características Principales

### 🔍 Monitoreo Ambiental
- Sensor **DHT22** para medir temperatura y humedad.
- Sensor **LDR** para medir la luminosidad del entorno.

### 🖥️ Interfaz Web
- Interfaz web moderna y responsiva.
- Gráficos interactivos en tiempo real con **Highcharts**.
- Visualización de históricos de mediciones.

### 🔥 Control de Calefacción
- Posibilidad de fijar una **temperatura objetivo**.
- Activación/desactivación automática de la calefacción según la temperatura ambiente.
- Visualización de temperatura actual vs. temperatura fijada.

### 📄 Exportación de Datos
- Funcionalidad para **exportar todos los gráficos a PDF**.
- Ideal para análisis y almacenamiento de registros históricos.

---

## ⚙️ Instalación

### 📋 Requisitos Previos

- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP8266 Board Support Package](https://github.com/esp8266/Arduino#installing-with-boards-manager)
- [LittleFS Arduino Library](https://github.com/lorol/LITTLEFS)
- [ArduinoJson Library](https://arduinojson.org/)
- [DHT Library](https://github.com/adafruit/DHT-sensor-library)
- [WebSockets Library](https://github.com/Links2004/arduinoWebSockets)
- [Highcharts Library](https://www.highcharts.com/)

### 🛠️ Pasos de Instalación

1. **Clonar o descargar el repositorio:**
   ```bash
   git clone https://gitlab.com/ejemplos_arduino/estacionmeteorologica.git
    ```

## 📡 Obtención y envío de datos

La estación meteorológica recoge datos de los sensores conectados al **ESP8266** y los envía a la interfaz web en tiempo real mediante **WebSockets**.

### 🔍 Proceso interno

1. **Lectura de sensores (cada 4 segundos):**
   - `DHT22` → temperatura (`t`) y humedad (`h`).  
   - `LDR` → luminosidad (`l`).  
   - Los valores se almacenan en variables globales.

   ```cpp
   h = dht.readHumidity();
   t = dht.readTemperature();
   l = 1024 - analogRead(PIN_LDR);
   ```

2. **Control de calefacción automático:**

    Actúa en consecuencia comparando la temperatura ambiente con la fijada.

    ```cpp
   controlSistemaCalefaccion();
   ```

3. **Creación del mensaje JSON**

    ```cpp
   String jsonData = "{\"temperatura\":" + String(t) + 
                  ",\"humedad\":" + String(h) + 
                  ",\"luminosidad\":" + String(l) + "}";
   ```

4. **Envío por WebSocket**

    El JSON se transmite a todos los clientes conectados en tiempo real.

    ```cpp
   webSocket.broadcastTXT(jsonData);
   ```

5. **Obtención de datos**

    El cliente recibirá los datos y son interpretados por la interfaz web, que actualiza los gráficos en tiempo real y permite al usuario visualizar el estado ambiental y controlar la calefacción.

    Ejemplo:
    ```
    {
    "temperatura": 23.7,
    "humedad": 42.5,
    "luminosidad": 680
    }
    ```
