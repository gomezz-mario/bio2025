#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#define DATABASE_URL "https://generador-de-cembf-default-rtdb.firebaseio.com/"
#define USER_EMAIL "gomez.92m@gmail.com"
#define USER_PASS "iot2025"
#define API_KEY "AIzaSyC6ypJvVlf_kxqccUO0TS3S2neM5Mn6QTY"

#include <Arduino.h>
#include <Firebase_ESP_Client.h>

class FirebaseManager
{
private:
    // Constructor y destructor privados
    FirebaseManager();
    ~FirebaseManager();
    // Atributo para la instancia única
    static FirebaseManager *instance;

    // Atributos para manejar Firebase
    FirebaseAuth auth;
    FirebaseConfig config;
    FirebaseData fbdo;

public:
    static FirebaseManager* getInstance() {
      if (!instance) {
        instance = new FirebaseManager();
      }
      return instance;
    };
    static void destroyInstance() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    };
    void autenticate();
    bool isReady();
    FirebaseJson getData(const String &nodo);
    bool setData(const String &nodo, FirebaseJson data);
};

#endif