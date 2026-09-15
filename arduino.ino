#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
const int button = 8;
int buttonstate = 0;
bool buttonflip;
int frequency = 0;

const int In1 = 9;
const int In2 = 10;
const int In3 = 11;
const int In4 = 12;
const int S0 = A0;
const int S1 = A1;
const int S2 = A2;
const int S3 = A3;
const int sensorOut = A4;
const int OE = A5;

void setup() {
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
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
  // Red Colour Code
  Serial.print("R= ");      
  Serial.print(frequency); 
  Serial.print("  ");
  delay(100);
  // Green Colour Code
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("G= ");      
  Serial.print(frequency);  
  Serial.print("  ");
  delay(100);
  // Blue Colour Code
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("B= ");      
  Serial.print(frequency);  
  Serial.println("  ");
  delay(1000);
}

void loop() {
  
  sensorfunc();
  buttonstate = digitalRead(button);
  if (buttonstate == HIGH) {

    buttonflip = !buttonflip;
    Serial.println("Button Pressed");
    delay(200);
  }
  // toggling between the line sensor array and the colour sensor
  if (buttonflip == true) {
    colour();
  } else {
    qtr.read(sensorValues);
    for (uint8_t i = 0; i < SensorCount; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }
    Serial.println();
    delay(500);
  }
}

void sensorfunc() {

  // this code can be updated to use the built in location function in qtr
  uint16_t position = qtr.readLineBlack(sensorValues);
  Serial.println(position);

  if (sensorValues[0] + sensorValues[1] >= 3000) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    Serial.print("MOVING TO THE LOEFT");
  } else if (sensorValues[1] + sensorValues[2] >= 3000) {
    digitalWrite(In3, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In1, HIGH);
    digitalWrite(In4, LOW);
    Serial.print("MOVING TO THE forward");
  } else if (sensorValues[2] + sensorValues[3] >= 3000) {
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    Serial.print("MOVING TO THE RIGHT");
  } else if (sensorValues[1] + sensorValues[2] + sensorValues[3] + sensorValues[0] >= 6000) {
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    Serial.print("MOVING TO THE NO");
  }
}
