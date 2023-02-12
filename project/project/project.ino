
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLtGsgYw0Y"
#define BLYNK_DEVICE_NAME "Chanakun Project"


#define BLYNK_FIRMWARE_VERSION        "0.1.8"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define APP_DEBUG
///e
/////////Fire base//////////
bool error_ = true;
int limit_amp;
float voltage;
float current;
float power;
float energy;
float frequency; 
float pf;
int relay = D8; 
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "BlynkEdgent.h"
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
PZEM004Tv30 pzem(D5, D6);
LiquidCrystal_I2C lcd(0x27, 20, 4);


/* Use software serial for the PZEM
 * Pin 12 Rx (Connects to the Tx pin on the PZEM)
 * Pin 13 Tx (Connects to the Rx pin on the PZEM)
 e
*/ 
byte customChar[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

 
bool t = true;
bool state = false;
WidgetLED led1(V7);
#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"


BlynkTimer timer; 




BLYNK_CONNECTED() {
  lcd.clear();
  Blynk.virtualWrite(V8, 0);
}


BLYNK_WRITE(V8){
  limit_amp = param.asInt();
}




BLYNK_WRITE(V4){
  int val =  param.asInt();
  digitalWrite(relay,val);
}



void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  pinMode(relay,OUTPUT);
  lcd.print("Connect Wifi..");
  timer.setInterval(1500L,readsensor);
  Serial.begin(115200);
  pinMode(D3,INPUT_PULLUP);
  BlynkEdgent.begin();
  lcd.createChar(0, customChar);
  


}







void readsensor(){

    voltage = pzem.voltage();
    current = pzem.current();
    power = pzem.power();
    energy = pzem.energy();
    frequency = pzem.frequency();
    pf = pzem.pf();

    if(isnan(voltage) || isnan(current) || isnan(power) || isnan(energy) || isnan(frequency) || isnan(pf)){
    Blynk.logEvent("alert", "Error reading sensor");
    for(int j = 0; j < 20; j++){
          lcd.setCursor(0,0);
          lcd.print("Error Read");
          lcd.setCursor(j,1);
          lcd.write(0);
          delay(300);

        }
    for(int j = 0; j < 20; j++){
          lcd.setCursor(0,0);
          lcd.print("Error Read");
          lcd.setCursor(j,1);
          lcd.print(" ");
          delay(300);
        }
        led1.setColor(BLYNK_RED);

        if(t){
          t=false;
          error_ = true;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Error Read");
          Blynk.virtualWrite(V0, 0);
          Blynk.virtualWrite(V1, 0);
          Blynk.virtualWrite(V2, 0);
          Blynk.virtualWrite(V5, 0);
          Blynk.virtualWrite(V6, 0);




        }
  }
  else{
    t=true;
      Blynk.virtualWrite(V7, 1);
      led1.setColor(BLYNK_GREEN);
      Blynk.virtualWrite(V0, voltage);
      Blynk.virtualWrite(V1, current);
      Blynk.virtualWrite(V2, power);
      Blynk.virtualWrite(V5, energy);
      Blynk.virtualWrite(V6, frequency);
      lcd.setCursor(0,0);
      lcd.print("Voltage: "+String(voltage)+" V  ");
      lcd.setCursor(0,1);
      lcd.print("Current: "+String(current)+" A     ");
      lcd.setCursor(0,2);
      lcd.print("Power: "+String(power)+" W  ");
      lcd.setCursor(0,3);
      lcd.print("Energy: "+String(energy)+" kWh   ");
  }

}




void loop() {
  BlynkEdgent.run();
  timer.run();



  if(limit_amp > 0){
    if(current > limit_amp){
      digitalWrite(relay,LOW);
      Blynk.virtualWrite(V4, 0);
    }
  }
}





