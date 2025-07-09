#include "security.h"
#include "config.h"
#include "hardware.h"
#include "logger.h"
#include <HTTPClient.h>
#include <WiFi.h>

void SecuritySystem::init() {
    deactivate();
}

void SecuritySystem::update(unsigned long currentMillis) {
    if (!active) return;

    // Verificar sensor PIR
    if (getPIRState() && !alarmTriggered) {
        alarmTriggered = true;
        alarmEndTime = currentMillis + ALARM_DURATION;
        setLED(true);
        setBuzzer(true, 2000);
        
        Logger::addLog("SEGURIDAD: Movimiento detectado - Alarma activada");
        sendAlertMessage();
    }
    
    // Verificar fin de alarma
    if (alarmTriggered && currentMillis >= alarmEndTime) {
        stopAlarm();
        Logger::addLog("SEGURIDAD: Alarma PIR detenida automáticamente");
    }
}

void SecuritySystem::activate() {
    active = true;
    alarmTriggered = false;
    Logger::addLog("SEGURIDAD: Modo seguridad activado");
}

void SecuritySystem::deactivate() {
    active = false;
    stopAlarm();
    Logger::addLog("SEGURIDAD: Modo seguridad desactivado");
}

bool SecuritySystem::isActive() const {
    return active;
}

bool SecuritySystem::isAlarmTriggered() const {
    return alarmTriggered;
}

void SecuritySystem::stopAlarm() {
    alarmTriggered = false;
    alarmEndTime = 0;
    setLED(false);
    setBuzzer(false);
}

void SecuritySystem::sendAlertMessage() const {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "https://api.callmebot.com/whatsapp.php?phone=" + String(CALLMEBOT_PHONE) + 
                    "&text=Intruso+detectado+en+modo+seguridad&apikey=" + String(CALLMEBOT_API_KEY);
        http.begin(url);
        int httpCode = http.GET();
        
        if (httpCode > 0) {
            Logger::addLog("SEGURIDAD: Alerta WhatsApp enviada");
        } else {
            Logger::addLog("SEGURIDAD: Error al enviar alerta WhatsApp");
        }
        http.end();
    }
}
