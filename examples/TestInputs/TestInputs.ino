/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example read the inputs value of the Maker Mini Sumo Controller
 * and print it via serial port every 250ms.
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

  // Play the Super Mario melody once.
  MakerSumo.playMelody(melodyPitch, melodyDuration, 9);
}



void loop() {
  // Print value for Start Button.
  Serial.print("START:");
  Serial.print(digitalRead(START));

  
  // Print value for Opponent Sensors.
  Serial.print("  OPP_L:");
  Serial.print(digitalRead(OPP_L));

  Serial.print("  OPP_FL:");
  Serial.print(digitalRead(OPP_FL));

  Serial.print("  OPP_FC:");
  Serial.print(digitalRead(OPP_FC));

  Serial.print("  OPP_FR:");
  Serial.print(digitalRead(OPP_FR));

  Serial.print("  OPP_R:");
  Serial.print(digitalRead(OPP_R));
  
  
  // Print value for Edge Sensors (Analog).
  Serial.print("      EDGE_L:");
  Serial.print(analogRead(EDGE_L));

  Serial.print("  EDGE_R:");
  Serial.print(analogRead(EDGE_R));
  
  
  // Print value for Potentiometer
  Serial.print("  POT:");
  Serial.print(analogRead(POT));


  // Print value for DIP Switch Setting.
  Serial.print("      MODE:");
  Serial.print(MakerSumo.readDipSwitch());


  // Print value for Battery Voltage.
  Serial.print("  BATT:");
  Serial.print(MakerSumo.readBatteryVoltage());


  // Print line feed.
  Serial.println("");


  delay(250);
}
