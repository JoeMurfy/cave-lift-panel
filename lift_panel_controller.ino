// Script Name: Lift Panel Controller
// Author: Joe Murphy
// Date: 29/04/23

// Write an arduinio script that controls the LED's on a lift control panel. It will take multiple inputs
// from 5 different sections, these are as follows:
// Section 1: 7 Switches with their own LED.
// Section 2: 4 Rotary Encoders
// Section 3: 8 Rocker Switches with their own LEDs.
// Section 4: 2 Rotary Encoders.
// Section 5: 4 LEDs indicating which sections are completed, 4 Switches with their own LED's.
// LED Level: Rocker switch with 4 LED Lights.

// After each section is completed correctly the corresonding LED in section 5 will light.

// Constants for storing pin numbers for arduino.
const int SECTION_1_PIN = 2;
const int SECTION_2_PIN = 3;
const int SECTION_3_PIN = 4;
const int SECTION_4_PIN = 5;

const int LED_1_PIN = 6;
const int LED_2_PIN = 7;
const int LED_3_PIN = 8;
const int LED_4_PIN = 9;

const int ROCKER_SWITCH_UP_PIN = 10;
const int ROCKER_SWITCH_DOWN_PIN = 11;
const int LED_LEVEL_1_PIN = 12;
const int LED_LEVEL_2_PIN = 13;
const int LED_LEVEL_3_PIN = 14;
const int LED_LEVEL_4_PIN = 15;

// Variables to store the current and previous states of the rocker switch
int rockerSwitchUpState = HIGH;
int lastRockerSwitchUpState = HIGH;
int rockerSwitchDownState = HIGH;
int lastRockerSwitchDownState = HIGH;
unsigned long lastDebounceTimeRocker = 0;

// The current LED level for incrementing and decrementing.
int currentLevel = 0;

// Variables to store the current and previous states of each button
int section1State = HIGH;
int section2State = HIGH;
int section3State = HIGH;
int section4State = HIGH;

int lastSection1State = HIGH;
int lastSection2State = HIGH;
int lastSection3State = HIGH;
int lastSection4State = HIGH;

// Variables to store the time of the last button state change - These are numbered 1-4 for each section (each of the sections effectively acts as a button/switch).
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;

// The debounce delay in milliseconds - ADJUST THIS IF READINGS ARE BEING DODGY!
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(SECTION_1_PIN, INPUT_PULLUP);
  pinMode(SECTION_2_PIN, INPUT_PULLUP);
  pinMode(SECTION_3_PIN, INPUT_PULLUP);
  pinMode(SECTION_4_PIN, INPUT_PULLUP);

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);

  pinMode(ROCKER_SWITCH_UP_PIN, INPUT_PULLUP);
  pinMode(ROCKER_SWITCH_DOWN_PIN, INPUT_PULLUP);
  pinMode(LED_LEVEL_1_PIN, OUTPUT);
  pinMode(LED_LEVEL_2_PIN, OUTPUT);
  pinMode(LED_LEVEL_3_PIN, OUTPUT);
  pinMode(LED_LEVEL_4_PIN, OUTPUT);
}

void loop() {
  // Read the state of each button
  int section1Reading = digitalRead(SECTION_1_PIN);
  int section2Reading = digitalRead(SECTION_2_PIN);
  int section3Reading = digitalRead(SECTION_3_PIN);
  int section4Reading = digitalRead(SECTION_4_PIN);

  // Read the state of the rocker switch
  int rockerSwitchUpReading = digitalRead(ROCKER_SWITCH_UP_PIN);
  int rockerSwitchDownReading = digitalRead(ROCKER_SWITCH_DOWN_PIN);


  // Check if the button 1 state has changed
  if (section1Reading != lastSection1State) {
    lastDebounceTime1 = millis();
  }

  // Check if the button 2 state has changed
  if (section2Reading != lastSection2State) {
    lastDebounceTime2 = millis();
  }

  // Check if the button 3 state has changed
  if (section3Reading != lastSection3State) {
    lastDebounceTime3 = millis();
  }

  // Check if the button 4 state has changed
  if (section4Reading != lastSection4State) {
    lastDebounceTime4 = millis();
  }

  // Check if the debounce delay has passed for button 1
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // Update the button state and turn on the LED if the button is pressed
    if (section1Reading != section1State) {
      section1State = section1Reading;
      if (section1State == LOW) {
        digitalWrite(LED_1_PIN, HIGH);
      }
    }
  }

  // Check if the debounce delay has passed for button 2
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // Update the button state and turn on the LED if the button is pressed
    if (section2Reading != section2State) {
      section2State = section2Reading;
      if (section2State == LOW) {
        digitalWrite(LED_2_PIN, HIGH);
      }
    }
  }

  // Check if the debounce delay has passed for button 3
  if ((millis() - lastDebounceTime3) > debounceDelay) {
    // Update the button state and turn on the LED if the button is pressed
    if (section3Reading != section3State) {
      section3State = section3Reading;
      if (section3State == LOW) {
        digitalWrite(LED_3_PIN, HIGH);
      }
    }
  }

  // Check if the debounce delay has passed for button 4
  if ((millis() - lastDebounceTime4) > debounceDelay) {
    // Update the button state and turn on the LED if the button is pressed
    if (section4Reading != section4State) {
      section4State = section4Reading;
      if (section4State == LOW) {
        digitalWrite(LED_4_PIN, HIGH);
      }
    }
  }

  // Check if the rocker switch state has changed
  if (rockerSwitchUpReading != lastRockerSwitchUpState) {
    if (millis() - lastDebounceTimeRocker > debounceDelay) {
      // Update the rocker switch up state and toggle the LED level
      lastRockerSwitchUpState = rockerSwitchUpReading;
      if (rockerSwitchUpReading == LOW) {
        // If the rocker switch is pressed up, turn on the next LED in sequence
        currentLevel = min(currentLevel + 1, 4);
      }
      // Update the LED level indicator
      digitalWrite(LED_LEVEL_1_PIN, currentLevel >= 1);
      digitalWrite(LED_LEVEL_2_PIN, currentLevel >= 2);
      digitalWrite(LED_LEVEL_3_PIN, currentLevel >= 3);
      digitalWrite(LED_LEVEL_4_PIN, currentLevel >= 4);
    }
  }

  // Check if the rocker switch down state has changed
  if (rockerSwitchDownReading != lastRockerSwitchDownState) {
    if (millis() - lastDebounceTimeRocker > debounceDelay) {
      // Update the rocker switch state and toggle the LED level
      lastRockerSwitchDownState = rockerSwitchDownReading;
      if (rockerSwitchDownReading == LOW) {
        // If the rocker switch is pressed down, turn off the next LED in sequence
        currentLevel = max(currentLevel - 1, 0);
      }
      // Update the LED level indicator
      digitalWrite(LED_LEVEL_1_PIN, currentLevel >= 1);
      digitalWrite(LED_LEVEL_2_PIN, currentLevel >= 2);
      digitalWrite(LED_LEVEL_3_PIN, currentLevel >= 3);
      digitalWrite(LED_LEVEL_4_PIN, currentLevel >= 4);
    }
  }

  // Update the debounce time.
  lastDebounceTimeRocker = millis();
}
