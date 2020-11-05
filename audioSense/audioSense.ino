
// These constants won't change. They're used to give names to the pins used:
const int audioInPin = A0;  // Analog input pin that the potentiometer is attached to
const int ledPin = 7; 
const int relayPin = 8;

int inputValue = 0;        // value read from the pot
int timeout = 0;        
bool active = false;      // True if there's audio input, false otherwise

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Read analog value from the audio-in
  inputValue = analogRead(audioInPin);
  // Serial.println(inputValue); // Commented out so the serial isn't just always running

  // If our read value is above the threshold, reset the timer
  if(inputValue > 20){
    timeout = 1500;
  }else if(timeout > 0){
    // Tick down the if the input is below the threshold, and if it's above 0
    timeout--;
  }

  if(timeout > 0){ // Active state
    // Timeout > 0 means that we either just saw audio, or we are waiting to time out
    if(active == false){
      // If we were previously inactive, turn on the LED and activate the relay
      digitalWrite(ledPin,HIGH);
      digitalWrite(relayPin,LOW);
    }
    // Set the active flag
    active = true;
  }else{    // Inactive state
    if(active == true){
      // If we were previously active, turn off the LED and disable the relay
      digitalWrite(ledPin,LOW);
      digitalWrite(relayPin,HIGH);
      // This delay is here because when the relay disables the stereo, there is some
      // back EMF that would be detected and would erroneously re-enable the stereo.
      // The delay halts the micro while we wait for the stereo to turn off completely.
      // This isn't ideal because if the audio signal starts up while we're waiting we'll
      // miss it. Ideally this would be done with an interrupt, but this works fine and
      // I'm too lazy to make it work
      delay(4000);
    }
    active = false;
  }
  
  // wait
  delay(20);
}
