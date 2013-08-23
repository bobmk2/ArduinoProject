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

const int SWITCH = 2; 

const int BOTH = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int NONE = 3;

boolean isMoving;//センサー発火中か否か
int movedCount;//センサー検知回数

boolean lastSwitch = false;//最後のスイッチ状態
long lastMillis = -1;
const int maxNonMovedMillis = 500;//これ以上のスパンで何も引っかからなかったら発火状態をOFF

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
  
  pinMode(SWITCH, INPUT);
  
  Serial.begin(9600);

  lastMillis = millis();
  movedCount = 0;
  isMoving = false;
  lastSwitch = false;
}

void loop()
{
  
  
  if(digitalRead(SWITCH) == LOW)
  {
    //スイッチがOFFの時は何も表示しない
    switchWriteTo(BOTH);
    switchLED(LOW,LOW,LOW,LOW,LOW,LOW,LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    lastSwitch = false;
    return;
  }
  else if (!lastSwitch && digitalRead(SWITCH) == HIGH)
  {
    lastSwitch = true;
    
    //初期化
    movedCount = 0;
    lastMillis = millis();
    isMoving = false;
    return;
  }  
  if(analogRead(0) > 1000)
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    if(!isMoving)
    {
      movedCount ++;
      isMoving = true;
    }
    lastMillis = millis();
  }
  else
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    
    if(isMoving && (millis() - lastMillis) > maxNonMovedMillis)
    {
        isMoving = false;
    }
  }

  setNumber(movedCount);
  
  return;
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

//数字を設定します（-9以上99以下）
void setNumber(int i)
{
  if(i <= -10)
  {
    i = -9;
  }
  if(i >= 100)
  {
    i = 99;
  }
     
  if(i < 0)
  {
    //-9以上、0未満
    writeChar('-',LEFT);
    delay(9);
    writeNumber(i*-1,RIGHT);
  }
  else if(i < 10)
  {
    //0以上10未満
    writeNone(LEFT);
    delay(9);
    writeNumber(i, RIGHT);
  }
  else
  {
    //10以上
    writeNumber(i / 10,LEFT);
    delay(9);
    writeNumber(i % 10,RIGHT);
  }

  delay(9);
}

//文字列を設定します（最大2文字）
void setChar(String str)
{
  if(str.length() > 2)
  {
    //2文字以上は何も表示しません
    writeNone(LEFT);
    delay(9);
    writeNone(RIGHT);
  }
  else if(str.length() == 1)
  {
    //1文字
    writeNone(LEFT);
    delay(9);
    writeChar(str.charAt(0), RIGHT);
  }
  else
  {
    //2文字
    writeChar(str.charAt(0), LEFT);
    delay(5);
    writeChar(str.charAt(1), RIGHT);
  }
  delay(9);
}

//非表示にする
void writeNone(int writeTo)
{
  switchWriteTo(writeTo);
  switchLED(LOW,LOW,LOW,LOW,LOW,LOW,LOW);
}

void writeChar(char c, int writeTo)
{
  switchWriteTo(writeTo);
  
  if(c == 'x')
  {
    switchLED(LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW);
  }
  if(c == 'n')
  {
    switchLED(HIGH,HIGH,HIGH,LOW,HIGH,HIGH,LOW);
  }
  if(c == 'o')
  {
    switchLED(HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH);
  }
  if(c == '_')
  {
    switchLED(LOW,LOW,LOW,LOW,LOW,LOW,HIGH);
  }
  if(c == '-')
  {
    switchLED(LOW,LOW,LOW,HIGH,LOW,LOW,LOW);
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
