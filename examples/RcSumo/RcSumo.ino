/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example is for the Radio-Controlled (RC) Sumo Robot.
 * 2-Channel RC controller is needed (one for forward/reverse and one for
 * left/right).
 * LED will turn on when the robot is moving.
 * 
 * Connect the forward/reverse channel to GPIO1 and left/right channel to GPIO2.
 * Invert the channel in RC transmitter settings if the direction is reversed.
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



// Pins connected to RC receiver.
#define RC_SPEED          GPIO1
#define RC_STEERING       GPIO2

// Neutral value for RC pulse (microseconds).
#define NEUTRAL_SPEED     1470
#define NEUTRAL_STEERING  1470

// Range for RC pulse (microseconds).
// Full down/left to full up/right.
#define RANGE_SPEED       1000
#define RANGE_STEERING    1000


// Define note and duration for Super Mario melody.
int melodyPitch[] = {NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5};
int melodyDuration[] = {10, 10, 10, 10, 10, 10, 10, 10, 10};



void setup() {
  Serial.begin(115200);
  MakerSumo.begin();

  // Set the pins for RC receiver as input with pulled up.
  pinMode(RC_SPEED, INPUT_PULLUP);
  pinMode(RC_STEERING, INPUT_PULLUP);

  // Stop the robot.
  MakerSumo.stop();

  // Play the Super Mario melody once.
  MakerSumo.playMelody(melodyPitch, melodyDuration, 9);
}



void loop() {
  // Read the speed channel from RC receiver.
  int speedPulse = pulseIn(RC_SPEED, HIGH, 100000);

  // Stop the robot if no pulse is received.
  if (speedPulse == 0) {
    digitalWrite(LED, LOW);
    MakerSumo.stop();
    return;
  }

  // Convert the pulse width to percentage (-1.0 to 1.0).
  float speedPercent = (float)(speedPulse - NEUTRAL_SPEED) / (float)(RANGE_SPEED / 2);
  speedPercent = constrain(speedPercent, -1.0f, 1.0f);

  // Add in dead band.
  if ((speedPercent > -0.1f) && (speedPercent < 0.1f)) {
    speedPercent = 0.0f;
  }


  
  // Read the steering channel from RC receiver.
  int steeringPulse = pulseIn(RC_STEERING, HIGH, 100000);

  // Stop the robot if no pulse is received.
  if (steeringPulse == 0) {
    digitalWrite(LED, LOW);
    MakerSumo.stop();
    return;
  }

  // Convert the pulse width to percentage (-1.0 to 1.0).
  float steeringPercent = (float)(steeringPulse - NEUTRAL_STEERING) / (float)(RANGE_STEERING / 2);
  steeringPercent = constrain(steeringPercent, -1.0f, 1.0f);

  // Add in dead band.
  if ((steeringPercent > -0.1f) && (steeringPercent < 0.1f)) {
    steeringPercent = 0.0f;
  }
  


  // Mix speed and steering together for left and right motor speed.
  float leftSpeedPercent = speedPercent + steeringPercent;
  int leftSpeed = (int)(leftSpeedPercent * 255.0f);
  leftSpeed = constrain(leftSpeed, -255, 255);

  float rightSpeedPercent = speedPercent - steeringPercent;
  int rightSpeed = (int)(rightSpeedPercent * 255.0f);
  rightSpeed = constrain(rightSpeed, -255, 255);

  // Set the speed for each motor.
  MakerSumo.setMotorSpeed(MOTOR_L, leftSpeed);
  MakerSumo.setMotorSpeed(MOTOR_R, rightSpeed);

  // Turn on LED if the speed is not 0.
  if ((leftSpeed != 0) || (rightSpeed != 0)) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}
