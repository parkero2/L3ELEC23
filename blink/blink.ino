//make a program for arduino that has a drive forward and backward functions
//and a turn left and right functions\
//and a stop function
//and a function that makes the robot go in a square
//and a function that makes the robot go in a circle
//and a function that makes the robot go in a triangle
//and a function that makes the robot go in a hexagon
//and a function that makes the robot go in a octagon
//and a function that makes the robot go in a star
//and a function that makes the robot go in a pentagon
//and a function that makes the robot go in a decagon
//and a function that makes the robot go in a heptagon
//and a function that makes the robot go in a nonagon

//and a function that makes the robot go in a square
//and a function that makes the robot go in a circle

#include <jdklfg.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward();
  delay(1000);
  backward();
  delay(1000);
  turnLeft();
  delay(1000);
  turnRight();
  delay(1000);
  stop();
  delay(1000);
  square();
  delay(1000);
  circle();
  delay(1000);
  triangle();
  delay(1000);
  hexagon();
  delay(1000);
  octagon();
  delay(1000);
  star();
  delay(1000);
  pentagon();
  delay(1000);
  decagon();
  delay(1000);
  heptagon();
  delay(1000);
  nonagon();
  delay(1000);
}

void forward() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void backward() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
} 

void turnLeft() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void turnRight() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void stop() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void square() {
    forward();
    delay(1000);
    turnRight();
    delay(1000);
    forward();
    delay(1000);
    turnRight();
    delay(1000);
    forward();
    delay(1000);
    turnRight();
    delay(1000);
    forward();
}

void circle() {
    for (int i = 0; i < 4; i++) {
        forward();
        delay(1000);
        turnRight();
        delay(1000);
    }
}

void triangle() {
    for (int i = 0; i < 3; i++) {
        forward();
        delay(1000);
        turnRight();
        delay(1000);
    }
}

void hexagon() {
    for (int i = 0; i < 6; i++) {
        forward();
        delay(1000);
        turnRight();
        delay(1000);
    }
}

void octagon() {
    for (int i = 0; i < 8; i++) {
        forward();
        delay(1000);
        turnRight();
        delay(1000);
    }
}

void star() {
    for (int i = 0; i < 5; i++) {
        forward();
        delay(1000);
        turnRight();
        delay(1000);
    }
}