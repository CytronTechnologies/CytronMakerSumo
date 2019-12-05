/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example is for the Autonomous Sumo Robot.
 * 
 *
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/

#include "CytronMakerSumo.h"


// Searching direction.
int searchDir = 0;

// Define note and duration for Super Mario melody.
int melodyPitch[] = {NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5};
int melodyDuration[] = {10, 10, 10, 10, 10, 10, 10, 10, 10};



/*******************************************************************************
 * Setup
 * This function runs once after reset.
 *******************************************************************************/
void setup() {
  MakerSumo.begin();

  // Play the Super Mario melody once.
  //MakerSumo.playMelody(melodyPitch, melodyDuration, 9);

  // Wait until start button is pressed and released.
  while (digitalRead(START));
  while (!digitalRead(START));

  // Turn on the User LED.
  digitalWrite(LED, HIGH);
  
  // Start routine..
  startRoutine();
}



/*******************************************************************************
 * Main program loop.
 *******************************************************************************/
void loop() {
  // Edge is detected on the left.
  if (analogRead(EDGE_L) < 720) {
    // Back off and make a U-Turn to the right.
    backoff(1);

    // Toggle the search direction.
    searchDir ^= 1;
  }
  
  // Edge is detected on the right.
  else if (analogRead(EDGE_R) < 638) {
    // Back off and make a U-Turn to the left.
    backoff(0);
    
    // Toggle the search direction.
    searchDir ^= 1;
  }

  // Edge is not detected.
  else {
    // Keep searching if opponent is not detected.
    if ( (digitalRead(OPP_FC) == HIGH) &&
         (digitalRead(OPP_FL) == HIGH) &&
         (digitalRead(OPP_FR) == HIGH) ) {
      search(searchDir);
    }
    
    // Attack if opponent is in view.
    else {
      attack();
    }
  }

  // Stop the robot if the button is pressed.
  if (digitalRead(START) == 0) {
    // Stop the motors.
    MakerSumo.setMotorSpeed(MOTOR_L, 0);
    MakerSumo.setMotorSpeed(MOTOR_R, 0);

    // Loop forever here.
    while (1);
  }

}



/*******************************************************************************
 * Start Routine
 * This function should be called once only when the game start.
 *******************************************************************************/
void startRoutine() {
  // Start delay.
  delay(1000);
  
  // Turn right around 45 degrees.
  MakerSumo.setMotorSpeed(MOTOR_L, 50);
  MakerSumo.setMotorSpeed(MOTOR_R, 0);
  delay(500);
  
  // Go straight.
  MakerSumo.setMotorSpeed(MOTOR_L, 80);
  MakerSumo.setMotorSpeed(MOTOR_R, 80);
  delay(1500);
  
  // Turn left until opponent is detected.
  MakerSumo.setMotorSpeed(MOTOR_L, 0);
  MakerSumo.setMotorSpeed(MOTOR_R, 50);
  
  unsigned long startTimestamp = millis();
  while (digitalRead(OPP_FC)) {
    // Quit if opponent is not found after timeout.
    if (millis() - startTimestamp > 1000) {
      break;
    }
  }
}



/*******************************************************************************
 * Search
 * dir = 0 - Turn left.
 * dir = 1 - Turn right.
 *******************************************************************************/
void search(int dir) {
  // Move in circular motion.
  if (dir == 0) {
    MakerSumo.setMotorSpeed(MOTOR_L, 50);
    MakerSumo.setMotorSpeed(MOTOR_R, 80);
  } else {
    MakerSumo.setMotorSpeed(MOTOR_L, 80);
    MakerSumo.setMotorSpeed(MOTOR_R, 50);
  }
}



/*******************************************************************************
 * Attack
 * Track and attack the opponent in full speed.
 * Do nothing if opponent is not found.
 *******************************************************************************/
void attack() {
  // Opponent in front center.
  // Go straight in full speed.
  if (digitalRead(OPP_FC) == LOW) {
    MakerSumo.setMotorSpeed(MOTOR_L, 255);
    MakerSumo.setMotorSpeed(MOTOR_R, 255);
  }

  // Opponent in front left.
  // Turn left.
  else if (digitalRead(OPP_FL) == LOW) {
    MakerSumo.setMotorSpeed(MOTOR_L, 0);
    MakerSumo.setMotorSpeed(MOTOR_R, 255);
  }

  // Opponent in front right.
  // Turn right.
  else if (digitalRead(OPP_FR) == LOW) {
    MakerSumo.setMotorSpeed(MOTOR_L, 255);
    MakerSumo.setMotorSpeed(MOTOR_R, 0);
  }
}



/*******************************************************************************
 * Back Off
 * This function should be called when the ring edge is detected.
 * dir = 0 - Turn left.
 * dir = 1 - Turn right.
 *******************************************************************************/
void backoff(int dir) {
  // Stop the motors.
  MakerSumo.setMotorSpeed(MOTOR_L, 0);
  MakerSumo.setMotorSpeed(MOTOR_R, 0);
  delay(100);

  // Rotate..
  if (dir == 0) {
    // Rotate left backward.
    MakerSumo.setMotorSpeed(MOTOR_L, -80);
    MakerSumo.setMotorSpeed(MOTOR_R, 0);
  } else {
    // Rotate right backward.
    MakerSumo.setMotorSpeed(MOTOR_L, 0);
    MakerSumo.setMotorSpeed(MOTOR_R, -80);
  }
  delay(100);

  // Start looking for opponent.
  // Timeout after a short period.
  unsigned long uTurnTimestamp = millis();
  while (millis() - uTurnTimestamp < 500) {
    // Opponent is detected if either one of the opponent sensor is triggered.
    if ( (digitalRead(OPP_FC) == LOW) ||
         (digitalRead(OPP_FL) == LOW) ||
         (digitalRead(OPP_FR) == LOW) ) {
          
      // Stop the motors.
      MakerSumo.setMotorSpeed(MOTOR_L, 0);
      MakerSumo.setMotorSpeed(MOTOR_R, 0);
      delay(100);

      // Return to the main loop immediately and run the attack program.
      return;
    }
  }
}
