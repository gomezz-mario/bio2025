#ifndef LECTURA_H
#define LECTURA_H

#include <Arduino.h>

class Lectura
{

public:
    Lectura(String sensorId, unsigned long timestamp, float valor);
    //~Lectura();
    String sensorId;
    unsigned long timestamp;
    float valor;
};

#endif
