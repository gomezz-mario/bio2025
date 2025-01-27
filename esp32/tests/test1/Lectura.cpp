#include "Lectura.h"

Lectura::Lectura(String sensorId, unsigned long timestamp, float valor)
    : sensorId(sensorId), timestamp(timestamp), valor(valor) {
    // Lista de inicialización para inicializar los miembros
}

// No es necesario definir el destructor si no hace nada