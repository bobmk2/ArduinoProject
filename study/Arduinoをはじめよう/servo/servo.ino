#include <DoubleDegits7SegmentsLED.h>
#include <Servo.h>
#include <math.h> 

DoubleDegits7SegmentsLED yellowDigitsLED;

const int TOP_LED = 11;
const int UPPER_RIGHT_LED = 10;
const int UPPER_LEFT_LED = 9;
const int MIDDLE_LED = 8;
const int LOWER_RIGHT_LED = 7;
const int LOWER_LEFT_LED = 6;
const int BOTTOM_LED = 5;

const int LEFT_LED = 13;
const int RIGHT_LED = 12;

const int SERVO = 3; 

Servo servo;

void setup()
{
  yellowDigitsLED.attach(TOP_LED, UPPER_LEFT_LED, UPPER_RIGHT_LED, MIDDLE_LED, LOWER_LEFT_LED, LOWER_RIGHT_LED, BOTTOM_LED, LEFT_LED, RIGHT_LED);
  
  servo.attach(SERVO);
  
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(0));
  
  int deg = map(analogRead(0),0,1023,0,90);
  
  servo.write(deg);

  yellowDigitsLED.writeNumber(deg);
}
