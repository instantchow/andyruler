
/*
* Totall-E-sp Sonar Sensor Test
*
* 
*/

  // Hardware Defines
  
  // defines pins numbers
  // note, do not use 36-39 on esp32
  const int trigPin = 32;
  const int echoPin = 35;
  const int relayPin = 33;
  // defines variables
  long duration;
  int distance;
  const unsigned long echoTimeout = 300000;
  

  
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(relayPin, OUTPUT); // Sets the relayPin as an Output


}

void loop() {

  // TODO: set millis() and loop with consistant timing
  
  // Ping! always takes about 12 Ms
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH, echoTimeout);
  // Calculating the distance (cm)
  distance = duration*0.034/2;

  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10)
  {
    // turn on
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    //turn off    
    digitalWrite(relayPin, LOW);
  }
  
  delay(200);
  
}
