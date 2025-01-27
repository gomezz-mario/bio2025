#ifndef CONEXION_WIFI_H
#define CONEXION_WIFI_H

#define RED_WIFI_NOMBRE "Personal-709"
#define RED_WIFI_PASSWORD "29523CD709"

#include <Arduino.h>

class ConexionWifi
{
private:
    unsigned long timeoutMs;

public:
    ConexionWifi();
    ~ConexionWifi();
    String getStatus();
    void conectar();
    void desconectar();
    bool isConectado();
    void setTimeOut(unsigned long timeoutMs);
};

#endif
