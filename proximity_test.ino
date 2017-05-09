// Pin setup
const int trigger_pin = 3;
const int echo_pin    = A0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9000);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sound_pulse();
}

void sound_pulse() {
  // Setting up timer for pulsing
  static unsigned long long previousmillisA = 0;
  unsigned long long currentmillisA = micros();

  // Setting up timer for determining when to pulse
  static unsigned long previousmillisB = 0;
  unsigned long currentmillisB = millis();
  static int state = HIGH;

  //Sending pulses
  if(currentmillisB - previousmillisB > 255 && state == HIGH) {
    // Setting up timers
    previousmillisB = millis();
    previousmillisA = micros();

    // Sending sound pulse
    digitalWrite(trigger_pin, state);
    state = !state;
  // Turning off speakers
  } else if(currentmillisA - previousmillisA > 10 && state == LOW) {
    // Turning off speakers
    digitalWrite(trigger_pin, state);
    digitalWrite(13, state);
    state = !state;
    
    // Printing data
    long duration = pulseIn(echo_pin, HIGH);
 
    // convert the time into a distance
    long cm = (duration/2) / 29.1;
    long inches = (duration/2) / 74; 
    
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
  }
}

