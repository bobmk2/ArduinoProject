#include "Arduino.h"
#include "DoubleDegits7SegmentsLED.h"

DoubleDegits7SegmentsLED::DoubleDegits7SegmentsLED()
	:m_topPIN(-1),m_upperLeftPIN(-1),m_upperRightPIN(-1),m_middlePIN(-1),
	m_lowerLeftPIN(-1),m_lowerRightPIN(-1),m_bottomPIN(-1),m_tenthsPlacePIN(-1),m_onesPlacePIN(-1){
	}

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

void DoubleDegits7SegmentsLED::writeText(String text)
{
	if(text.length() > 2)
	{
		//末尾2文字しか出力しません
		text = text.substring((unsigned int)(text.length() - 3));
	}
	_switchLED(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH);
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
			write(NULL, num);
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

	delay(WRITE_DELAY);

	delay(WRITE_DELAY);
}

void DoubleDegits7SegmentsLED::write(char tenth, int ones)
{
}

void DoubleDegits7SegmentsLED::write(int tenth, int ones)
{
}

void DoubleDegits7SegmentsLED::write(int tenth, char ones)
{
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
			digitalWrite(m_tenthsPlacePIN, HIGH);
			digitalWrite(m_onesPlacePIN, HIGH);
			break;
		case TENTH:
			//10の位に書き込む
			digitalWrite(m_tenthsPlacePIN, HIGH);
			digitalWrite(m_onesPlacePIN, LOW);
			break;
		case ONES:
			//1の位に書き込む
			digitalWrite(m_tenthsPlacePIN, LOW);
			digitalWrite(m_onesPlacePIN, HIGH);
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
		case 'c':
			_switchLED(LOW,LOW,LOW,HIGH,HIGH,LOW,HIGH);
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
			
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		default:
			//対応していない場合は何も表示しません
			_switchLED(LOW,LOW,LOW,LOW,LOW,LOW,LOW);
			break;
	}
}
