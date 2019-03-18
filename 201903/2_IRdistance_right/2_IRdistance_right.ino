int sensorValue;
int distance;
int sensorID = 2;   // 1:center 2:left 3:right
int prevDist;
const int THRESHOLD = 50;

void setup() {
  Serial.begin(9600);

}

void loop() {

  sensorValue = analogRead(0);
  if (sensorValue >= 280 && sensorValue <= 512)
  {
    distance = 28250 / (sensorValue - 229.5);

    if ( abs(prevDist - distance) < THRESHOLD ) {
      String postData = "{\"sensor\":";
      postData.concat(sensorID);
      postData.concat(", \"distance\":");
      postData.concat(distance);
      postData.concat("}");

      Serial.println(postData);
    }
    
    prevDist = distance;
  }
  delay(100);
}
