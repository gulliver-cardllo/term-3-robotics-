#include <QTRSensors.h>



QTRSensors qtr;
const uint8_t SensorCount = 4;

uint16_t sensorValues[SensorCount];



void setup()

{
  qtr.setSensorPins((const uint8_t[]){4,5,6,7}, SensorCount);
  // configure the sensors

  qtr.setTypeRC();

  qtr.setSensorPins((const uint8_t[]){A0}, SensorCount);

  Serial.begin(9600);

}



void loop()

{

  // read raw sensor values

  qtr.read(sensorValues);



  // print the sensor values as numbers from 0 to 1023, where 0 means maximum

  // reflectance and 1023 means minimum reflectance

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();
  delay(250);
}
