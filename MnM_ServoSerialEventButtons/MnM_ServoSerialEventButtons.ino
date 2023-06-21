  /*
  Serial Event

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

#include <Servo.h>

//ezButton Library for Arduino
// This library is designed to make it easy to use push button, 
// momentary switches, toggle switch, magnetic contact switch (door sensor)..​. 
// It is easy to use for not only beginners but also experienced users.
#include <ezButton.h> //https://github.com/ArduinoGetStarted/button
ezButton button1(2);  // create Button object that attach to pin 2;
ezButton button2(3);  // create Button object that attach to pin 3;
// Servo control 
// create servo object to control a servo
Servo myservo;
int pos = 0;    // variable to store the servo position

// string received from the serial connection
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int nMnMs;
void setup() {
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button1.setCountMode(COUNT_FALLING);
  button2.setCountMode(COUNT_FALLING);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // initialize serial:
  Serial.begin(9600);
  while (!Serial){
  };
  // lets matlab know it's ready
  Serial.println('1');
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first

  int btn1State = button1.getState();
  int btn2State = button2.getState();

  unsigned long btn1Count = button1.getCount();
  unsigned long btn2Count = button2.getCount();

  if(button1.isPressed()){
    Serial.println("The button 1 is pressed");
    Serial.println(btn1Count);
  }
  if(button1.isReleased())
    Serial.println("The button 1 is released");

  if(button2.isPressed()){
    Serial.println("The button 2 is pressed");
    Serial.println(btn2Count);
  }

  if(button2.isReleased())
    Serial.println("The button 2 is released");
    
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);                       // wait for a second
//    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    // trigger servo the required # of times
    nMnMs = inputString.toInt();
    cycleServo();
    inputString = "";
    stringComplete = false;
  }
  
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void cycleServo(){
  int ii = 0;
  for (ii = 0; ii<nMnMs; ii++){
    for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(4);                       // waits 15ms for the servo to reach the position
    }
    delay(500);
    for (pos = 120; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(4);                       // waits 15ms for the servo to reach the position
    }
  }
}
