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

struct SHT_sensor 
{
  float humid,temp;
};

SHT_sensor getHumidTemp()
{ 
  sht.read();

  SHT_sensor humidTemp;
  
  humidTemp.temp = sht.getTemperature();
  humidTemp.humid = sht.getHumidity();

  return humidTemp;
}

float getUVData()
{
  float UV = ml8511.getUV();
  return UV;
}

int getPM_2_5()
{
  int PM_2_5 = pms7003.getPM_2_5();
  return PM_2_5;
}

int getRainWater()
{
  int rainWater = analogRead(MKES12_PIN);
  return rainWater;
}

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  
  sht.begin(I2C_ADDRESS);
  ml8511.enable();
}

void printData(SHT_sensor humidTemp, int PM_2_5, int rainWater, float UV)
{ 
    Serial.print("PM2.5:");
    Serial.print(PM_2_5);
    Serial.println("μg/m3");
    
    Serial.print("UV index:");
    Serial.print(UV,4);
    Serial.println("mW cm^2");
     
    Serial.print("humidity:");
    Serial.print(humidTemp.humid,4);
    Serial.print("%\t");
  
    Serial.print("temperature:");
    Serial.print(humidTemp.temp,4);
    Serial.println("℃");
  
    Serial.print("Rain water:");
    Serial.println(rainWater);
}
void loop() 
{
    SHT_sensor humidTemp = getHumidTemp();
    int PM_2_5 = getPM_2_5;
    int rainWater = getRainWater();
    float UV = getUVData();
    
    printData(humidTemp,PM_2_5,rainWater,UV);
    delay(2000);
}
