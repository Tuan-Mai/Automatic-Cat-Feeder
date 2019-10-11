#include <Servo.h>


int buttonInput = 3;
int onOffButton = 4;
int onLight = 11;
int offLight = 12;
int manualFeedLight = 2;
bool isOnOff = false;

int initialState;
long initial_millis_held;    // How long the button was held (milliseconds)
long initial_secs_held;      // How long the button was held (seconds)
long initial_prev_secs_held; // How long the button was held in the previous check
byte initialPrevious = HIGH;
unsigned long initialFirstTime; // how long since the button was first pressed


int buttonState;         // Current state of the button
long millis_held;    // How long the button was held (milliseconds)
long secs_held;      // How long the button was held (seconds)
long prev_secs_held; // How long the button was held in the previous check
byte previous = HIGH;
unsigned long firstTime; // how long since the button was first pressed

Servo servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(manualFeedLight, OUTPUT);
  digitalWrite(manualFeedLight, LOW);

  pinMode(onLight, OUTPUT);
  digitalWrite(onLight, LOW);

  pinMode(offLight, OUTPUT);
  digitalWrite(offLight, HIGH);

  pinMode(buttonInput, INPUT);
  digitalWrite(buttonInput, HIGH);

  pinMode(onOffButton, INPUT);
  digitalWrite(onOffButton, HIGH);

  servo.attach (9);
  servo.write(0);
}

void loop() {

  initialState = digitalRead(onOffButton);

  if (initialState == LOW && initialPrevious == HIGH && (millis() - initialFirstTime) > 200)
  {
    initialFirstTime = millis();
  }

  initial_millis_held = (millis() - initialFirstTime);
  initial_secs_held = initial_millis_held / 1000;

  if (initial_millis_held > 50) {

    if (initialState == LOW && initial_secs_held > initial_prev_secs_held) {
      ledblink(1, 100, LED_BUILTIN); // Each second the button is held blink the indicator led
    }

    if (initialState == LOW && initial_secs_held >= 5) {
      isOnOff = true;
      //ledblink(5, 200, onOffLight);
      digitalWrite(offLight, LOW);
      digitalWrite(onLight, HIGH);
    }

    // check if the button was released since we last checked
    //    if (initialState == HIGH && initialPrevious == LOW) {
    //
    //      if (initial_secs_held >= 5) {
    //        isOnOff = true;
    //        //ledblink(5, 200, onOffLight);
    //        digitalWrite(offLight, LOW);
    //        digitalWrite(onLight, HIGH);
    //
    //      }

    while (isOnOff == true) {
      buttonState = digitalRead(buttonInput);
      //
      if (buttonState == LOW && previous == HIGH && (millis() - firstTime) > 200)
      {
        firstTime = millis();
      }
      //
      millis_held = (millis() - firstTime);
      secs_held = millis_held / 1000;

      if (millis_held > 50) {

        if (buttonState == LOW && secs_held > prev_secs_held) {
          ledblink(1, 100, LED_BUILTIN); // Each second the button is held blink the indicator led
        }

        if (buttonState == LOW && secs_held >= 2 && secs_held < 5) {
          feed();
        }
//
//        if (buttonState == LOW && initial_secs_held >= 5) {
//          isOnOff = false;
//          //ledblink(5, 200, onOffLight);
//          digitalWrite(offLight, HIGH);
//          digitalWrite(onLight, LOW);
//        }

        //                  if (secs_held >= 5) {
        //            isOnOff = false;
        //            //ledblink(5, 200, onOffLight);
        //            digitalWrite(onLight, LOW);
        //            digitalWrite(offLight, HIGH);
        //          }

        // check if the button was released since we last checked
        if (buttonState == HIGH && previous == LOW) {

          //Button held for 1-3 seconds
          //            if (secs_held >= 2 && secs_held < 5) {
          //              feed();
          //            }

//          if (secs_held >= 5) {
//            isOnOff = false;
//            //ledblink(5, 200, onOffLight);
//            digitalWrite(onLight, LOW);
//            digitalWrite(offLight, HIGH);
//          }
          //
          //            int buttonState = digitalRead(buttonInput);
          //            if (buttonState)
          //            {
          //              delay(3000);
          //              int buttonState = digitalRead(buttonInput);
          //              if (buttonState)
          //              {
          //                // feed the beasts
          //                feed();
          //              }
          //            }


          // ===============================================================================
        }
      }
      previous = buttonState;
      prev_secs_held = secs_held;
    }

  }

  initialPrevious = initialState;
  initial_prev_secs_held = initial_secs_held;

}

// Just a simple helper function to blink an led in various patterns
void ledblink(int times, int lengthms, int pinnum) {
  for (int x = 0; x < times; x++) {
    digitalWrite(pinnum, HIGH);
    delay (lengthms);
    digitalWrite(pinnum, LOW);
    delay(lengthms);
  }
}

void feed() {
  ledblink(3, 50, manualFeedLight);

  servo.write(100);
  delay(1500);

  servo.write(0);
  delay(1000);
}



