// Test code for the arduino parallel parking bot V1
#include <Arduino.h>

int RightMT1 = 6;
int RightMT2 = 7;
int LeftMT1 = 8;
int LeftMT2 = 9;
int EnRight = 5; //pwm
int EnLeft = 11;

int SPD = 120;
int SPD1 = 150;

int frontOUT = A5;
int frontIN = A4;
int leftOUT = A3;
int leftIN = A2;
int backOUT = A1;
int backIN = A0;

int leftDistance = 0;
int backDistance = 0;
int frontDistance = 0;

int counter = 0;
int previous = 0;
int current = 0;

void moveForward2()
{
  analogWrite(EnRight, SPD1);
  analogWrite(EnLeft, SPD1);
  digitalWrite(RightMT1, HIGH);
  digitalWrite(RightMT2, LOW);
  digitalWrite(LeftMT1, LOW);
  digitalWrite(LeftMT2, HIGH);
}

void moveForward()
{
  analogWrite(EnRight, SPD);
  analogWrite(EnLeft, SPD);
  digitalWrite(RightMT1, HIGH);
  digitalWrite(RightMT2, LOW);
  digitalWrite(LeftMT1, LOW);
  digitalWrite(LeftMT2, HIGH);
}
void moveBackward()
{
  analogWrite(EnRight, SPD);
  analogWrite(EnLeft, SPD);
  digitalWrite(RightMT1, LOW);
  digitalWrite(RightMT2, HIGH);
  digitalWrite(LeftMT1, HIGH);
  digitalWrite(LeftMT2, LOW);
}
void turnRight2()
{
  analogWrite(EnRight, SPD1);
  analogWrite(EnLeft, SPD1);
  digitalWrite(RightMT1, LOW);
  digitalWrite(RightMT2, HIGH);
  digitalWrite(LeftMT1, LOW);
  digitalWrite(LeftMT2, HIGH);
}
void turnRight()
{
  analogWrite(EnRight, SPD);
  analogWrite(EnLeft, SPD);
  digitalWrite(RightMT1, LOW);
  digitalWrite(RightMT2, HIGH);
  digitalWrite(LeftMT1, LOW);
  digitalWrite(LeftMT2, HIGH);
}
void turnLeft2()
{
  analogWrite(EnRight, SPD1);
  analogWrite(EnLeft, SPD1);
  digitalWrite(RightMT1, HIGH);
  digitalWrite(RightMT2, LOW);
  digitalWrite(LeftMT1, HIGH);
  digitalWrite(LeftMT2, LOW);
}
void turnLeft()
{
  analogWrite(EnRight, SPD);
  analogWrite(EnLeft, SPD);
  digitalWrite(RightMT1, HIGH);
  digitalWrite(RightMT2, LOW);
  digitalWrite(LeftMT1, HIGH);
  digitalWrite(LeftMT2, LOW);
}
void stop()
{
  digitalWrite(EnRight, LOW);
  digitalWrite(EnLeft, LOW);
}
int leftDistanceMeasure()
{
  digitalWrite(leftOUT, LOW);
  delayMicroseconds(2);
  digitalWrite(leftOUT, HIGH);
  delayMicroseconds(20);
  digitalWrite(leftOUT, LOW);
  float lDistance = pulseIn(leftIN, HIGH); //hit back
  lDistance = lDistance / 58; //calibration to conv to meters
  return (int)lDistance;
}
int backDistanceMeasure()
{
  digitalWrite(backOUT, LOW);
  delayMicroseconds(2);
  digitalWrite(backOUT, HIGH);
  delayMicroseconds(20);
  digitalWrite(backOUT, LOW);
  float bDistance = pulseIn(backIN, HIGH);
  bDistance = bDistance / 58;
  return (int)bDistance;
}
int frontDistanceMeasure()
{
  digitalWrite(frontOUT, LOW);
  delayMicroseconds(2);
  digitalWrite(frontOUT, HIGH);
  delayMicroseconds(20);
  digitalWrite(frontOUT, LOW);
  float bDistance = pulseIn(frontIN, HIGH);
  bDistance = bDistance / 58;
  return (int)bDistance;
}

void setup()
{ // Config fucvtıon . it wıll only run one time
  Serial.begin(9600); //Serial Monitor Rate defınatıon
  pinMode(RightMT1, OUTPUT);
  pinMode(RightMT2, OUTPUT);
  pinMode(LeftMT1, OUTPUT);
  pinMode(LeftMT2, OUTPUT);
  pinMode(EnRight, OUTPUT);
  pinMode(EnLeft, OUTPUT);
  pinMode(leftOUT, OUTPUT);
  pinMode(leftIN, INPUT);
  pinMode(backOUT, OUTPUT);
  pinMode(backIN, INPUT);
  stop();
}

void detectWall()
{

  while (counter != 4)
  {

    current = leftDistanceMeasure();
    delay(10);

    int difference = abs(current - previous);
    delay(10);
    if (difference > 10)
    {
      previous = current;
      counter++;
      moveForward();
    }
    else
    {
      previous = current;
      moveForward();
    }
  }
}
void back()
{
  moveBackward();
  Serıal.prıntln("Back");
  delay(50);
}
void adjustright()
{
  turnRight();
  delay(450);
}
void adjustleft()
{
  turnLeft();
  delay(350);
}
void park()
{
  moveBackward();
  delay(100);
  while (1)
  {
    backDistance = backDistanceMeasure();

    if (backDistance < 11)
    {
      stop();

      break;
    }
    else
    {
      moveBackward();
    }
    frontDistance = frontDistanceMeasure();
    if (frontDistance < 5)
    {
      stop();

      break;
    }
  }
}
void loop()
{ // Parking
  detectWall();
  back();
  adjustright();
  park();
  stop();
  delay(10);
  adjustleft();
  stop();
// Getting out of Parkıng
  delay(100);
  turnRight2();
  delay(400);
  moveForward2();
  delay(500);
  turnLeft2();
  delay(300);
  moveForward2();
  delay(2000);
  stop();
  delay(50000); // 1 sec = 1000.
}