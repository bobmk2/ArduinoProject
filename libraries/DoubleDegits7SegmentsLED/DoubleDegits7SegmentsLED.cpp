#include "Arduino.h"
#include "DoubleDegits7SegmentsLED.h"

DoubleDegits7SegmentsLED::DoubleDegits7SegmentsLED(long writeDelay)
	:m_writeDelay(writeDelay),m_topPIN(-1),m_upperLeftPIN(-1),m_upperRightPIN(-1),m_middlePIN(-1),
	m_lowerLeftPIN(-1),m_lowerRightPIN(-1),m_bottomPIN(-1),m_tenthsPlacePIN(-1),m_onesPlacePIN(-1)
{
}

//PINと関連付けます
//setup()で呼んで下さい
void DoubleDegits7SegmentsLED::attach(int topPIN, int upperLeftPIN, int upperRightPIN, int middlePIN, int lowerLeftPIN, int lowerRightPIN, int bottomPIN, int tenthsPlacePIN, int onesPlacePIN)
{
	m_topPIN = topPIN;
	m_upperLeftPIN = upperLeftPIN;
	m_upperRightPIN = upperRightPIN;
	m_middlePIN = middlePIN;
	m_lowerLeftPIN = lowerLeftPIN;
	m_lowerRightPIN = lowerRightPIN;
	m_bottomPIN = bottomPIN;
	m_tenthsPlacePIN = tenthsPlacePIN;
	m_onesPlacePIN = onesPlacePIN;

	pinMode(m_topPIN, OUTPUT);
	pinMode(m_upperRightPIN, OUTPUT);
	pinMode(m_upperLeftPIN, OUTPUT);
	pinMode(m_middlePIN, OUTPUT);
	pinMode(m_lowerRightPIN, OUTPUT);
	pinMode(m_lowerLeftPIN, OUTPUT);
	pinMode(m_bottomPIN, OUTPUT);
	pinMode(m_tenthsPlacePIN, OUTPUT);
	pinMode(m_onesPlacePIN, OUTPUT);
}


//デバッグ用に文字列を一定時間表示します
//処理がdelay値分だけ止まるので毎loopでwriteTextを呼んでください
void DoubleDegits7SegmentsLED::writeTextWithDelay(long delay, String text)
{
	long startMillis = millis();
	while((millis() - startMillis) < delay)
	{
		writeText(text);
	}
}

//デバッグ用に数値を一定時間表示します
//処理がdelay値分だけ止まるので毎loopでwriteNumberを呼んでください
void DoubleDegits7SegmentsLED::writeNumberWithDelay(long delay, int number, bool twoDegits)
{
	long startMillis = millis();
	while((millis() - startMillis) < delay)
	{
		writeNumber(number, twoDegits);
	}
}

//PINが正しく設定されてるか確認するための関数です
//10秒ほどかかります
void DoubleDegits7SegmentsLED::testWrite()
{
	writeTextWithDelay(1000,"AB");
	writeTextWithDelay(1000,"CD");
	writeTextWithDelay(1000,"EF");
	writeTextWithDelay(1000,"ab");
	writeTextWithDelay(1000,"cd");
	writeTextWithDelay(1000,"hn");
	writeTextWithDelay(1000,"or");
	writeTextWithDelay(1000,"-_");
	writeNumberWithDelay(500,1,true);
	writeNumberWithDelay(500,2,true);
	writeNumberWithDelay(500,3,true);
	writeNumberWithDelay(500,4,true);
	writeNumberWithDelay(500,5,true);
	writeNumberWithDelay(500,6,true);
	writeNumberWithDelay(500,7,true);
	writeNumberWithDelay(500,8,true);
	writeNumberWithDelay(500,9,true);
}

void DoubleDegits7SegmentsLED::writeText(String text)
{
	if(text.length() > 2)
	{
		//末尾2文字しか出力しません
		text = text.substring((unsigned int)(text.length() - 3));
	}
	
	
	if(text.length() == 0)
	{
		//長さ0
		write((char)NULL, (char)NULL);
	}
	else if(text.length() == 1)
	{
		//長さ1
		write((char)NULL, text.charAt(0));
	}
	else
	{
		//長さ2
		write(text.charAt(0), text.charAt(1));
	}
}

void DoubleDegits7SegmentsLED::writeNumber(int num, bool twoDegits)
{
	if(num < -9)
	{
		num = -9;
	}
	if(num > 99)
	{
		num = 99;
	}

	if(num < 0)
	{
		//-9以上0未満
		write('-', num*-1);
	}
	else if (num < 10)
	{
		//0以上10未満(1桁)
		if(twoDegits)
		{
			//先頭に0を付ける
			write(0, num);
		}
		else
		{
			//先頭に0を付けない
			write((char)NULL, num);
		}
	}
	else
	{
		//2桁以上の正の整数
		write(num / 10, num % 10);
	}
}

void DoubleDegits7SegmentsLED::write(char tenth, char ones)
{
	_writeChar(tenth, TENTHS);
	delay(m_writeDelay);
	_writeChar(ones, ONES);
	delay(m_writeDelay);
}

void DoubleDegits7SegmentsLED::write(char tenth, int ones)
{
	_writeChar(tenth, TENTHS);
	delay(m_writeDelay);
	_writeNum(ones, ONES);
	delay(m_writeDelay);
}

void DoubleDegits7SegmentsLED::write(int tenth, int ones)
{
	_writeNum(tenth, TENTHS);
	delay(m_writeDelay);
	_writeNum(ones, ONES);
	delay(m_writeDelay);
}

void DoubleDegits7SegmentsLED::write(int tenth, char ones)
{
	_writeNum(tenth, TENTHS);
	delay(m_writeDelay);
	_writeChar(ones, ONES);
	delay(m_writeDelay);
}

void DoubleDegits7SegmentsLED::_switchLED(int top, int upperLeft, int upperRight, int middle, int lowerLeft, int lowerRight, int bottom)
{
	digitalWrite(m_topPIN, top);
	digitalWrite(m_upperLeftPIN, upperLeft);
	digitalWrite(m_upperRightPIN, upperRight);
	digitalWrite(m_middlePIN, middle);
	digitalWrite(m_lowerLeftPIN, lowerLeft);
	digitalWrite(m_lowerRightPIN, lowerRight);
	digitalWrite(m_bottomPIN, bottom);
}

void DoubleDegits7SegmentsLED::_switchPlace(E_PLACE place)
{
	switch(place)
	{
		case BOTH:
			//両方に書き込む
			digitalWrite(m_tenthsPlacePIN, LOW);
			digitalWrite(m_onesPlacePIN, LOW);
			break;
		case TENTHS:
			//10の位に書き込む
			digitalWrite(m_tenthsPlacePIN, LOW);
			digitalWrite(m_onesPlacePIN,HIGH);
			break;
		case ONES:
			//1の位に書き込む
			digitalWrite(m_tenthsPlacePIN, HIGH);
			digitalWrite(m_onesPlacePIN, LOW);
			break;
	}
}

void DoubleDegits7SegmentsLED::_writeChar(char c, E_PLACE place)
{
	_switchPlace(place);

	switch(c)
	{
		case 'A':
			_switchLED(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW);
			break;
		case 'B':
			_switchLED(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH);
			break;
		case 'C':
			_switchLED(HIGH,HIGH,LOW,LOW,HIGH,LOW,HIGH);
			break;
		case 'D':
			_switchLED(HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH);
			break;
		case 'E':
			_switchLED(HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH);
			break;
		case 'F':
			_switchLED(HIGH,HIGH,LOW,HIGH,HIGH,LOW,LOW);
			break;
		case 'G':
			_switchLED(HIGH,HIGH,LOW,LOW,HIGH,HIGH,HIGH);
			break;
		case 'X':
			_switchLED(LOW,HIGH,HIGH,HIGH,HIGH,HIGH,LOW);
			break;
		case 'a':
			//aの表現は7セグメントでは難しいのでoと同じ
			_switchLED(LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH);
			break;
		case 'b':
			_switchLED(LOW,HIGH,LOW,HIGH,HIGH,HIGH,HIGH);
			break;
		case 'c':
			_switchLED(LOW,LOW,LOW,HIGH,HIGH,LOW,HIGH);
			break;
		case 'd':
			_switchLED(LOW,LOW,HIGH,HIGH,HIGH,HIGH,HIGH);
			break;
		case 'h':
			_switchLED(LOW,HIGH,LOW,HIGH,HIGH,HIGH,LOW);
			break;
		case 'n':
			_switchLED(LOW,LOW,LOW,HIGH,HIGH,HIGH,LOW);
			break;
		case 'o':
			_switchLED(LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH);
			break;
		case 'r':
			_switchLED(LOW,LOW,LOW,HIGH,HIGH,LOW,LOW);
			break;
		case '-':
			_switchLED(LOW,LOW,LOW,HIGH,LOW,LOW,LOW);
			break;
		case '_':
			_switchLED(LOW,LOW,LOW,LOW,LOW,LOW,HIGH);
			break;
		case '0':
			_switchLED(HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH);
			break;
		case '1':
			_switchLED(LOW,LOW,HIGH,LOW,LOW,HIGH,LOW);
			break;
		case '2':
			_switchLED(HIGH,LOW,HIGH,HIGH,HIGH,LOW,HIGH);
			break;
		case '3':
			_switchLED(HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH);
			break;
		case '4':
			_switchLED(LOW,HIGH,HIGH,HIGH,LOW,HIGH,LOW);
			break;
		case '5':
			_switchLED(HIGH,HIGH,LOW,HIGH,LOW,HIGH,HIGH);
			break;
		case '6':
			_switchLED(HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH);
			break;
		case '7':
			_switchLED(HIGH,LOW,HIGH,LOW,LOW,HIGH,LOW);
			break;
		case '8':
			_switchLED(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH);
			break;
		case '9':
			_switchLED(HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH);
			break;
		default:
			//対応していない場合は何も書きません
			_switchLED(LOW,LOW,LOW,LOW,LOW,LOW,LOW);
			break;
	}
}

void DoubleDegits7SegmentsLED::_writeNum(int num, E_PLACE place)
{
	_switchPlace(place);
	switch(num)
	{
		case 0:
			_switchLED(HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH);
			break;
		case 1:
			_switchLED(LOW,LOW,HIGH,LOW,LOW,HIGH,LOW);
			break;
		case 2:
			_switchLED(HIGH,LOW,HIGH,HIGH,HIGH,LOW,HIGH);
			break;
		case 3:
			_switchLED(HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH);
			break;
		case 4:
			_switchLED(LOW,HIGH,HIGH,HIGH,LOW,HIGH,LOW);
			break;
		case 5:
			_switchLED(HIGH,HIGH,LOW,HIGH,LOW,HIGH,HIGH);
			break;
		case 6:
			_switchLED(HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH);
			break;
		case 7:
			_switchLED(HIGH,LOW,HIGH,LOW,LOW,HIGH,LOW);
			break;
		case 8:
			_switchLED(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH);
			break;
		case 9:
			_switchLED(HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH);
			break;
		default:
			//対応していない場合は何も表示しません
			_switchLED(LOW,LOW,LOW,LOW,LOW,LOW,LOW);
			break;
	}
}
