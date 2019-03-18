#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <Servo.h>


// WiFi network informations
char ssid[] = "";           // network name
char password[] = "";   // network password
int status = WL_IDLE_STATUS;
unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back

WiFiUDP Udp;

Servo servoPinHead;
Servo servoPinBody;
int posH = 1500;  // initial mid position 
int posB = 1500;
unsigned long previousMillis = 0; //used for timer
boolean increasePulse = true;
int headSpd = 20; //speed of increment or decrement on sweep
int bodySpd = 10;
int minPulse = 1200;  // 1500-250;
int maxPulse = 1700;  // 1500+250;
float interval = 0.001; // fixed value of pulsing servos

// defines variables
long durationL;
float distanceL;
long durationR;
float distanceR;
bool turnRight;
bool turnLeft;



void setup() {
  // Setup Mortors --------------
  servoPinHead.attach(1);  // head
  servoPinBody.attach(0);  // body
  servoPinHead.writeMicroseconds(posH);   // initialise
  servoPinBody.writeMicroseconds(posB);

  Serial.begin(9600); // Starts the serial communication

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, password);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("Connected to wifi");
  // you're connected now, so print out the status:
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);


}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);


    // Rotating
    unsigned long currentMillis = millis(); //get time in milliseconds

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      if (String(packetBuffer) == "left") {
        increasePulse = true;
        sweep(headSpd);
        pulse(posH);
      } else if (String(packetBuffer) == "right") {
        increasePulse = false;
        sweep(headSpd);
        pulse(posH);
      }  else {
        // stay
      }
    }


    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}

//print the WiFi informations on the serial connection
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
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
}

void pulse(int p) {
  // constrain to minimum and maximum pulse
  servoPinHead.writeMicroseconds(posH);
  servoPinBody.writeMicroseconds(posB);

  delayMicroseconds(p);
}
