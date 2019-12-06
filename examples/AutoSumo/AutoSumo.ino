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



// Edge Sensor Threshold.
#define EDGE_L_THRESHOLD  720
#define EDGE_R_THRESHOLD  638

// Constants for direction.
#define LEFT    0
#define RIGHT   1



// Searching direction.
int searchDir = LEFT;

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
  MakerSumo.playMelody(melodyPitch, melodyDuration, 9);

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
  if (analogRead(EDGE_L) < EDGE_L_THRESHOLD) {
    // Back off and make a U-Turn to the right.
    backoff(RIGHT);

    // Toggle the search direction.
    searchDir ^= 1;
  }
  
  // Edge is detected on the right.
  else if (analogRead(EDGE_R) < EDGE_R_THRESHOLD) {
    // Back off and make a U-Turn to the left.
    backoff(LEFT);
    
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
 *******************************************************************************/
void search(int dir) {
  // Move in circular motion.
  if (dir == LEFT) {
    MakerSumo.setMotorSpeed(MOTOR_L, 60);
    MakerSumo.setMotorSpeed(MOTOR_R, 80);
  } else {
    MakerSumo.setMotorSpeed(MOTOR_L, 80);
    MakerSumo.setMotorSpeed(MOTOR_R, 60);
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
 *******************************************************************************/
void backoff(int dir) {
  // Reverse
  MakerSumo.setMotorSpeed(MOTOR_L, -50);
  MakerSumo.setMotorSpeed(MOTOR_R, -50);
  delay(300);

  // Rotate..
  if (dir == LEFT) {
    // Rotate left backward.
    MakerSumo.setMotorSpeed(MOTOR_L, -50);
    MakerSumo.setMotorSpeed(MOTOR_R, 50);
  } else {
    // Rotate right backward.
    MakerSumo.setMotorSpeed(MOTOR_L, 50);
    MakerSumo.setMotorSpeed(MOTOR_R, -50);
  }
  delay(600);

  // Stop the motors.
  MakerSumo.setMotorSpeed(MOTOR_L, 0);
  MakerSumo.setMotorSpeed(MOTOR_R, 0);
  delay(50);
}
