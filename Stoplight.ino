/* ABOUT
  - Green light on when program is run. Countdown timer displays an "X".
  - On button push, lights cycle to yellow, then red. After cycle, timer counts down for crosswalk. When timer is close to expiration, buzzer sounds for audible warning.
  - At "0", countodwn changes to an X, and lught cycles back to green. 
*/

/* NOTES
  - ButtonHandler is a debounced button handler. Due to finicky input without an actual button press, ButtonHandler will compare the duration of a raw input validButtonPressDelay.
      Should the duration be >= validButtonPressDelay, the input will be accepted and isPushed is returned true, else returned false.  
  - digitPins and digitLED reffer to the countdown timer. Each pin is associated to one line that makes up a the number. digitLED contains the on/off state of each pin in the order
    they occure in digitPins. Displaying the "X" is contained within the function.
*/

const int digitPins[7] = {
  22,  // L-TOP                           _____  < TOP
  3,   // TOP                            |     |  < R-TOP
  1,   // R-TOP                  L-TOP > |     |
  23,  // MIDDLE                          _____  < MIDDLE
  21,  // L-BOTTOM                       |     |   < R-BOTTOM
  19,  // BOTTOM               L-BOTTOM >|     |
  18   // R-BOTTOM                        _____ < BOTTOM
};

const int digitLED[11][7] = {
  {0, 0, 0, 0, 0, 0, 0},  // OFF
  {1, 1, 1, 0, 1, 1, 1},  // 0
  {0, 0, 1, 0, 0, 0, 1},  // 1
  {0, 1, 1, 1, 1, 1, 0},  // 2
  {0, 1, 1, 1, 0, 1, 1},  // 3
  {1, 0, 1, 1, 0, 0, 1},  // 4
  {1, 1, 0, 1, 0, 1, 1},  // 5
  {1, 1, 0, 1, 1, 1, 1},  // 6
  {0, 1, 1, 0, 0, 0, 1},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 0, 1}   // 9
};

// Stoplight Pins
const int pinRedLED = 13;
const int pinYellowLED = 12;
const int pinGreenLED = 14;

// Button Pins
const int pinButton = 27;

// Buzzer Pins
const int pinBuzzer = 15;

// Button Press Validation
const unsigned long validButtonPressDelay = 30;
bool lastRawState = HIGH;
bool stableState = HIGH;
unsigned long buttonPressTime = 0;

void setup() {

  Serial.begin(115200);

  // Stoplight LEDs
  pinMode(pinRedLED, OUTPUT);
  pinMode(pinYellowLED, OUTPUT);
  pinMode(pinGreenLED, OUTPUT);

  // Button
  pinMode(pinButton, INPUT_PULLUP);

  // countdown
  for (int i = 0; i < 7; i++) {
    pinMode(digitPins[i], OUTPUT);
  }

  // Buzzer
  pinMode(pinBuzzer, OUTPUT);

  delay(1000);
  Serial.println("Booting...");

  clearStopLights();
}

void loop() {
  bool isPressed = buttonHandler();

  !isPressed ? go() : stop();
  
}

void clearStopLights() {
  digitalWrite(pinRedLED, LOW);
  digitalWrite(pinYellowLED, LOW);
  digitalWrite(pinGreenLED, LOW);
}

void go() {
  //clear stoplight
  clearStopLights();

  //display X on crosswalk countdown
  displayXOnCountdown();

  //green light
  digitalWrite(pinGreenLED, HIGH);
}

void stop() {
  // yellow light
  clearStopLights();
  digitalWrite(pinYellowLED, HIGH);
  delay(3000);

  // red light
  clearStopLights();
  digitalWrite(pinRedLED, HIGH);

  // countdown timer
  delay(1000);
  for (int num = 10; num >= 0; num--) {
    displayCountdownNumber(num);
    delay(1000);
    if (num < 5) {
      beep();
    }
  }
  displayXOnCountdown();
  delay(1000);

}

bool buttonHandler() {

  bool isPressed = false;
  bool rawState = digitalRead(pinButton);

  if (rawState != lastRawState) {
    buttonPressTime = millis();
    lastRawState = rawState;
  }

  if ((millis() - buttonPressTime) > validButtonPressDelay) {
    if (stableState != rawState) {
      stableState = rawState;
      if (stableState == LOW) {
        Serial.println("PRESSED");
        isPressed = true;
      } else {
        Serial.println("RELEASED");
        isPressed = false;
      }
    }
  }
  return isPressed;
}

void displayCountdownNumber(int number) {

  // run through digitPins and digitLED to get pin number and on/off states for display LEDs
  for (int i = 0; i < 7; i++) {
    digitalWrite(digitPins[i], digitLED[number][i]);
  }
}

void displayXOnCountdown() {
  int xLEDDisplay[7] = {1, 0, 1, 1, 1, 0, 1};

  for (int i = 0; i < 7; i++) {
    digitalWrite(digitPins[i], xLEDDisplay[i]);
  }
}

void beep() {
  digitalWrite(pinBuzzer, HIGH);
  delay(200);
  digitalWrite(pinBuzzer, LOW);
}



