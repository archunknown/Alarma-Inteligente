#include "webserver.h"
#include "config.h"
#include "security.h"
#include "classes.h"
#include "logger.h"
#include "hardware.h"
#include <ArduinoJson.h>

WebServer WebServerManager::server(80);
SecuritySystem* WebServerManager::securitySystem = nullptr;
ClassesSystem* WebServerManager::classesSystem = nullptr;

void WebServerManager::init(SecuritySystem* security, ClassesSystem* classes) {
    securitySystem = security;
    classesSystem = classes;
    
    // Configurar rutas
    server.on("/", HTTP_GET, handleRoot);
    server.on("/api/status", HTTP_GET, handleGetStatus);
    server.on("/api/mode", HTTP_POST, handleSetMode);
    server.on("/api/emergency", HTTP_POST, handleEmergency);
    server.on("/api/stop-buzzer", HTTP_POST, handleStopBuzzer);
    server.on("/api/horarios", HTTP_POST, handleSetHorarios);
    server.on("/api/events", HTTP_GET, handleGetEvents);
    server.on("/api/log", HTTP_GET, handleGetLog);
    
    // Habilitar CORS
    server.enableCORS(true);
    
    server.begin();
    Logger::addLog("Servidor web iniciado");
}

void WebServerManager::handleClient() {
    server.handleClient();
}

void WebServerManager::handleRoot() {
    server.send(200, "text/html", getHtmlContent());
}

void WebServerManager::handleGetStatus() {
    DynamicJsonDocument doc(1024);
    
    if (securitySystem->isActive()) {
        doc["mode"] = "security";
    } else if (classesSystem->isActive()) {
        doc["mode"] = "classes";
    } else {
        doc["mode"] = "none";
    }
    
    doc["emergencyActive"] = classesSystem->isEmergencyAlarmActive();
    doc["pirActive"] = securitySystem->isAlarmTriggered();
    
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
}

void WebServerManager::handleSetMode() {
    if (server.hasArg("plain")) {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, server.arg("plain"));
        
        String mode = doc["mode"];
        
        // Detener cualquier alarma activa
        stopAllOutputs();
        
        if (mode == "security") {
            classesSystem->deactivate();
            securitySystem->activate();
        } else if (mode == "classes") {
            securitySystem->deactivate();
            classesSystem->activate();
        } else {
            securitySystem->deactivate();
            classesSystem->deactivate();
        }
        
        server.send(200, "application/json", "{\"status\":\"ok\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"Invalid request\"}");
    }
}

void WebServerManager::handleEmergency() {
    if (server.hasArg("plain")) {
        DynamicJsonDocument doc(512);
        deserializeJson(doc, server.arg("plain"));
        
        bool activate = doc["active"];
        
        if (classesSystem->isActive()) {
            classesSystem->toggleEmergencyAlarm(activate);
        }
        
        server.send(200, "application/json", "{\"status\":\"ok\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"Invalid request\"}");
    }
}

void WebServerManager::handleStopBuzzer() {
    stopAllOutputs();
    securitySystem->stopAlarm();
    classesSystem->toggleEmergencyAlarm(false);
    
    Logger::addLog("SISTEMA: Buzzer detenido manualmente");
    server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void WebServerManager::handleSetHorarios() {
    if (server.hasArg("plain")) {
        DynamicJsonDocument doc(512);
        deserializeJson(doc, server.arg("plain"));
        
        String entrada = doc["entrada"];
        String receso = doc["receso"];
        String salida = doc["salida"];
        
        classesSystem->setSchedule(entrada, receso, salida);
        
        server.send(200, "application/json", "{\"status\":\"ok\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"Invalid request\"}");
    }
}

void WebServerManager::handleGetEvents() {
    server.send(200, "text/plain", Logger::getLastEvent());
    Logger::clearLastEvent();
}

void WebServerManager::handleGetLog() {
    server.send(200, "text/plain", Logger::getSystemLog());
}

// El contenido HTML se incluirá desde index.h
extern const char INDEX_HTML[] PROGMEM;

const char* WebServerManager::getHtmlContent() {
    return INDEX_HTML;
}
