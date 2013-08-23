const int LED = 13;

void setup()
{
  //2番目の引数で入力か出力を切り替える
  pinMode(LED, OUTPUT);
}

void loop()
{
  digitalWrite(LED, HIGH);
  delay(5000);
  digitalWrite(LED, LOW);
  delay(5000);
}

