#include <Arduino.h>
#include <ML8511.h>

#include "SHT85.h"
#include "Plantower_PMS7003.h"

#define I2C_ADDRESS       0x44
#define ML8511_ANALOGPIN     A0
#define MKES12_PIN           A1

SHT85 sht;
ML8511 ml8511(ML8511_ANALOGPIN);
Plantower_PMS7003 pms7003 = Plantower_PMS7003();

void getHumidTemp()
{ 
  sht.read();
  
  float temp = sht.getTemperature();
  float humid = sht.getHumidity();

  Serial.print("humidity:");
  Serial.print(humid,4);
  Serial.print("%\t");

  Serial.print("temperature:");
  Serial.print(temp,4);
  Serial.println("℃");
}

void getUVData()
{
  float UV = ml8511.getUV();

  Serial.print("UV index:");
  Serial.print(UV,4);
  Serial.println("mW cm^2"); 
}

void getPM_2_5()
{
  int PM_2_5 = pms7003.getPM_2_5();

  Serial.print("PM2.5:");
  Serial.println(PM_2_5);
}

void getRainWater()
{
  int RainWater = analogRead(MKES12_PIN);
  
  Serial.println(RainWater);
}

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  
  sht.begin(I2C_ADDRESS);
  ml8511.enable();
}

void loop() 
{
  delay(2000);
}
