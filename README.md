# Estación Meteorológica Inteligente con Control de Calefacción

Este proyecto presenta una Estación Meteorológica Inteligente basada en el microcontrolador ESP8266, diseñada para monitorear y visualizar datos ambientales en tiempo real, así como controlar un sistema de calefacción. La estación mide la temperatura, humedad y luminosidad del entorno, proporcionando una interfaz web interactiva para el usuario.

## Características Principales

### 1. Monitoreo Ambiental
- La estación utiliza un sensor DHT22 para medir la temperatura y la humedad.
- La luminosidad se mide mediante un sensor LDR (Resistor Dependiente de la Luz).

### 2. Interfaz Web
- Se ha implementado una interfaz web moderna y receptiva para visualizar los datos recopilados.
- Los datos se presentan en gráficos interactivos utilizando la biblioteca Highcharts.
- La interfaz permite la actualización en tiempo real de las mediciones y la visualización de históricos.

### 3. Control de Calefacción
- El sistema incluye la capacidad de establecer una temperatura objetivo para el entorno.
- Se puede activar o desactivar un sistema de calefacción basado en la temperatura ambiente.
- Un gráfico análogo muestra la temperatura actual y la temperatura fijada.

### 4. Exportación a PDF
- Proporciona una funcionalidad de exportación que permite generar un archivo PDF con todos los gráficos.
- Útil para el análisis de datos y el almacenamiento de registros.

## Instalación

### Requisitos Previos

- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP8266 Board Support Package](https://github.com/esp8266/Arduino#installing-with-boards-manager)
- [LittleFS Arduino Library](https://github.com/lorol/LITTLEFS)
- [ArduinoJson Library](https://arduinojson.org/)
- [DHT Library](https://github.com/adafruit/DHT-sensor-library)
- [WebSockets Library](https://github.com/Links2004/arduinoWebSockets)
- [Highcharts Library](https://www.highcharts.com/blog/news/249-highcharts-arduino-library-v1-0-released)

### Pasos de Instalación

1. **Clonar o Descargar el Repositorio:**
   ```bash
   git clone https://gitlab.com/ejemplos_arduino/estacionmeteorologica.git
   ```

2. **Configurar Arduino IDE:**
   - Abrir el archivo `EstacionMeteorologica.ino` en Arduino IDE.
   - Configurar las credenciales de red (`ssid` y `password`) en el código.

3. **Instalar Bibliotecas Necesarias:**
   - En Arduino IDE, ir a "Sketch" -> "Include Library" -> "Manage Libraries..."
   - Buscar y instalar las siguientes bibliotecas:
      - LittleFS
      - ArduinoJson
      - DHT Sensor Library
      - Arduino WebSockets
      - Highcharts

4. **Seleccionar Placa y Puerto:**
   - En Arduino IDE, seleccionar la placa ESP8266 adecuada y el puerto al que está conectado el dispositivo.

5. **Subir el Código:**
   - Hacer clic en "Subir" para cargar el código en el ESP8266.

6. **Acceder a la Interfaz Web:**
   - Después de cargar el código con éxito, abrir el Monitor Serie en Arduino IDE para obtener la dirección IP asignada al ESP8266.
   - Abrir un navegador web y acceder a esa dirección IP.

## Uso

- La interfaz web mostrará gráficos en tiempo real de temperatura, humedad y luminosidad.
- Se puede establecer la temperatura objetivo y activar/desactivar el sistema de calefacción mediante la interfaz.
- La opción "Exportar todo a PDF" permite generar un archivo PDF con todos los gráficos actuales.

## Configuración Adicional

- La carpeta `data` contiene el archivo `index.html`, que define la interfaz web. Puedes personalizar este archivo según tus necesidades.
- Asegúrate de tener una conexión Wi-Fi estable para que el ESP8266 pueda comunicarse con la interfaz web.

## Contribuciones

¡Las contribuciones son bienvenidas! Si encuentras problemas o tienes ideas para mejorar el proyecto, no dudes en abrir problemas o enviar solicitudes de extracción.

## Realizado por

Este proyecto ha sido realizado por Jesús Manzano Álvarez y Jesús Morales Villegas. Alumnos del grado de informática de la Universidad de Jaén, España.