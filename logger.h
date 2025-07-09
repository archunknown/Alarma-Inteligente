#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {
public:
    static void init();
    static void addLog(const String& message);
    static String getLastEvent();
    static String getSystemLog();
    static void clearLastEvent();

private:
    static String lastEvent;
    static String systemLog;
    static const int MAX_LOG_LINES = 20;
};

#endif
