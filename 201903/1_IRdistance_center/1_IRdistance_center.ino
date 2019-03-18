int sensorValue;
int distance;
int sensorID = 1;

void setup() {
  Serial.begin(9600);

}

void loop() {

  sensorValue = analogRead(0);
  if (sensorValue >= 280 && sensorValue <= 512)
  {

    distance = 28250 / (sensorValue - 229.5);

    String postData = "{sensor:";
    postData.concat(sensorID);
    postData.concat(", Distance:");
    postData.concat(distance);
    postData.concat("}");

    Serial.println(postData);
  }
  delay(500);
}
