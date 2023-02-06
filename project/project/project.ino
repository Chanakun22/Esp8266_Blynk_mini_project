
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLtGsgYw0Y"
#define BLYNK_DEVICE_NAME "Chanakun Project"


#define BLYNK_FIRMWARE_VERSION        "0.1.5"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define APP_DEBUG
///e
/////////Fire base//////////
bool lcd_clear = false;
bool error_ = true;
bool lcd_switch = true;
float voltage;
float current;
float power;
float energy;
float frequency; 
float pf;
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
LiquidCrystal_I2C lcd(0x27, 16, 2);


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
  lcd.begin();
  lcd.backlight();
}









void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Connect Wifi..");
  timer.setInterval(2600L,readsensor);
  timer.setInterval(60000L,clearlcd);
  Serial.begin(115200);
  pinMode(D3,INPUT_PULLUP);
  BlynkEdgent.begin();
  lcd.createChar(0, customChar);
  


}


void clearlcd(){
  lcd_clear = true;
}




// void readsensor(){
  
//   if(lcd_clear){
//     lcd_clear = false;
//     lcd.clear();
//   }
//         //Serial.print("Custom Address:");
//     // Serial.println(pzem.readAddress(), HEX);

//     // Read the data from the sensor
//     voltage = pzem.voltage();
//     current = pzem.current();
//     power = pzem.power();
//     energy = pzem.energy();
//     frequency = pzem.frequency();
//     pf = pzem.pf();

//     // Check if the data is valid
//     if(isnan(voltage) || isnan(current) || isnan(power) || isnan(energy) || isnan(frequency) || isnan(pf)){
//     Blynk.logEvent("alert", "Error reading sensor");
//         // Blynk.virtualWrite(V7, 0);
//         led1.setColor(BLYNK_RED);
//         if(t){
//           t=false;
//           error_ = true;
//           lcd.clear();
//           lcd.setCursor(0,1);
//           lcd.print("Error reading sensor");
//           Blynk.virtualWrite(V0, 0);
//           Blynk.virtualWrite(V1, 0);
//           Blynk.virtualWrite(V2, 0);
//           Blynk.virtualWrite(V5, 0);
//           Blynk.virtualWrite(V6, 0);
//         }
        
//     }
//      else {
//       if(error_){
//         error_ = false;
//         lcd.clear();
//       }
//       t=true;

//     }
// }


void readsensor(){
  lcd_switch = !lcd_switch;

    voltage = pzem.voltage();
    current = pzem.current();
    power = pzem.power();
    energy = pzem.energy();
    frequency = pzem.frequency();
    pf = pzem.pf();

    if(isnan(voltage) || isnan(current) || isnan(power) || isnan(energy) || isnan(frequency) || isnan(pf)){
    Blynk.logEvent("alert", "Error reading sensor");
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



          for(int j = 0; j < 16; j++){
          lcd.setCursor(j,1);
          lcd.write(0);
          delay(300);

        }
        for(int j = 0; j < 16; j++){
          lcd.setCursor(j,1);
          lcd.print(" ");
          delay(300);
        }
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
    if(lcd_switch){
      lcd.setCursor(0,0);
      lcd.print("V: "+String(voltage)+" V  ");
      lcd.setCursor(0,1);
      lcd.print("A: "+String(current)+" A     ");
    }
    else{
      lcd.setCursor(0,0);
      lcd.print("W: "+String(power)+" W  ");
      lcd.setCursor(0,1);
      lcd.print("Whr: "+String(energy)+" Whr   ");
    }
  }

}




void loop() {
  BlynkEdgent.run();
  timer.run();
}





