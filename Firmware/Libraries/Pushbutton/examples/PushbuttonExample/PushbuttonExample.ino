#include <Pushbutton.h>

/* This example uses the Pushbutton library to demonstrate three
 * different methods for detecting a button press and release. It
 * blinks the yellow user LED on pin 13 each time the a button on
 * pin 12 is pressed and released.  A normally-open momentary
 * pushbutton should be connected between pin 12 and ground.  */

#define LED_PIN 13
#define BUTTON_PIN 12

/* Create a Pushbutton object with default settings, which
 * enables the internal pull-up on the pin and interprets a HIGH
 * pin value as the default (unpressed) state of the
 * button. (Optional arguments can be passed to the constructor
 * to specify other button types and connection methods; see the
 * documentation for details.) */
Pushbutton button(BUTTON_PIN);

void setup()
{
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  /* Method 1: Directly read the state of the button with the
   * isPressed() function. You must debounce the button yourself
   * with this method. */
  do
  {
    while (!button.isPressed());  // wait for button to be pressed
    delay(10);                    // debounce the button press
  }
  while (!button.isPressed());    // if button isn't still pressed, loop

  do
  {
    while (button.isPressed());   // wait for button to be released
    delay(10);                    // debounce the button release
  }
  while (button.isPressed());     // if button isn't still released, loop

  // blink LED
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);

  /* Method 2: Use the waitForButton() function, which blocks and
   * doesn't return until a button press and release are
   * detected. This function takes care of button debouncing. */
  button.waitForButton();

  // blink LED
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);

  /* Method 3: Call the getSingleDebouncedRelease() function
   * repeatedly in a loop, which returns true to report a single
   * button release or false otherwise. This function takes care
   * of button debouncing. If you have multiple buttons, you can
   * call getSingleDebouncedRelease() or
   * getSingleDebouncedPress() in a loop for all of them until
   * one of them returns true. */
  while (1)
  {
    if (button.getSingleDebouncedRelease())
    {
      // blink LED
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      break;
    }
  }
}
