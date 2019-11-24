Pseudocode:

Press the green button three times, each time will return the count value of 1, until it reaches 3, the code will execute the code for getting the second pop

Green light will turn on to indicate the robot is getting the second pop

Going forward, the left motor power is -60 and right motor power is 37, the delay for the code is 0.3 seconds

Servo arm position 0, which is vertical to the surface. Delay is 1 second for the code to execute

Turn right, set the motor powers to 30, delay is 0.6 seconds

While the sensor detects the line, stop and turn left, while it does not see the line again, stop and turn right 

The code instructs the robot to follow the line until the ultrasonic sensor detects the proximity to the wall is 15 centimeters away, set motors to stop

Set servo position as 0 and delay 1 second to set the servo arm vertical to the ground

The light turns on for 0.5 seconds and turn off for 0.5 seconds, repeat until the light flashes 3 times

Turn right, set the motor powers to 30, delay is 0.6 seconds

Move forward for 0.5 seconds

Stop if the the ultrasonic sensor detects the distance between the robot and the wall is 5 centimeters 

Close the claws for 0.5 seconds

Move backwards for 0.1 seconds

Going right, set motor powers as 30, continue for 0.6 second

Set motorpowers as -60 and 37, continue for 0.3 seconds

If the robot detects the line, stop and turn left, while it does not see the line again, stop and turn right, the delay for the line following code is 13 seconds, stop after 13 seconds

After 13 seconds, set servo position as 140 to open the claws and drop the pop at the starting position

Press the green button two times, each time will register count as 1, until it reaches 2, the code will execute for getting the first pop

Red light will turn on to indicate the robot is getting the first pop

Set left motor power higher than the right motor power to go slightly right towards the line

If the sensor detects the line, stop and turn left, while it does not see the line again, stop and turn right 

Continue line following, stop until the ultrasonic sensor is in proximity of 28 centimeters away from the wall

Servo arm position 0, which is vertical to the surface. Delay is 1 second for the code to execute

Turn right, set the motor powers to 30, delay is 0.6 seconds

Move forward for 0.5 seconds

Stop if the the ultrasonic sensor detects the distance between the robot and the wall is 7 centimeters 

Close the claws in 0.5 seconds

Move backwards for 0.08 seconds

Going right, set motor powers as 30, continue for 0.44 second

If it detects the line, start line following code for a period of time and stop

Turn left for 0.74 seconds

Set motorpowers as 40 and go straight for 0.62 seconds

Set second servo position as 140, delay is 0.5 seconds to release the pop







#include <PRIZM.h>
PRIZM prizm;
int count = 0;

void setup() {
  prizm.PrizmBegin();
  prizm.setServoSpeed(1, 100);
  prizm.setServoPosition(2, 50);
  delay(1000);
  prizm.setServoSpeed(1, 100);
  for (int x = 0; x <= 60; x++) {
    while (prizm.readStartButton() == 1) {
      count = count + 1;
      delay(350);
    }
    delay(100);
  }
}

void loop() {
  counter();
  prizm.PrizmEnd();
}

void counter() {
  //if counter is one do pop1
  if (count == 1) {
    prizm.setRedLED(1);
    pop1();
  }
  //if counter is 2 do pop 2
  else if (count == 2) {
    prizm.setGreenLED(1);
    pop2();
  }
  // if counter in anything else do nothing
  else if ((count == 0) || (count > 3)) {
    prizm.setGreenLED(1);
    prizm.setRedLED(1);
    delay(1000);
    prizm.PrizmEnd();
  }
}

void pop1() {
  start();
  
  //find the line
  L1(0, 0);
  
  //grab pop 1 
  rightturn1(30, 640);
  f1();
  prizm.setServoPosition(2, 0);
  delay(500);
  
  //Return to the line
  back1(30, 100);
  rightturn1(30, 600);
  prizm.setMotorPowers(-60, 37);
  delay(300);
  
  //Find the line and start following it for a certain period of time
  followline1 ();
  RL1(0, 0);

  //after a certain amount of time following the line go straight
  straight1(40, 1080);
  prizm.setMotorPowers(125, 125);
  delay(500);

  //release pop 1
  prizm.setServoPosition(2, 140);
  delay(500);
}

void pop2() {

  //find the line
  start2();

  //follow the line
  L2(0, 0);

  //Grab pop 2
  rightturn2(30, 640);
  f2();
  prizm.setServoPosition(2, 0);
  delay (500);

  //Return and find the line again
  back2(30, 80);
  rightturn2(30, 440);
  prizm.setMotorPowers(125, 125);
  delay(100);

  //follow that line for a certain period of time 
  followline2 ();
  RL2(0, 0);

  //After that period of time return to start position
  leftturn2(30, 740);
  straight2(40, 620);
  prizm.setMotorPowers(125, 125);
  delay(500);

  // release pop 2
  prizm.setServoPosition(2, 140);
  delay (500);

}

void start() {
  
//open hand 
  prizm.setServoPosition(2, 70);
  delay(1000);

  //Get out of parking position
  straight1(40, 620);
  rightturn1(30, 720);

  //go straight until you see the line
  prizm.setMotorPowers(-60, 37);
  delay(400);
  while (prizm.readLineSensor(3) == HIGH) {
    prizm.setMotorPowers(-20, 8);
  }
  prizm.setMotorPowers(125, 125);
  delay(50);
}

void followline1() {
  
  //After grabbing pop 1, follow a curve unil you see the line
  while (prizm.readLineSensor(3) == HIGH) {
    prizm.setMotorPowers(-20, 8);
  }
  prizm.setMotorPowers(125, 125);
  delay(50);
}


void straight1(int m, int d) {
  prizm.setMotorPowers(-m, m - 15);
  delay(d);
  prizm.setMotorPowers(125, 125);
}

void rightturn1 (int m, int d) {
  prizm.setServoPosition(1, 0);
  delay(500);
  for (int x = 0; x <= 2; x++) {
    prizm.setRedLED(HIGH);
    delay(100);
    prizm.setRedLED(LOW);
    delay(100);
  }
  prizm.setMotorPowers(-m, -m + 15);
  delay(d);
}


void f1() {
  //go forward until you are 4 cm away from pop1
  while (prizm.readSonicSensorCM(4) >= 4) {
    prizm.setMotorPowers(-24, 15);
  }
  prizm.setMotorPowers(125, 125);
  delay(500);
}

void L1 (int m, int n) {
  //follow the line until you are 28 cm away from the wall
  while (prizm.readSonicSensorCM(4) >= 28) {
    if (prizm.readLineSensor(3) == 1) {
      prizm.setMotorPowers(-m - 40, 125);
    }
    else  prizm.setMotorPowers(125, n + 50);
  }
  prizm.setMotorPowers(125, 125);
}

void RL1 (int m, int n) {
  //go left and right following the line this many times
  for (int x = 0; x <= 430; x++) {
    if (prizm.readLineSensor(3) == 1) {
      prizm.setMotorPowers(-m - 30, 125);
      delay(10);
    }
    else prizm.setMotorPowers(125, n + 50);
    delay(10);
  }
  prizm.setMotorPowers(125, 125);
}


void back1 (int m, int n) {
  prizm.setMotorPowers(m, -m + 15);
  delay(n);
}




void start2 () {
  // open hand
  prizm.setServoPosition(2, 140);
  delay(1000);
  //go on this curve until you see the line
  straight2(40, 620);
  while (prizm.readLineSensor(3) == HIGH) {
    prizm.setMotorPowers(-20, 8);
  }
  prizm.setMotorPowers(125, 125);
  delay(50);
}


void L2 (int m, int n) {
  //follow that line until you are 20 cm away from the wall
  while (prizm.readSonicSensorCM(4) >= 20) {
    if (prizm.readLineSensor(3) == 1) {
      prizm.setMotorPowers(-m - 40, 125);
    }
    else  prizm.setMotorPowers(125, n + 50);
  }
  prizm.setMotorPowers(125, 125);
}



void f2() {
  //go for forward until you are 3 cm away from the pop
  while (prizm.readSonicSensorCM(4) >= 3) {
    prizm.setMotorPowers(-24, 15);
  }
  prizm.setMotorPowers(125, 125);
  delay(500);
}



void rightturn2 (int m, int d) {
  prizm.setServoPosition(1, 0);
  delay(500);
  for (int x = 0; x <= 2; x++) {
    prizm.setRedLED(HIGH);
    delay(100);
    prizm.setRedLED(LOW);
    delay(100);
  }
  prizm.setMotorPowers(-m, -m + 15);
  delay(d);
}

void straight2(int m, int d) {
  prizm.setMotorPowers(-m, m - 15);
  delay(d);
  prizm.setMotorPowers(125, 125);
}


void back2 (int m, int n) {
  prizm.setMotorPowers(m, -m + 15);
  delay(n);
}


void RL2 (int m, int n) {
  //go left and right following the line this many times 
  for (int x = 0; x <= 700; x++) {
    if (prizm.readLineSensor(3) == 1) {
      prizm.setMotorPowers(-m - 30, 125);
      delay(10);
    }
    else prizm.setMotorPowers(125, n + 50);
    delay(10);
  }
  prizm.setMotorPowers(125, 125);
}

void followline2() {
  //After grabbing pop 2 move back this period of time until you see the line again
  while (prizm.readLineSensor(3) == HIGH) {
    prizm.setMotorPowers(-25, 8);
  }
  prizm.setMotorPowers(125, 125);
  delay(50);
}


void leftturn2(int m, int n) {
  prizm.setMotorPowers(m, m - 15);
  delay(n);
}



