# Cytron Maker Sumo Library
This is Arduino Library for Cytron Maker Mini Sumo Controller (MAKER-MSUMO).<br>
Examples for sumo robot are included.
<br><br><br>

## Installation
1. Open the Arduino IDE, select `Sketch` -> `Include Library` -> `Manage Libraries...`.
2. Search for `Cytron Maker Sumo Library`.
3. Click `Install` to install the library.
4. Restart the Arduino IDE.
5. Examples can be opened in Arduino IDE from `File` -> `Examples` -> `Cytron Maker Sumo Library`.
<br><br><br>

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
