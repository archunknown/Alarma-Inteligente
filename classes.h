#ifndef CLASSES_H
#define CLASSES_H

#include <Arduino.h>

class ClassesSystem {
public:
    void init();
    void update(const String& currentTime);
    void activate();
    void deactivate();
    bool isActive() const;
    
    void setSchedule(const String& entrada, const String& receso, const String& salida);
    void toggleEmergencyAlarm(bool state);
    bool isEmergencyAlarmActive() const;
    void ringBell(const String& type);

private:
    bool active = false;
    bool emergencyAlarmActive = false;
    
    String horaEntrada = "07:30";
    String horaReceso = "10:30";
    String horaSalida = "12:30";
    
    bool timbreActivado[3] = {false, false, false}; // entrada, receso, salida
    
    void resetDailyBells();
};

#endif
