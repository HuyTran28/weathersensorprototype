#include <Arduino.h>
#include <ML8511.h>

#include "SHT85.h"
#include "Plantower_PMS7003.h"

#define I2C_ADDRESS       0x44
#define ML8511_ANALOGPIN     A0

SHT85 sht;
ML8511 ml8511(ML8511_ANALOGPIN);
Plantower_PMS7003 pms7003 = Plantower_PMS7003();

void getHumidTemp()
{ 
  sht.read();
  
  float temp = sht.getTemperature();
  float humid = sht.getHumidity();
  
  Serial.print(humid,4);
  Serial.print("%\t");
  Serial.print(temp,4);
  Serial.println("℃");
}

void getUVData()
{
  float UV = ml8511.getUV();
  
  Serial.print(UV,4);
  Serial.println("mW cm^2"); 
}

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  
  sht.begin(I2C_ADDRESS);
  ml8511.enable();
}

void loop() 
{
  getHumidTemp();
  getUVData();
  delay(2000);
}
