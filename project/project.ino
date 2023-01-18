
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
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

#if defined(ESP32)
    #error "Software Serial is not supported on the ESP32"
#endif

/* Use software serial for the PZEM
 * Pin 12 Rx (Connects to the Tx pin on the PZEM)
 * Pin 13 Tx (Connects to the Rx pin on the PZEM)
 e
*/ 
#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN D5
#define PZEM_TX_PIN D6
#endif
SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);
 
bool t = true;
FirebaseData firebaseData;
bool state = false;





BLYNK_CONNECTED() {
  if(Firebase.getInt(firebaseData, "/state/Status_blynk_ledV3")) {
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
  Firebase.setInt(firebaseData, "/state/Status_blynk_ledV3", value);
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

  if(Firebase.getInt(firebaseData, "/state/Status_blynk_ledV3")) {
    int val = firebaseData.intData();
    Blynk.virtualWrite(V4, val);
  } 
  else {
    Serial.println("Error : " + firebaseData.errorReason());
  }

    //Serial.print("Custom Address:");
    // Serial.println(pzem.readAddress(), HEX);

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        Blynk.logEvent("alert", "Error reading current");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {
      
      // Print the values to the Serial console
      Blynk.virtualWrite(V0, voltage);
      Blynk.virtualWrite(V1, current);
      Blynk.virtualWrite(V2, power);
      Blynk.virtualWrite(V5, energy);
      Blynk.virtualWrite(V6, frequency);
      // Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
      //  Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
      //  Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
      // Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
      //  Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
      //  Serial.print("PF: ");           Serial.println(pf);
    }



}



