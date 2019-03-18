/*
 * for Triangle
 * 
 */
 
#include <Servo.h> 

Servo servoPinHead;
Servo servoPinBody;


int posH = 1500;
int posB = 1500;
unsigned long previousMillis = 0; //used for timer
boolean increasePulse = true;
int headSpd = 5; //speed of increment or decrement on sweep
int bodySpd = 2;
int minPulse = 1100;  // 500;
int maxPulse = 1900;  // 800;
float interval = 0.01; // fixed value of pulsing servos

// defines pins numbers
const int trigPin = 11;  // left
const int echoPin = 12;
const int trigPin2 = 5; // right
const int echoPin2 = 6;

// defines variables
long durationL;
float distanceL;
long durationR;
float distanceR;
bool turnRight;
bool turnLeft;

void setup() {
  servoPinHead.attach(A0);  // head
  servoPinBody.attach(A2);  // body
  servoPinHead.writeMicroseconds(posH);   // initialise
  servoPinBody.writeMicroseconds(posB);


  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

//  pinMode (servoPinHead, OUTPUT);
//  pinMode (servoPinBody, OUTPUT);
  
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
    if (distanceL < 20) {
//      turnRight = false;
//      turnLeft = true;
      increasePulse = true;
//      //pVal = 562;
      sweep(headSpd);
      pulse(posH);
        
    } else if (distanceR < 20) {
//      turnRight = true;
//      turnLeft = false;
      increasePulse = false;
//      //pVal = 0;
      sweep(headSpd);
      pulse(posH);
        
    }
  }
}



void sweep(int headSpd) {
  if (increasePulse) {
    // left
    if (posH < maxPulse) {
      posH += headSpd;
      posB += bodySpd;
    }
  } else {
    // right
    if (posH > minPulse) {
      posH -= headSpd;
      posB -= bodySpd;
    }
  }
  
//  if (pVal >= maxPulse || minPulse <= pVal) {
//    turnRight = false;
//    turnLeft = false;
//  }
}

void pulse (int p) {
  // constrain to minimum and maximum pulse
  servoPinHead.writeMicroseconds(posH);
  servoPinBody.writeMicroseconds(posB);

//  digitalWrite(servoPinHead, HIGH);
//  digitalWrite(servoPinBody, HIGH);

  delayMicroseconds(p);
//  digitalWrite(servoPinHead, LOW);
//  digitalWrite(servoPinBody, LOW);
}
