# Cytron Maker Sumo Library
This is Arduino Library for Cytron Maker Mini Sumo Controller (MAKER-MSUMO).

---

## Installation
1. Open the Arduino IDE, select `Sketch` -> `Include Library` -> `Manage Libraries...`.
2. Search for `Cytron Maker Sumo Library`.
3. Click `Install` to install the library.
4. Restart the Arduino IDE.
5. Examples can be opened in Arduino IDE from `File` -> `Examples` -> `Cytron Maker Sumo Library`.

---

## Library Functions
These functions are provided in the library.
<br><br>

### MakerSumo.begin()
Initialize the I/O pins of the controller.<br>
Must be called once before using other library functions.

**Syntax:**<br>
`void MakerSumo.begin(void);`

**Parameters:**<br>
None

**Returns:**<br>
None

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
}
```
<br>


### MakerSumo.readDipSwitch()
Read the value of the DIP Switch.<br>
Each switch position represents 1 bit (SW1 = MSB, SW3 = LSB).

**Syntax:**<br>
`int MakerSumo.readDipSwitch(void);`

**Parameters:**<br>
None

**Returns:**<br>
Value of the DIP Switch (0 to 7).<br>
```
------------------------------------
| SW1 | SW2 | SW3 | Returned Value |
------------------------------------
|  0  |  0  |  0  |        0       |
------------------------------------
|  0  |  0  |  1  |        1       |
------------------------------------
|  0  |  1  |  0  |        2       |
------------------------------------
|  0  |  1  |  1  |        3       |
------------------------------------
|  1  |  0  |  0  |        4       |
------------------------------------
|  1  |  0  |  1  |        5       |
------------------------------------
|  1  |  1  |  0  |        6       |
------------------------------------
|  1  |  1  |  1  |        7       |
------------------------------------

*SW: 0 = OFF    1 = ON
```

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  Serial.begin(115200);
  
  int mode = MakerSumo.readDipSwitch();
  println(mode);
}
```
<br>

### MakerSumo.readBatteryVoltage()
Read the battery voltage.

**Syntax:**<br>
`float MakerSumo.readBatteryVoltage(void);`

**Parameters:**<br>
None

**Returns:**<br>
Battery voltage in volt.

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  Serial.begin(115200);
  
  float batteryVoltage = MakerSumo.readBatteryVoltage();
  println(batteryVoltage);
}
```
<br>

### MakerSumo.stop()
Stop the robot.

**Syntax:**<br>
`void MakerSumo.stop(void);`

**Parameters:**<br>
None

**Returns:**<br>
None

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  MakerSumo.stop();
}
```
<br>

### MakerSumo.moveForward()
Control the robot to move forward.<br>
Left motor rotates counter-clockwise.<br>
Right motor rotates clockwise.

**Syntax:**<br>
`void MakerSumo.moveForward(int speed);`

**Parameters:**<br>
- ***speed*** - How fast the robot moves (0 to 255).

**Returns:**<br>
None

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  MakerSumo.moveForward(128);
}
```
<br>

### MakerSumo.moveBackward()
Control the robot to move backward.<br>
Left motor rotates clockwise.<br>
Right motor rotates counter-clockwise.

**Syntax:**<br>
`void MakerSumo.moveBackward(int speed);`

**Parameters:**<br>
- ***speed*** - How fast the robot moves (0 to 255).

**Returns:**<br>
None

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  MakerSumo.moveBackward(128);
}
```
<br>

### MakerSumo.turnLeft()
Control the robot to turn left.<br>
Left motor and right motor rotate clockwise.

**Syntax:**<br>
`void MakerSumo.turnLeft(int speed);`

**Parameters:**<br>
- ***speed*** - How fast the robot turns (0 to 255).

**Returns:**<br>
None

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  MakerSumo.turnLeft(50);
}
```
<br>

### MakerSumo.turnRight()
Control the robot to turn right.<br>
Left motor and right motor rotate counter-clockwise.

**Syntax:**<br>
`void MakerSumo.turnRight(int speed);`

**Parameters:**<br>
- ***speed*** - How fast the robot turns (0 to 255).

**Returns:**<br>
None

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  MakerSumo.turnRight(50);
}
```
<br>

### MakerSumo.setServoPosition()
Control the servo position.

**Syntax:**<br>
`void MakerSumo.setServoPosition(int position);`

**Parameters:**<br>
- ***position*** - Servo position in degrees (0 to 180).

**Returns:**<br>
None

**Example Code:**<br>
```
void setup() {
  MakerSumo.begin();
  MakerSumo.setServoPosition(90);
}
```
<br>

### MakerSumo.playMelody()
Play melody through the piezo buzzer.<br>
Only return after finish playing.<br>
This function is modified from Arduino Example - toneMelody.

**Syntax:**<br>
`void MakerSumo.playMelody(const int *pitch, const int *duration, int length);`

**Parameters:**<br>
- ***pitch*** - Array of notes in the melody.
- ***duration*** - Array of duration for each notes (4 = quarter note, 8 = eighth note, etc).
- ***length*** - Number of notes in the melody.

**Returns:**<br>
None

**Example Code:**<br>
```
// Note in the melody:
int melodyPitch[] = {NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int melodyDuration[] = {10, 10, 10, 10, 10, 10, 10, 10, 10};

void setup() {
  MakerSumo.begin();
  MakerSumo.playMelody(melodyPitch, melodyDuration, 9);
}
```
<br>

---

## Predefined Constants
These constants are predefined in the library.

#### I/O Pins Assignment:
```
PWM_L
PWM_R
DIR_L
DIR_R

LED
SERVO
BUZZER

OPP_FC
OPP_FL
OPP_FR
OPP_L
OPP_R

START
GPIO1
GPIO2

EDGE_L
EDGE_R

POT
MODE
VBATT
```

#### Melody Notes:
```
NOTE_B0,
NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1,
NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2,
NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7,
NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8
```
