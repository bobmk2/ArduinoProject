const int LED = 9;
const int BUTTON = 13;

int i =0;
int val = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  val = digitalRead(BUTTON);
  if(val == HIGH)
  {
    for (i = 0; i < 255; i++)
    {
      analogWrite(LED, i);
      delay(1);
    }
    for (i = 255; i> 0; i--)
    {
      analogWrite(LED, i);
      delay(1);
    }
  }
}
