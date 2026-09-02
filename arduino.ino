#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
const int button = 8;
int buttonstate = 0;
bool buttonflip;
int frequency = 0;


const int S0 = A0;
const int S1 = A1;
const int S2 = A2;
const int S3 = A3;
const int sensorOut = A4;
const int OE = A5;

void setup() {

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);


  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 7, 6, 5, 4 }, SensorCount);
  Serial.begin(9600);
  Serial.print("Goon ");
  pinMode(button, INPUT);
}
void colour() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("R= ");      //printing name
  Serial.print(frequency);  //printing RED color frequency
  Serial.print("  ");
  delay(100);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("G= ");      //printing name
  Serial.print(frequency);  //printing Green color frequency
  Serial.print("  ");
  delay(100);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("B= ");      //printing name
  Serial.print(frequency);  //printing Blue color frequency
  Serial.println("  ");
  delay(1000);
}
void loop()

{

  buttonstate = digitalRead(button);
  if (buttonstate == HIGH) {

    buttonflip = !buttonflip;
    Serial.println("Button Pressed");
    delay(200);
  }
  if (buttonflip == true) {
    colour();
  }
  else{
    qtr.read(sensorValues);
     for (uint8_t i = 0; i < SensorCount; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
  }
  Serial.println();
  delay(500);
  }
  
  
}
