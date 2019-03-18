int servoPin = A1;

int pVal = 500;
unsigned long previousMillis = 0; //used for timer
boolean increasePulse = true;
int spd = 10; //speed of increment or decrement on sweep
int minPulse = 300;
int maxPulse = 2000;
int interval = 10; // fixed value of pulsing servos



// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode (servoPin, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);


  unsigned long currentMillis = millis(); //get time in milliseconds

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis ;
    if (distance < 50) {
      sweep(spd);
      pulse(pVal);


    }
  }
}


void pulse (int p) {
  // constrain to minimum and maximum pulse

  digitalWrite(servoPin, HIGH);
  
  delayMicroseconds(p);
  digitalWrite(servoPin, LOW);

}

void sweep(int spd) {
  if (increasePulse) {

    pVal += spd;

    if (pVal >= maxPulse) {
      increasePulse = false;
    }

  } else {
    pVal -= spd;

    if (pVal <= minPulse) {
      increasePulse = true;

    }

  }

}
