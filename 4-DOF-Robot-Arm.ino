/* <<< How to control 4 DFO Robot Arm with Arduino using dual joystick shield >>>
   Material needed:
    1x Arduino Uno
    1x Arduino joystick shield
    4x SG-90 servo motors 180 degrees
    1x Robot arm assembly - usually sourced from Ali Express
    1x External power supply 5V/5A (or more amps)
    1x power supply 5V/1A for Arduino Uno
    Wires, connectors, etc.
Please don't ask me how to do it, you are on your own. I spent so much time making this thing work, and it should have been done in a few hours.
Few tips:
    pay attention to the motor position before you install it
    an external PSU is a must for servo motors, roughly for each servo motor you need 1A
    test each servo motor before installation
    all joints need to be adjusted, not too tight not too loose, if needed lubricate
    arm assembly instructions you can find anywhere on the internet
    https://github.com/stealthbyroot/4-DOF-Robot-Arm---Arduino
*/

#include <Servo.h>
Servo servo_x;  // base
Servo servo_y;  // right servo
Servo servo_z;  // left servo
Servo servo_grip;  // claw

// Declare the pins for the Button
int x_pin = A0;  // base
int y_pin = A1;  // right servo
int z_pin = A2;  // left servo
int grip_pin = A3; // claw

int x_pos;    // servo position - base
int y_pos;    // servo position - right servo
int z_pos;    // servo position - left servo
int grip_pos;    // servo position - claw

void setup() {
  Serial.begin(9600);
  // Define pin as input
  servo_x.attach(11);  // servo x - base
  servo_y.attach(10);  // servo y - right servo
  servo_z.attach(9);  // servo z - left servo
  servo_grip.attach(5);  // servo grip - claw

  //original position
  x_pos = 90;
  y_pos = 0;
  z_pos = 175;
  grip_pos = 0;

  servo_x.write(x_pos);
  servo_y.write(y_pos);
  servo_z.write(z_pos);
  servo_grip.write(grip_pos);
}

void loop() {
  // Read the value of the input
  int val_x = analogRead(x_pin);
  int val_y = analogRead(y_pin);
  int val_z = analogRead(z_pin);
  int val_grip = analogRead(grip_pin);

  delay(15);
  // button x
  if (val_x < 400) {
    if (x_pos < 180) {
      x_pos = x_pos + 1;
      servo_x.write(x_pos);
    }
  }
  else if (val_x > 750) {
    if (x_pos > 0) {
      x_pos = x_pos - 1;
      servo_x.write(x_pos);
    }
  }
  // button x

  // button y
  if (val_y < 400) {
    if (y_pos < 120) {
      y_pos = y_pos + 1;
      servo_y.write(y_pos);
    }
  }
  else if (val_y > 750) {
    if (y_pos > 0) {
      y_pos = y_pos - 1;
      servo_y.write(y_pos);

      //check z pos
      if (z_pos < 150)
      {
        if (z_pos < 175) {
          z_pos = z_pos + 1;
          servo_z.write(z_pos);
        }
      }
    }
  }
  // button y
 
  // joystick Z
  if (val_z < 400) {
    if (z_pos < 175) {
      z_pos = z_pos + 1;
      servo_z.write(z_pos);
    }
  }
  else if (val_z > 750) {
    if (z_pos > 90) {
      z_pos = z_pos - 1;
      servo_z.write(z_pos);
    }
  }
  // button z

  // button claw
  if (val_grip < 400) {
    if (grip_pos < 120) {
      grip_pos = grip_pos + 1;
      servo_grip.write(grip_pos);
    }
  }
  else if (val_grip > 750) {
    if (grip_pos > 0) {
      grip_pos = grip_pos - 1;
      servo_grip.write(grip_pos);
    }
  }
  // button claw

  Serial.print("x_axis: ");
  Serial.print(x_pos);
  Serial.print(", y_axis: ");
  Serial.print(y_pos);
  Serial.print(", z_axis: ");
  Serial.println(z_pos);
}
