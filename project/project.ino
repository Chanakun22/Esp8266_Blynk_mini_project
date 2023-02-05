
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLtGsgYw0Y"
#define BLYNK_DEVICE_NAME "Chanakun Project"


#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define APP_DEBUG
///e
/////////Fire base//////////
int LED_PIN = D0;
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include "BlynkEdgent.h"
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


 
bool t = true;
bool state = false;
WidgetLED led1(V7);
#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"


BlynkTimer timer; 

PZEM004Tv30 pzem(D5, D6);



BLYNK_CONNECTED() {
  lcd.begin();
  lcd.backlight();
}



BLYNK_WRITE(V3){
  int value = param.asInt();
  // digitalWrite(D0,!value)
  digitalWrite(LED_PIN,!value);
  digitalWrite(D4,!value);
}






void setup()
{
    
  timer.setInterval(2000L,readsensor);
  Serial.begin(115200);
  delay(100);
  pinMode(LED_PIN,OUTPUT);
  pinMode(D4,OUTPUT);
  BlynkEdgent.begin();
  


}




void readsensor(){
  

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
        // Blynk.virtualWrite(V7, 0);
        led1.setColor(BLYNK_RED);
        if(t){
          t=false;
          lcd.clear();
          lcd.setCursor(5,1);
          lcd.print("Sensor Eror");
          Blynk.virtualWrite(V0, 0);
          Blynk.virtualWrite(V1, 0);
          Blynk.virtualWrite(V2, 0);
          Blynk.virtualWrite(V5, 0);
          Blynk.virtualWrite(V6, 0);
        }
        
    } else if (isnan(current)) {
          Blynk.logEvent("alert", "Error reading current");
        // Blynk.virtualWrite(V7, 0);
        led1.setColor(BLYNK_RED);
        if(t){
          t=false;
          lcd.clear();
          lcd.setCursor(5,1);
          lcd.print("Sensor Eror");
          Blynk.virtualWrite(V0, 0);
          Blynk.virtualWrite(V1, 0);
          Blynk.virtualWrite(V2, 0);
          Blynk.virtualWrite(V5, 0);
          Blynk.virtualWrite(V6, 0);
        }
    } else if (isnan(power)) {
          Blynk.logEvent("alert", "Error reading current");
        // Blynk.virtualWrite(V7, 0);
        led1.setColor(BLYNK_RED);
        if(t){
          t=false;
          lcd.clear();
          lcd.setCursor(5,1);
          lcd.print("Sensor Eror");
          Blynk.virtualWrite(V0, 0);
          Blynk.virtualWrite(V1, 0);
          Blynk.virtualWrite(V2, 0);
          Blynk.virtualWrite(V5, 0);
          Blynk.virtualWrite(V6, 0);
        }
    } else if (isnan(energy)) {
          Blynk.logEvent("alert", "Error reading current");
        // Blynk.virtualWrite(V7, 0);
        led1.setColor(BLYNK_RED);
        if(t){
          t=false;
          lcd.clear();
          lcd.setCursor(5,1);
          lcd.print("Sensor Eror");
          Blynk.virtualWrite(V0, 0);
          Blynk.virtualWrite(V1, 0);
          Blynk.virtualWrite(V2, 0);
          Blynk.virtualWrite(V5, 0);
          Blynk.virtualWrite(V6, 0);
        }
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {
      t=true;
      // Blynk.virtualWrite(V7, 1);
      led1.setColor(BLYNK_GREEN);
      // Print the values to the Serial console
      Blynk.virtualWrite(V0, voltage);
      Blynk.virtualWrite(V1, current);
      Blynk.virtualWrite(V2, power);
      Blynk.virtualWrite(V5, energy);
      Blynk.virtualWrite(V6, frequency);
      lcd.setCursor(0,0);
      lcd.print("Vlotage: "+String(voltage)+" V ");
      lcd.setCursor(0,1);
      lcd.print("Current: "+String(current)+" A  ");
      lcd.setCursor(0,2);
      lcd.print("Power:   "+String(power)+" W  ");
      lcd.setCursor(0,3);
      lcd.print("energy:  "+String(energy)+" Kwh  ");
      // Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
      //  Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
      //  Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
      // Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
      //  Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
      //  Serial.print("PF: ");           Serial.println(pf);
    }
}



void loop() {
  BlynkEdgent.run();
  timer.run();
}









