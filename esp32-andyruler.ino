
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
  float distance;
  const unsigned long echoTimeout = 300000;

  int state = 0;
  float handPos = 99.0;
  float prevHandPos = 0.0;
  float moveThres = 1.4;
  

void setup() {
  // put your setup code here, to run once:u
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(relayPin, OUTPUT); // Sets the relayPin as an Output
}


void loop() {


  
  // TODO: set millis() and loop with consistant timing

  switch (state)
  {
    //
    // IDLE STATE
    //
    case 0:
    {
      Serial.println((String)"Idle State: " + handPos);
      
      // did i move?
      if (abs(prevHandPos - handPos) > moveThres)
      {
        Serial.println((String)"Idle State to Moved, prevHandPos, new handPos: " + prevHandPos+" "+handPos);
        prevHandPos = handPos;
        state = 1;
      } 
      break;
    }
    
    //
    // MOVED STATE
    //
    case 1:
    {
      // i got moved state
      Serial.println((String)"Moved State: " + handPos);
      state = 2;
      break;
    }
  
    //
    // BUMP POS STATE
    //
    case 2:
    {
      Serial.println((String)"Bump State: " + handPos);
      
      // xtra bump me brah state
      digitalWrite(relayPin, HIGH);
      delay(2000);
      digitalWrite(relayPin, LOW);
      
      prevHandPos = getAvgDistance(3);
      Serial.println((String)"Bump  State setting prevHandPos: " + prevHandPos);
      
      // go back to idle
      state = 0;
      break;
    }
  
    //
    // EOL STATE
    //
    case 3:
    {
      Serial.println((String)"EOL State" + handPos);
      // end of the line
      // dont do anything until you get back home
      break;
    }
    default:
    {
      Serial.println("unexpected state");
      break;
    }
  }  

  handPos = getAvgDistance(3);
 
  delay(1500);

}


float getAvgDistance(int readings)
{
  float retval = -1.0;
  int i = 0;
  int distSum = 0;
  
  // gets two or some more distance values from the sonar and returns the 
  // avg of the readings
  for (i = 0; i < readings; i ++)
  {
    //read the distance
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
    distSum += distance;
    delayMicroseconds(1000);
  }

  retval = (float) distSum / readings;
    
  return retval;
}
