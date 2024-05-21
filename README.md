# Single master - single slave I2C communication on PIC microcontroller
## PIC microcontroller that can be used
- PIC16F877
- PIC16F877A
- PIC16F887
## Task
- Utilize Special Function Registers (SFR), do not use built-in functions.
- When the button on RB7 pin of the Master is pressed, a 4-digit float is sent to the Slave from the Master.
- The Slave extracts two numbers after the decimal dot.
- When the button on RB6 pin of the Master is pressed, the Slave sends a new number with the numbers after the decimal dot are the two extracted numbers above.
## Simulation video:
- Link: https://drive.google.com/file/d/1KelWmSp5iTbTxtWb9Ep3Uhz1N2EVhra8/view?usp=sharing
