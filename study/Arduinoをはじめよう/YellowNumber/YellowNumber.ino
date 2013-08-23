const int TOP_LED = 11;
const int UPPER_RIGHT_LED = 10;
const int UPPER_LEFT_LED = 9;
const int MIDDLE_LED = 8;
const int LOWER_RIGHT_LED = 7;
const int LOWER_LEFT_LED = 6;
const int BOTTOM_LED = 5;

const int GREEN_LED = 4;
const int RED_LED = 3;

const int LEFT_LED = 12;
const int RIGHT_LED = 13;

const int BUTTON = 2;

const int BOTH = 0;
const int LEFT = 1;
const int RIGHT = 2;

long lastMillis = -1;
int val = 0;
int timer = 10;


void setup()
{
  pinMode(TOP_LED, OUTPUT);
  pinMode(UPPER_RIGHT_LED, OUTPUT);
  pinMode(UPPER_LEFT_LED, OUTPUT);
  pinMode(MIDDLE_LED, OUTPUT);
  pinMode(LOWER_LEFT_LED, OUTPUT);
  pinMode(LOWER_RIGHT_LED, OUTPUT);
  pinMode(BOTTOM_LED, OUTPUT);

  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  pinMode(BUTTON, INPUT);
  
  Serial.begin(9600);
  lastMillis = millis();
  timer = 10;
}

void loop()
{
  if(digitalRead(BUTTON) == HIGH)
  {
    timer = 10;
    lastMillis = millis();
  }
  
  char s[2];
  sprintf(s,"%d", timer);
  Serial.println("========");

  if(timer >= 0 && timer < 100)
  {
    writeNumber(timer/10, LEFT);
    delay(9);
    writeNumber(timer % 10, RIGHT);
    delay(9);
  }
  else
  {
    //対応していないのでXXとする
    writeChar('x', LEFT);
    delay(9);
    writeChar('x', RIGHT);
    delay(9);
  }
  
  if(timer > 0 && timer < 100)
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
  else
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
  
  long m = millis();
  if (m - lastMillis >= 1000)
  {
    timer --;
    lastMillis = m;
  }
  /*
  if(val == 0)
  {
      val = 1;
//  change(LOW, HIGH, LOW, HIGH, LOW);
      writeNumber(0,LEFT);
      delay(8);
  }
  else
  {
    val = 0;
//  change(LOW, LOW, HIGH, LOW, HIGH);

    writeNumber(5, RIGHT);
    delay(8);
  }
  */
  /*
  Serial.write("first");
  change(HIGH, HIGH, HIGH, LOW, LOW);
  delay(1000);
  change(HIGH, HIGH, HIGH, HIGH, LOW);
  delay(1000);
  change(HIGH, HIGH, HIGH, LOW, HIGH);
  delay(1000);
  change(HIGH, HIGH, HIGH, HIGH, HIGH);
  delay(1000);

  Serial.write("second");
  change(LOW, HIGH, HIGH, LOW, LOW);
  delay(1000);
  change(LOW, HIGH, HIGH, HIGH, LOW);
  delay(1000);
  change(LOW, HIGH, HIGH, LOW, HIGH);
  delay(1000);
  change(LOW, HIGH, HIGH, HIGH, HIGH);
  delay(1000);

  Serial.write("third");
  change(LOW, LOW, HIGH, LOW, LOW);
  delay(1000);
  change(LOW, LOW, HIGH, HIGH, LOW);
  delay(1000);
  change(LOW, LOW, HIGH, LOW, HIGH);
  delay(1000);
  change(LOW, LOW, HIGH, HIGH, HIGH);
  delay(1000);

//  change(HIGH, HIGH, HIGH, LOW, LOW);
//  delay(1000);
//  change(HIGH, HIGH, HIGH, LOW, LOW);
//  delay(1000);
  */
}

void switchWriteTo(int writeTo)
{
  if(writeTo == BOTH)
  {
    digitalWrite(LEFT_LED, HIGH);
    digitalWrite(RIGHT_LED, HIGH);
  }
  else if (writeTo == LEFT)
  {
    digitalWrite(LEFT_LED, HIGH);
    digitalWrite(RIGHT_LED, LOW);
  }
  else if (writeTo == RIGHT)
  {
    digitalWrite(LEFT_LED, LOW);
    digitalWrite(RIGHT_LED, HIGH);
  }
}


void writeChar(char c, int writeTo)
{
  switchWriteTo(writeTo);
  
  if(c == 'x')
  {
    switchLED(LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW);
  }
}

void writeNumber(int number, int writeTo)
{
  switchWriteTo(writeTo);
  
  if(number == 0)
  {
    switchLED(HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH);
  }
  if(number == 1)
  {
    switchLED(LOW,LOW,HIGH,LOW,LOW,HIGH,LOW);
  }
  if(number == 2)
  {
    switchLED(HIGH,LOW,HIGH,HIGH,HIGH,LOW,HIGH);
  }
  if(number == 3)
  {
    switchLED(HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH);
  }
  if(number == 4)
  {
    switchLED(LOW,HIGH,HIGH,HIGH,LOW,HIGH,LOW);
  }
  if(number == 5)
  {
    switchLED(HIGH,HIGH,LOW,HIGH,LOW,HIGH,HIGH);
  }
  if(number == 6)
  {
    switchLED(HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH);
  }
  if(number == 7)
  {
    switchLED(HIGH,LOW,HIGH,LOW,LOW,HIGH,LOW);
  }
  if(number == 8)
  {
    switchLED(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH);
  }
  if(number == 9)
  {
    switchLED(HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH);
  }
}

void switchLED(int top, int upperLeft, int upperRight, int middle, int lowerLeft, int lowerRight, int bottom)
{
    digitalWrite(TOP_LED, top);
    digitalWrite(UPPER_LEFT_LED, upperLeft);
    digitalWrite(UPPER_RIGHT_LED, upperRight);
    digitalWrite(MIDDLE_LED, middle);
    digitalWrite(LOWER_LEFT_LED, lowerLeft);
    digitalWrite(LOWER_RIGHT_LED, lowerRight);
    digitalWrite(BOTTOM_LED, bottom);
}

void change(int a, int b, int c, int q, int r)
{
  digitalWrite(TOP_LED, a);
  digitalWrite(UPPER_RIGHT_LED, b);
  digitalWrite(UPPER_LEFT_LED, c);
  digitalWrite(LEFT_LED, q);
  digitalWrite(RIGHT_LED, r);
}
