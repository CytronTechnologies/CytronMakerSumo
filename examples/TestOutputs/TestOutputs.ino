/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example test the motors, LED and servo of the Maker Mini Sumo Controller.
 *
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/

#include "CytronMakerSumo.h"



// Define note and duration for Super Mario melody.
int melodyPitch[] = {NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5};
int melodyDuration[] = {10, 10, 10, 10, 10, 10, 10, 10, 10};



void setup() {
  Serial.begin(115200);
  MakerSumo.begin();

  // Stop the robot.
  MakerSumo.stop();

  // Play the Super Mario melody once.
  MakerSumo.playMelody(melodyPitch, melodyDuration, 9);

  // Wait here until start button is pressed.
  while (digitalRead(START) == HIGH);
}



void loop() {
  // Turn on LED, set servo to 0 degree and move forward at 50% speed.
  digitalWrite(LED, HIGH);
  MakerSumo.setServoPosition(0);
  MakerSumo.moveForward(128);
  delay(1000);

  // Turn off LED, set servo to 90 degree and move backward at 50% speed.
  digitalWrite(LED, LOW);
  MakerSumo.setServoPosition(90);
  MakerSumo.moveBackward(128);
  delay(1000);

  // Turn on LED, set servo to 180 degree and turn left at 50% speed.
  digitalWrite(LED, HIGH);
  MakerSumo.setServoPosition(180);
  MakerSumo.turnLeft(128);
  delay(1000);

  // Turn off LED, set servo to 90 degree and turn right at 50% speed.
  digitalWrite(LED, LOW);
  MakerSumo.setServoPosition(90);
  MakerSumo.turnRight(128);
  delay(1000);
}
