
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLtGsgYw0Y"
#define BLYNK_DEVICE_NAME "Chanakun Project"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
///
/////////Fire base//////////
int LED_PIN = D0;
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"


#include <FirebaseESP8266.h>


#define FIREBASE_HOST "projecy-31eb8-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_KEY "8rC32YDSJr5hJCDjIRk9CHvPpmXOAV5DvGXpHpmP"

bool t = true;
FirebaseData firebaseData;
bool state = false;

BLYNK_CONNECTED() {
  if(Firebase.getInt(firebaseData, "/state")) {
    int val = firebaseData.intData();
    Blynk.virtualWrite(V4, val);
    Blynk.virtualWrite(V3, val);
    digitalWrite(D0,!val);
  } 
  else {
    Serial.println("Error : " + firebaseData.errorReason());
  }
}



BLYNK_WRITE(V3){
  int value = param.asInt();
  // digitalWrite(D0,!value);
  Firebase.setInt(firebaseData, "/state", value);
  digitalWrite(D0,!value);
}




void setup()
{
  
  Serial.begin(115200);
  delay(100);
  pinMode(D0,OUTPUT);
  BlynkEdgent.begin();
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);



}









void loop() {
  BlynkEdgent.run();
    // state = !state;
    // if(Firebase.setInt(firebaseData, "/state", state)) {
    //     Serial.println("Added"); 
    // } else {
    //     Serial.println("Error : " + firebaseData.errorReason());
    // }

  if(Firebase.getInt(firebaseData, "/state")) {
    int val = firebaseData.intData();
    Blynk.virtualWrite(V4, val);
  } 
  else {
    Serial.println("Error : " + firebaseData.errorReason());
  }



}



