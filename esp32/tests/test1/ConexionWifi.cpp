#include "ConexionWifi.h"
#include <WiFi.h>

ConexionWifi::ConexionWifi()
    : timeoutMs(3000)
{
}

ConexionWifi::~ConexionWifi()
{
    desconectar();
}

String ConexionWifi::getStatus()
{
    switch (WiFi.status())
    {
    case WL_CONNECTED:
        return "CONECTADO";
    case WL_NO_SSID_AVAIL:
        return "RED NO DISPONIBLE";
    case WL_CONNECT_FAILED:
        return "ERROR DE CONEXION";
    case WL_DISCONNECTED:
        return "DESCONECTADO";
    default:
        return "ESTADO DESCONOCIDO";
    }
}

void ConexionWifi::conectar()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(RED_WIFI_NOMBRE, RED_WIFI_PASSWORD);
        unsigned long start = millis();

        while (WiFi.status() != WL_CONNECTED && ((millis() - start) < timeoutMs))
        {
        }
        delay(500);
    }
}

void ConexionWifi::desconectar()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.disconnect();
    }
}

bool ConexionWifi::isConectado()
{
    return WiFi.status() == WL_CONNECTED;
}

void ConexionWifi::setTimeOut(unsigned long timeoutMs)
{
    this->timeoutMs = timeoutMs;
}
