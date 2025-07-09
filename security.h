#ifndef SECURITY_H
#define SECURITY_H

#include <Arduino.h>

class SecuritySystem {
public:
    void init();
    void update(unsigned long currentMillis);
    void activate();
    void deactivate();
    bool isActive() const;
    bool isAlarmTriggered() const;
    void stopAlarm();

private:
    bool active = false;
    bool alarmTriggered = false;
    unsigned long alarmEndTime = 0;
    void sendAlertMessage() const;
};

#endif
