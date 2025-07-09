#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
const char* WIFI_SSID = "TASAYCO 5G";
const char* WIFI_PASSWORD = "pivotArchAdrian";

// Pin Configuration
const int LED_PIN = 2;     // LED indicativo
const int BUZZER_PIN = 4;  // Buzzer pasivo
const int PIR_PIN = 13;    // Sensor PIR

// CallMeBot Configuration
const char* CALLMEBOT_PHONE = "51999999999;
const char* CALLMEBOT_API_KEY = "7256100";

// Time Configuration
const int UTC_OFFSET = -5; // UTC-5 (Peru)
const int NTP_UPDATE_INTERVAL = 60000; // 60 seconds

// Alarm Configuration
const unsigned long ALARM_DURATION = 5000;
const unsigned long BELL_DURATION = 3000;

#endif
