#include "logger.h"
#include <NTPClient.h>
#include <WiFiUDP.h>

String Logger::lastEvent = "";
String Logger::systemLog = "";

extern NTPClient timeClient;

void Logger::init() {
    systemLog.reserve(2048);
    lastEvent.reserve(256);
}

void Logger::addLog(const String& message) {
    String timestamp = timeClient.getFormattedTime();
    String logEntry = "[" + timestamp + "] " + message;
    systemLog += logEntry + "\n";
    lastEvent = message;
    
    // Mantener solo los últimos MAX_LOG_LINES registros
    int lineCount = 0;
    for (int i = 0; i < systemLog.length(); i++) {
        if (systemLog.charAt(i) == '\n') lineCount++;
    }
    
    if (lineCount > MAX_LOG_LINES) {
        int firstNewline = systemLog.indexOf('\n');
        systemLog = systemLog.substring(firstNewline + 1);
    }
    
    Serial.println(logEntry);
}

String Logger::getLastEvent() {
    return lastEvent;
}

String Logger::getSystemLog() {
    return systemLog;
}

void Logger::clearLastEvent() {
    lastEvent = "";
}
