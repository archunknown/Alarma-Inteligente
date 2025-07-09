#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <WebServer.h>
#include <Arduino.h>

class WebServerManager {
public:
    static void init(SecuritySystem* security, ClassesSystem* classes);
    static void handleClient();

private:
    static WebServer server;
    static SecuritySystem* securitySystem;
    static ClassesSystem* classesSystem;
    
    // Handlers
    static void handleRoot();
    static void handleGetStatus();
    static void handleSetMode();
    static void handleEmergency();
    static void handleStopBuzzer();
    static void handleSetHorarios();
    static void handleGetEvents();
    static void handleGetLog();
    
    // HTML content
    static const char* getHtmlContent();
};

#endif
