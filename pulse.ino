const int pulsePin = A0;       // Pulse sensor signal pin
const int RED = 12; // Optional LED pin to visualize the pulse
int buzzer=13;  //Buzzer Pin
int green=11;  //Green pin
int pulseValue;               // Raw analog value from the pulse sensor
int pulseThreshold =1000;    // Adjust this threshold according to your setup
bool pulseDetected = false;   // Flag to indicate pulse detection

unsigned long lastPulseTime = 0; // Time of the last pulse detected
unsigned int heartbeatCount = 0; // Total number of heartbeats counted
unsigned long heartbeatInterval = 0; // Time interval between consecutive heartbeats
unsigned long heartRateBPM = 0; // Heart rate in BPM

void setup() {
  Serial.begin(9600);
  pinMode(pulsePin, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  pulseValue = analogRead(pulsePin);
  int sensor=analogRead(A4);
  

  if(sensor>=280)
  {
    digitalWrite(buzzer,HIGH);
  }
  if(sensor<280)
  {
    digitalWrite(buzzer,LOW);
  }

  if (pulseValue > pulseThreshold && !pulseDetected) {
    pulseDetected = true;
    digitalWrite(RED, HIGH); // Turn on the LED when a pulse is detected
    unsigned long currentTime = millis();
    heartbeatInterval = currentTime - lastPulseTime;
    lastPulseTime = currentTime;
    
    if (heartbeatInterval > 0) {
      heartRateBPM = 60000 / heartbeatInterval; // Calculate BPM (60,000 ms = 60 seconds)
      heartbeatCount++; // Increment the heartbeat count

      Serial.print("Heart Rate: ");
      Serial.print(heartRateBPM);
      Serial.println(" BPM");
    }
  } 
  else if (pulseValue <500 && pulseValue>530) {
    pulseDetected = false;
    digitalWrite(RED, HIGH); // Turn off the LED when the pulse goes back to normal
  }
  else if(pulseValue>=475 && pulseValue<550)
  {
  
    digitalWrite(green, HIGH);// Turn on if heart beat is normal.
  }

 // Print the raw pulse sensor value
  Serial.print("Pulse value: ");
  Serial.println(pulseValue);

 

  delay(10); // Adjust the delay based on your sampling rate requirements
}
