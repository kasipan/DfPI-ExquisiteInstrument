int sensorValue;
int distance;
int sensorID = 1;   // 1:center 2:left 3:right
const int THRESHOLD = 70;
int prevDist,prevDist2; // also used as initial value 

void setup() {
  Serial.begin(9600);

}

void loop() {

  sensorValue = analogRead(A0);
  if (sensorValue >= 280 && sensorValue <= 512)
  {
    distance = 28250 / (sensorValue - 229.5);

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
  }
  delay(100);
}
