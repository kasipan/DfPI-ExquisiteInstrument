#include <SharpDistSensor.h>

int sensorValue;
int distance;
int sensorID = 2;   // 1:center 2:right 3:left
int prevDist, prevDist2;
const int THRESHOLD = 70;

// Analog pin to which the sensor is connected
const byte sensorPin = A0;

// Window size of the median filter (odd number, 1 = no filtering)
const byte medianFilterWindowSize = 5;

// Create an object instance of the SharpDistSensor class
SharpDistSensor sensor(sensorPin, medianFilterWindowSize);

void setup() {
  Serial.begin(9600);

  // Set sensor model
  sensor.setModel(SharpDistSensor::GP2Y0A710K0F_5V_DS);
}

void loop() {
  // Get distance from sensor
  unsigned int distance = round(sensor.getDist() / 10); // get as cm

  if ( abs(prevDist - distance) < THRESHOLD || abs(prevDist2 - distance) < THRESHOLD) {
    String postData = "{\"sensor\":";
    postData.concat(sensorID);
    postData.concat(", \"distance\":");
    postData.concat(distance);
    postData.concat("}");

    Serial.println(postData);
  }

  prevDist2 = prevDist;
  prevDist = distance;

  delay(200);
}
