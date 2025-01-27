#include <FirebaseManager.h>

// Inicialización de la instancia estática
FirebaseManager *FirebaseManager::instance = nullptr;

// Constructor privado
FirebaseManager::FirebaseManager()
{
    Serial.println("FirebaseManager inicializado");
    // Inicializa cualquier recurso necesario aquí
}

// Destructor privado
FirebaseManager::~FirebaseManager()
{
  Serial.println("FirebaseManager deleted");
}

// Implementación de los métodos públicos
void FirebaseManager::autenticate()
{
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASS;
    fbdo.setBSSLBufferSize(4096, 1024);
    Firebase.begin(&config, &auth);
}

FirebaseJson FirebaseManager::getData(const String &nodo)
{
    FirebaseJson json;
    if (Firebase.RTDB.getJSON(&fbdo, nodo))
    {
        json = fbdo.to<FirebaseJson>();
        Serial.println(String("Data retrieved: ") + json.raw());
    }
    else
    {
        Serial.println("Failed to retrieve data: " + fbdo.errorReason());
    }
    return json;
}

bool FirebaseManager::setData(const String &nodo, FirebaseJson data) {
    // Intentamos establecer los datos JSON en el nodo especificado
    Serial.printf("Set json at %s... %s\n", nodo.c_str(),
      Firebase.RTDB.setJSON(&fbdo, nodo.c_str(), &data) ? "ok" : fbdo.errorReason().c_str());

    // Verificamos si los datos se han establecido correctamente en Firebase
    if (Firebase.RTDB.getJSON(&fbdo, nodo.c_str())) {
      Serial.printf("Get json from %s: %s\n", nodo.c_str(), fbdo.to<FirebaseJson>().raw());
      return true;
    } else {
      Serial.printf("Error getting json: %s\n", fbdo.errorReason().c_str());
      return false;
    }
}

bool FirebaseManager::isReady(){
  return Firebase.ready();
}
  


