#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "config.h"
#include "hardware.h"
#include "logger.h"
#include "security.h"
#include "classes.h"
#include "webserver.h"

// NTP Configuration
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET*3600, NTP_UPDATE_INTERVAL);

// System components
SecuritySystem securitySystem;
ClassesSystem classesSystem;

void setup() {
    Serial.begin(115200);
    
    // Inicializar hardware
    setupHardware();
    
    // Conectar WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    
    // Inicializar NTP
    timeClient.begin();
    timeClient.update();
    
    // Inicializar componentes
    Logger::init();
    securitySystem.init();
    classesSystem.init();
    WebServerManager::init(&securitySystem, &classesSystem);
    
    Serial.println("=== Sistema de Alarma Colegio Raúl Porras Barrenechea ===");
    Serial.println("Servidor iniciado en: http://" + WiFi.localIP().toString());
    
    Logger::addLog("Sistema iniciado correctamente");
}

void loop() {
    WebServerManager::handleClient();
    timeClient.update();
    
    unsigned long currentMillis = millis();
    String currentTime = timeClient.getFormattedTime().substring(0, 5); // HH:MM
    
    // Actualizar sistemas según modo
    securitySystem.update(currentMillis);
    classesSystem.update(currentTime);
    
    delay(100);
}
