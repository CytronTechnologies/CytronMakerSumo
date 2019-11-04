/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example calibrates the edge sensors if the START button is pressed during
 * power up / reset.
 * The sensor threshold is then printed via serial port and LED is turned on
 * whenever edge is detected.
 * 
 * To calibrate the edge sensors:
 * 1. Press and hold the START button.
 * 2. Power up / reset the controller.
 * 3. Release the START button after the buzzer beeps.
 * 4. LED will blink during sensor calibration.
 * 5. Sweep both edge sensors across the white edge and black background to get
 *    the minimum and maximum value.
 * 6. Press and release the START button once calibration is done. Sensors'
 *    threshold will be calculated automatically.
 * 
 * The sensor calibration data is saved in EEPROM. The data will still be
 * there even thought the controller has been powered off.
 * 
 *
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/

#include <EEPROM.h>
#include "CytronMakerSumo.h"



// Note and duration for Super Mario melody.
int melodyPitch[] = {NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5};
int melodyDuration[] = {10, 10, 10, 10, 10, 10, 10, 10, 10};

// Note and duration for edge sensor calibration.
int calPitch[] = {NOTE_C5, NOTE_G5};
int calDuration[] = {10, 10};



void setup() {
  Serial.begin(115200);
  MakerSumo.begin();

  
  // Enter edge sensor calibration mode if the START button is pressed
  // during reset.
  if (digitalRead(START) == LOW) {
    // Beep to indicate we are in the calibration mode.
    MakerSumo.playMelody(calPitch, calDuration, 2);

    // Wait until start button is released.
    while ((digitalRead(START) == LOW));
    delay(100);

    // Calibrate the edge sensors.
    MakerSumo.calibrateEdgeSensors(); 
  }

  
  // Play the Super Mario melody once.
  MakerSumo.playMelody(melodyPitch, melodyDuration, 9);
}



void loop() {
  // Turn on LED if edge is detected.
  if (MakerSumo.isEdgeDetected(EDGE_L) || MakerSumo.isEdgeDetected(EDGE_R)) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }

  // Print the sensors' threshold via serial port.
  Serial.print ("Left: ");
  Serial.print (MakerSumo.readEdgeSensorThreshold(EDGE_L));
  Serial.print ("    Right: ");
  Serial.println (MakerSumo.readEdgeSensorThreshold(EDGE_R));

  delay(250);
}
