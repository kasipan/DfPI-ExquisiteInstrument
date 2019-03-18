int servoPinHead = A0;   // head
int servoPinBody = A2;   // body

int pVal = 1000;
unsigned long previousMillis = 0; //used for timer
boolean increasePulse = true;
int spd = 15; //speed of increment or decrement on sweep
int minPulse = 600;  // 500;
int maxPulse = 700;  // 800;
int interval = 20; // fixed value of pulsing servos

// defines pins numbers
const int trigPin2 = 5;
const int echoPin2 = 6;
const int trigPin = 11;
const int echoPin = 12;

// defines variables
long durationL;
float distanceL;
long durationR;
float distanceR;
bool turnRight;
bool turnLeft;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode (servoPinHead, OUTPUT);
  pinMode (servoPinBody, OUTPUT);
  
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
  durationL = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distanceL = durationL * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance left: ");
  Serial.println(distanceL);

  // ================ 2nd distance senser ====================
  //delayMicroseconds(8.5);  // aviod affection from 1st

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  durationR = pulseIn(echoPin2, HIGH);
  distanceR = durationR * 0.034 / 2;

  Serial.print("Distance right: ");
  Serial.println(distanceR);



  unsigned long currentMillis = millis(); //get time in milliseconds

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis ;
    if (distanceL < 30) {
      turnRight = false;
      turnLeft = true;
      increasePulse = true;
      //pVal = 562;
      sweep(spd);
      pulse(pVal);
    } else if (distanceR < 30) {
      turnRight = true;
      turnLeft = false;
      increasePulse = false;
      //pVal = 0;
      sweep(spd);
      pulse(pVal);
    }
  }
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
  
  if (pVal >= maxPulse || minPulse <= pVal) {
    turnRight = false;
    turnLeft = false;
  }
}

void pulse (int p) {
  // constrain to minimum and maximum pulse

  digitalWrite(servoPinHead, HIGH);
  digitalWrite(servoPinBody, HIGH);

  delayMicroseconds(p);
  digitalWrite(servoPinHead, LOW);
  digitalWrite(servoPinBody, LOW);
}
