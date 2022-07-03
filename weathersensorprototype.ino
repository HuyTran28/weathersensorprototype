#include <Arduino.h>
#include <ML8511.h>

#include "SHT85.h"
#include "Plantower_PMS7003.h"

#define I2C_ADDRESS       0x44
#define ML8511_ANALOGPIN     A0

SHT85 sht;
ML8511 ml8511(ML8511_ANALOGPIN);
Plantower_PMS7003 pms7003 = Plantower_PMS7003();

struct SHT_sensor
{
    float temp, humid;
};

SHT_sensor getHumidTemp()
{ 
  sht.read();
  
  SHT_sensor shtData;
  shtData.temp = sht.getTemperature();
  shtData.humid = sht.getHumidity();
  return shtData;
}

float getUVData()
{
  float UVData = ml8511.getUV();
  return UVData; 
}

void setup() {
  sht.begin(I2C_ADDRESS);
  light.enable();
}

void loop() {
  
}
