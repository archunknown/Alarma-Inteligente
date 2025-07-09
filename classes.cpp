#include "classes.h"
#include "config.h"
#include "hardware.h"
#include "logger.h"

void ClassesSystem::init() {
    deactivate();
}

void ClassesSystem::update(const String& currentTime) {
    if (!active) return;

    // Verificar horarios de timbre
    if (currentTime == horaEntrada && !timbreActivado[0]) {
        ringBell("ENTRADA");
        timbreActivado[0] = true;
    }
    
    if (currentTime == horaReceso && !timbreActivado[1]) {
        ringBell("RECESO");
        timbreActivado[1] = true;
    }
    
    if (currentTime == horaSalida && !timbreActivado[2]) {
        ringBell("SALIDA");
        timbreActivado[2] = true;
    }
    
    // Reset diario de timbres (a las 00:00)
    if (currentTime == "00:00") {
        resetDailyBells();
    }
}

void ClassesSystem::activate() {
    active = true;
    resetDailyBells();
    Logger::addLog("CLASES: Modo clases activado");
}

void ClassesSystem::deactivate() {
    active = false;
    emergencyAlarmActive = false;
    stopAllOutputs();
    Logger::addLog("CLASES: Modo clases desactivado");
}

bool ClassesSystem::isActive() const {
    return active;
}

void ClassesSystem::setSchedule(const String& entrada, const String& receso, const String& salida) {
    horaEntrada = entrada;
    horaReceso = receso;
    horaSalida = salida;
    
    resetDailyBells();
    
    String logMsg = "HORARIOS: Configurados - Entrada:" + entrada + 
                   ", Receso:" + receso + ", Salida:" + salida;
    Logger::addLog(logMsg);
}

void ClassesSystem::toggleEmergencyAlarm(bool state) {
    emergencyAlarmActive = state;
    
    if (state) {
        setLED(true);
        setBuzzer(true, 1500);
        Logger::addLog("EMERGENCIA: Alarma manual activada");
    } else {
        stopAllOutputs();
        Logger::addLog("EMERGENCIA: Alarma manual desactivada");
    }
}

bool ClassesSystem::isEmergencyAlarmActive() const {
    return emergencyAlarmActive;
}

void ClassesSystem::ringBell(const String& type) {
    setLED(true);
    setBuzzer(true, 1000);
    
    String event = "CLASES: Timbre de " + type + " activado";
    Logger::addLog(event);
}

void ClassesSystem::resetDailyBells() {
    timbreActivado[0] = timbreActivado[1] = timbreActivado[2] = false;
}
