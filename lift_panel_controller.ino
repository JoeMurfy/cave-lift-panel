#include <Bounce2.h>

/*
  Script Name: Fiorella's Cave Lift Panel Script
  Author: Joe Murphy
  Date: 9/05/2023
*/


// ----------------- SECTION 1 -----------------------//
// How many switches in Section 1
#define NUM_S1 7
// Assign pin numbers. Section LED will always be the pin after these. i.e. 9.
const uint8_t SWITCHES_PINS_S1[NUM_S1] = { 2, 3, 4, 5, 6, 7, 8 };
const uint8_t SWITCHES_LED_PINS_S1 = 39;

const int LED_S1 = 9;

int ledStateS1 = LOW;

Bounce* switchesS1 = new Bounce[NUM_S1];
// ---------------------------------------------------//

// ----------------- SECTION 2 -----------------------//
// How many switches in Section 2
#define NUM_S2 4
// Assign pin numbers.
const uint8_t SWITCHES_PINS_S2[NUM_S2] = { 10, 11, 12, 13 };

const int LED_S2 = 14;

int ledStateS2 = LOW;

Bounce* switchesS2 = new Bounce[NUM_S2];
// ---------------------------------------------------//

// ----------------- SECTION 3 -----------------------//
// How many switches in Section 3
#define NUM_S3 8
// Assign pin numbers.
const uint8_t SWITCHES_PINS_S3[NUM_S3] = { 15, 16, 17, 18, 19, 20, 21, 22 };
const uint8_t SWITCHES_LED_PINS_S3 = 40;

const int LED_S3 = 23;

int ledStateS3 = LOW;

Bounce* switchesS3 = new Bounce[NUM_S3];
// ---------------------------------------------------//

// ----------------- SECTION 4 -----------------------//
// How many switches in Section 4
#define NUM_S4 2
// Assign pin numbers.
const uint8_t SWITCHES_PINS_S4[NUM_S4] = { 24, 25 };

const int LED_S4 = 26;

int ledStateS4 = LOW;

Bounce* switchesS4 = new Bounce[NUM_S4];
// ---------------------------------------------------//

// ----------------- SECTION 5 -----------------------//
// How many switches in Section 5 including final override (pin 31).
#define NUM_S5 5
// Assign pin numbers.
const uint8_t SWITCHES_PINS_S5[NUM_S5] = { 27, 28, 29, 30, 31 };
const uint8_t SWITCHES_LED_PINS_S5 = 41;

// Buzzer stuff. Not vital but nice for cues to the games master.
const int BUZZER_S5 = 32;

unsigned long lastPeriodStart;
const int onDuration = 1000;
const int periodDuration = 6000;

Bounce* switchesS5 = new Bounce[NUM_S5];
// ---------------------------------------------------//

// ----------------- ROCKER SWITCH -------------------//
#define ROCKER_LED_NUM 4

const int ROCKER_DOWN_PIN = 33;
const int ROCKER_UP_PIN = 34;

const int ROCKER_LED_PINS[ROCKER_LED_NUM] = { 35, 36, 37, 38 };  // Pins for LEDs

int currentLed = 0;  // Variable to store the index of the currently lit LED

Bounce rockerUp = Bounce(ROCKER_DOWN_PIN, 10);  // Debounce object for increment button
Bounce rockerDown = Bounce(ROCKER_UP_PIN, 10);  // Debounce object for decrement button
// ---------------------------------------------------//


void setup() {

  for (int i = 0; i < NUM_S1; i++) {
    switchesS1[i].attach(SWITCHES_PINS_S1[i], INPUT_PULLUP);  //setup the bounce instance for the 1st section
    switchesS1[i].interval(25);                               // interval in ms
  }

  pinMode(SWITCHES_LED_PINS_S1, OUTPUT);  //setup leds for the 1st section
  digitalWrite(SWITCHES_LED_PINS_S1, LOW);


  for (int i = 0; i < NUM_S2; i++) {
    switchesS2[i].attach(SWITCHES_PINS_S2[i], INPUT_PULLUP);  //setup the bounce instance for the 2nd section
    switchesS2[i].interval(25);                               // interval in ms
  }

  for (int i = 0; i < NUM_S3; i++) {
    switchesS3[i].attach(SWITCHES_PINS_S3[i], INPUT_PULLUP);  //setup the bounce instance for the 3rd section
    switchesS3[i].interval(25);                               // interval in ms
  }

  pinMode(SWITCHES_LED_PINS_S3, OUTPUT);  //setup leds for the 1st section
  digitalWrite(SWITCHES_LED_PINS_S3, LOW);

  for (int i = 0; i < NUM_S4; i++) {
    switchesS4[i].attach(SWITCHES_PINS_S4[i], INPUT_PULLUP);  //setup the bounce instance for the 4th section
    switchesS4[i].interval(25);                               // interval in ms
  }

  for (int i = 0; i < NUM_S5; i++) {
    switchesS5[i].attach(SWITCHES_PINS_S5[i], INPUT_PULLUP);  //setup the bounce instance for the 4th section
    switchesS5[i].interval(25);                               // interval in ms
  }
  
  pinMode(SWITCHES_LED_PINS_S5, OUTPUT);  //setup leds for the 1st section
  digitalWrite(SWITCHES_LED_PINS_S5, LOW);

  // Setup Rocker and LEDs
  pinMode(ROCKER_DOWN_PIN, INPUT_PULLUP);
  pinMode(ROCKER_UP_PIN, INPUT_PULLUP);

  for (int i = 0; i < ROCKER_LED_NUM; i++) {
    pinMode(ROCKER_LED_PINS[i], OUTPUT);
    digitalWrite(ROCKER_LED_PINS[i], LOW);  // Initially turn off all LEDs
  }

  //Setup the Section LEDs
  pinMode(LED_S1, OUTPUT);
  digitalWrite(LED_S1, LOW);

  pinMode(LED_S2, OUTPUT);
  digitalWrite(LED_S2, LOW);

  pinMode(LED_S3, OUTPUT);
  digitalWrite(LED_S3, LOW);

  pinMode(LED_S4, OUTPUT);
  digitalWrite(LED_S4, LOW);


  Serial.begin(9600);
}

void loop() {

  // ------------ Section 1 Logic ------------ //
  
  bool needToToggleLedS1 = true;

  digitalWrite(SWITCHES_LED_PINS_S1, LOW);

  for (int i = 0; i < NUM_S1; i++) {

    // Update the Bounce instance :
    switchesS1[i].update();
    // If it fell, flag the need to toggle the LED
    if (switchesS1[i].fell()) {
      needToToggleLedS1 = true;
      Serial.println(i);
    }
  }

  // Check switch states
  for (int i = 0; i < NUM_S1; i++) {
    // If any of the required switches are off, exit loop
    if (((i == 0 || i == 3 || i == 5) && !switchesS1[i].read()) ||           // Required switches off
        ((i == 1 || i == 2 || i == 4 || i == 6) && switchesS1[i].read())) {  // Required switches on
      needToToggleLedS1 = false;
      break;
    }
  }

  // Turn on/off LED based on condition
  if (needToToggleLedS1) {
    digitalWrite(LED_S1, HIGH);  // Turn on LED
    // Serial.println("Section 1 Complete");
    digitalWrite(SWITCHES_LED_PINS_S1, HIGH);
  } else {
    digitalWrite(LED_S1, LOW);  // Turn off LED
  }

  digitalWrite(SWITCHES_LED_PINS_S1, HIGH);

  // ----------------------------------------- //

  // ------------ Section 2 Logic ------------ //

  bool needToToggleLedS2 = true;

  for (int i = 0; i < NUM_S2; i++) {
    // Update the Bounce instance :
    switchesS2[i].update();
    // If it fell, flag the need to toggle the LED
    if (switchesS2[i].fell()) {
      needToToggleLedS2 = true;
           Serial.println(i);
    }
  }

  // Check switch states
  for (int i = 0; i < NUM_S2; i++) {
    // If any of the required switches are off, exit loop
    if ((i == 0 || i == 1 || i == 2 || i == 3) && switchesS2[i].read()) {
      needToToggleLedS2 = false;
      break;
    }
  }

  // Turn on/off LED based on condition
  if (needToToggleLedS2) {
    digitalWrite(LED_S2, HIGH);  // Turn on LED
    // Serial.println("Section 2 complete.");
  } else {
    digitalWrite(LED_S2, LOW);  // Turn off LED
  }

  // ----------------------------------------- //

  // ------------ Section 3 Logic ------------ //

  bool needToToggleLedS3 = true;

  digitalWrite(SWITCHES_LED_PINS_S3, LOW);

  for (int i = 0; i < NUM_S3; i++) {
    // Update the Bounce instance :
    switchesS3[i].update();
    // If it fell, flag the need to toggle the LED
    if (switchesS3[i].fell()) {
      needToToggleLedS3 = true;
      Serial.println(i);
    }
  }

  // Check switch states
  for (int i = 0; i < NUM_S3; i++) {
    // If any of the required switches are off, exit loop
    if (((i == 0 || i == 1 || i == 4 || i == 5 || i == 6) && !switchesS3[i].read()) ||  // Required switches off
        ((i == 2 || i == 3 || i == 7) && switchesS3[i].read())) {                       // Required switches on
      needToToggleLedS3 = false;
      break;
    }
  }

  // Turn on/off LED based on condition
  if (needToToggleLedS3) {
    digitalWrite(LED_S3, HIGH);  // Turn on LED
    digitalWrite(SWITCHES_LED_PINS_S3, HIGH);
  } else {
    digitalWrite(LED_S3, LOW);  // Turn off LED
  }

  digitalWrite(SWITCHES_LED_PINS_S3, HIGH);

  // ----------------------------------------- //

  // ------------ Section 4 Logic ------------ //

  bool needToToggleLedS4 = true;

  for (int i = 0; i < NUM_S4; i++) {
    // Update the Bounce instance :
    switchesS4[i].update();
    // If it fell, flag the need to toggle the LED
    if (switchesS4[i].fell()) {
      needToToggleLedS4 = true;
      Serial.println(i);
    }
  }

  // Check switch states
  for (int i = 0; i < NUM_S4; i++) {
    // If any of the required switches are off, exit loop
    if ((i == 0 || i == 1) && switchesS4[i].read()) {
      needToToggleLedS4 = false;
      break;
    }
  }

  // Turn on/off LED based on condition
  if (needToToggleLedS4) {
    digitalWrite(LED_S4, HIGH);  // Turn on LED
  } else {
    digitalWrite(LED_S4, LOW);  // Turn off LED
  }

  // ----------------------------------------- //

  // ------------ Rocker Logic --------------- //
  // Update the state of the buttons
  rockerUp.update();
  rockerDown.update();

  // Check if the increment button is pressed and released
  if (rockerUp.fell()) {
    incrementLed();
  }

  // Check if the decrement button is pressed and released
  if (rockerDown.fell()) {
    decrementLed();
  }
  // ----------------------------------------- //

  // ------------ Section 5 Logic ------------ //
  bool needToToggleBuzzerS5 = true;
  // ON OFF ON ON
  // 0   1   2  3
  for (int i = 0; i < NUM_S5; i++) {
    // Update the Bounce instance :
    switchesS5[i].update();
    // If it fell, flag the need to toggle the LED
    if (switchesS5[i].fell()) {
      needToToggleBuzzerS5 = true;
      //      Serial.println(i);
    }
  }

  // Check switch states
  for (int i = 0; i < NUM_S5; i++) {
    // If any of the required switches are off, exit loop
    if (((i == 1) && !switchesS5[i].read()) ||                               // Required switches off
        ((i == 0 || i == 2 || i == 3 || i == 4) && switchesS5[i].read())) {  // Required switches on
      needToToggleBuzzerS5 = false;
      break;
    }
  }

  // Turn on/off buzzer based on condition
  // TODO: Could possibly check if all other sections were complete using their booleans
  if (needToToggleBuzzerS5) {
    if (millis() - lastPeriodStart >= periodDuration) {
      lastPeriodStart += periodDuration;
      tone(BUZZER_S5, 550, onDuration);  // play 550 Hz tone in background for 'onDuration'
    }
  }
  // ----------------------------------------- //
}


// ----- Incremental LED Functions -------- //
void incrementLed() {
  if (currentLed < ROCKER_LED_NUM - 1) {
    currentLed++;
    digitalWrite(ROCKER_LED_PINS[currentLed], HIGH);
  }
}

void decrementLed() {
  if (currentLed >= 0) {
    digitalWrite(ROCKER_LED_PINS[currentLed], LOW);
    currentLed--;
  }
}
// ----------------------------------------- //
