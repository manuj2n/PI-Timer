
const int cmdPiPin =  2;      // the number of the LED pin

// Variables will change:
int piState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 20;           // interval at which to blink (milliseconds)

void setup() {
  pinMode(cmdPiPin, OUTPUT);      
}

void loop()
{

  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > (interval * 1000)) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;

    // if the PI is off turn it on and vice-versa:
    if (piState == LOW)
      piState = HIGH;
    else
      piState = LOW;

    // set the PI with the ledState of the variable:
    digitalWrite(cmdPiPin, piState);
  }
}
