const int LED = 9;
const int BUTTON = 13;

int val = 0;
int lastVal = 0;
int state = 0;

int brightness = 129;
int isLightning =true;
unsigned long startTime = 0;

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(BUTTON, INPUT);
}

void loop()
{
  val = digitalRead(BUTTON);
  
  if ((val == HIGH) && (lastVal == LOW))
  {
    state = 1 - state;
    startTime = millis();
    isLightning=true;
    delay(10);
  }
  
  if ((val == HIGH) && (lastVal == HIGH))
  {
    if(state == 1 && (millis() - startTime) > 500)
    {
      if(isLightning == true)
      {
        brightness ++;
      }
      else
      {
        brightness --;
      }
       delay(10);
       if (brightness > 255)
       {
         brightness = 255;
         isLightning = false;
       }
       else if (brightness < 0)
       {
         brightness = 1;
         isLightning = true;
       }
    }
  }
  
  lastVal = val;
  if (state == 1)
  {
    analogWrite(LED, brightness);
  }
  else
  {
    analogWrite(LED, 0);
  }
}
