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



