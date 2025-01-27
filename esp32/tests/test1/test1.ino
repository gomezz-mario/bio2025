#include <Arduino.h>
#include <ConexionWifi.h>
#include <FirebaseManager.h>
#include <Firebase_ESP_Client.h>
#include <Lectura.h>

ConexionWifi conexion = ConexionWifi();
FirebaseManager* fb = FirebaseManager::getInstance();

Lectura lecturas[15] = {
  Lectura("temp1", 1633072800, 25.4),
  Lectura("temp1", 1633072860, 24.9),
  Lectura("temp1", 1633072920, 24.2),
  Lectura("temp1", 1633072980, 23.9),
  Lectura("temp1", 1633073040, 23.8),
  Lectura("temp1", 1633073100, 23.2),
  Lectura("temp1", 1633073160, 22.9),
  Lectura("temp1", 1633073220, 22.1),
  Lectura("temp1", 1633073280, 19.7),
  Lectura("temp1", 1633073340, 19.8),
  Lectura("temp1", 1633073400, 20.0),
  Lectura("temp1", 1633073460, 20.1),
  Lectura("temp1", 1633073520, 20.2),
  Lectura("temp1", 1633073580, 20.1),
  Lectura("temp1", 1633073640, 20.2)
};

int n = 0; // Iniciar desde 0 para recorrer el array

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  // Conectar a WiFi
  conexion.conectar();
  delay(2000);
  while (!conexion.isConectado()) {
    Serial.println("Reconectando...");
    conexion.conectar();
    delay(1000);
  }
  digitalWrite(LED_BUILTIN, HIGH);

  // Autenticar en Firebase
  fb->autenticate();
  while (!fb->isReady()) {
    Serial.println("Esperando inicialización de Firebase...");
    delay(1000);
  }

  // Insertar datos en Firebase
  while (n < 15) {
    FirebaseJson data;
    // Agregar los valores de la lectura actual al JSON
    data.set("sensorId", lecturas[n].sensorId);
    data.set("timestamp", lecturas[n].timestamp);
    data.set("valor", lecturas[n].valor);

    // Generar un identificador único para cada lectura
    String path = "Lecturas/lectura_" + String(n + 1);
    
    // Intentar insertar los datos en Firebase
    if (fb->setData(path, data)) {
      Serial.println("Datos insertados correctamente");
    } else {
      Serial.println("No se pudo insertar los datos");
    }

    n++; // Pasar a la siguiente lectura
    delay(60000); // Esperar 1 minuto (60,000 ms)
  }
}

void loop() {
  // No es necesario hacer nada en el loop para este ejemplo
}
