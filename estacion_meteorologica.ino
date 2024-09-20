#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTTYPE DHT22
#define ON LOW     
#define OFF HIGH

// Reemplaza con tus credenciales de red
const char *ssid = "Xiaomi 11 Lite 5G NE";
const char *password = "croqueta";

const int DHTPin = 2; // Pin del DHT22
const int PIN_LDR = A0; // Pin lectura del LDR
const int PIN_RELE = D1; // Pin del rele
const float MARGEN_CALEFACCION = 0.5; // Margen de act/des ºC
float h; // Ultimo valor de humedad
float t; // Ultimo valor de temperatura
float l; // Ultimo valor de luminosidad
float tFijada = 25; // Valor de temperatura fijado
bool sActivado = false; // Sistema de calef. actv/desv

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
DHT dht(DHTPin, DHTTYPE);

void handleRoot() {
  // Abre el archivo en modo lectura
  File file = LittleFS.open("/index.html", "r");
  
  if (file) {
    // Lee el contenido del archivo
    String content = file.readString();
    file.close();

    // Envía el contenido como respuesta HTTP
    server.send(200, "text/html", content);
  } else {
    server.send(404, "text/plain", "Error al abrir el archivo");
  }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
}

void handleWebSocketMessage(uint8_t *payload, size_t length) {
  // Analizar el mensaje JSON
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload, length);

  // Identificar el tipo de mensaje y realizar la acción correspondiente
  const char *type = doc["type"];
  if (strcmp(type, "temperature") == 0) {
    // Actualizar la temperatura en el ESP8266
    tFijada = doc["value"];
  } else if (strcmp(type, "calefaccion") == 0) {
    // Activar/desactivar la calefacción en el ESP8266
    sActivado = doc["value"];
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      // Procesar mensaje de texto
      handleWebSocketMessage(payload, length);
      //avisa a todos los clientes del último cambio realizado
      String controlData = "{\"tFijada\":" + String(tFijada) + 
                     ",\"sActivado\":" + String(sActivado) + "}";
      webSocket.broadcastTXT(controlData);
      controlSistemaCalefaccion();
      break;
  }
}

void controlSistemaCalefaccion() {
  float margenInf = tFijada - MARGEN_CALEFACCION;
  float margenSup = tFijada + MARGEN_CALEFACCION;

  if (!sActivado) {
    digitalWrite(PIN_RELE, OFF);
  } 
  else {
    if (t < margenInf) {
      digitalWrite(PIN_RELE, ON);
    }

    if (t > margenSup) {
      digitalWrite(PIN_RELE, OFF);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Conéctate a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conexión establecida");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Inicializa LittleFS
  if (LittleFS.begin()) {
    Serial.println("LittleFS iniciado");
  } else {
    Serial.println("Error al iniciar LittleFS");
    return;
  }

  // Activamos MDNS
  if (MDNS.begin("estacionmeteorologica")) { Serial.println("MDNS responder started"); }

  // Rutas para el servidor web
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);

  // Inicia el servidor
  server.begin();
  // Iniciar WebSocket
  webSocket.begin();
  //Inicia el DHT
  dht.begin();

  // Configuramos pin rele
  pinMode(PIN_RELE, OUTPUT);
}

void loop() {
  server.handleClient();
  MDNS.update();
  webSocket.loop();
  webSocket.onEvent(webSocketEvent); // Manejar mensajes WebSocket
  

  static unsigned long lastTemperatureReading = 0;
  const unsigned long temperatureInterval = 4000; // 4 segundos en milisegundos

  unsigned long currentMillis = millis();

  // Lee la temperatura solo si ha pasado el tiempo especificado
  if (currentMillis - lastTemperatureReading >= temperatureInterval) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    l = 1024 - analogRead(PIN_LDR);

    controlSistemaCalefaccion(); // Comprueba Act./Desc. del sistema de calefacc.

    lastTemperatureReading = currentMillis;
    String jsonData = "{\"temperatura\":" + String(t) + 
                      ",\"humedad\":" + String(h) + 
                      ",\"luminosidad\":" + String(l) + "}";
    webSocket.broadcastTXT(jsonData);
  }

}
