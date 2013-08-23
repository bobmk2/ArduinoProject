#ifndef DoubleDegits7SegmentsLED_h
#define DoubleDegits7SegmentsLED_h
#include "Arduino.h"

class DoubleDegits7SegmentsLED
{
	public:
		static const long WRITE_DELAY = 8;
		DoubleDegits7SegmentsLED(long writeDelay = WRITE_DELAY);
		void attach(int topPIN, int upperRightPIN, int upperLeftPIN, int middlePIN, int lowerRightPIN, int lowerLeftPIN, int bottomPIN, int tenthsPlacePIN, int onesPlacePIN);
		void write(char tenths, char ones);
		void write(char tenths, int ones);
		void write(int tenths, int ones);
		void write(int tenths, char ones);
		void writeText(String text);
		void writeTextWithDelay(long delay, String text);
		void writeNumber(int number, bool twoDegits = false);
		void writeNumberWithDelay(long delay, int number, bool twoDegits = false);
	private:
		enum E_PLACE {BOTH, TENTHS, ONES};//書き込み先（10の位、1の位、両方）
		int m_writeDelay;
		int m_topPIN;
		int m_upperLeftPIN;
		int m_upperRightPIN;
		int m_middlePIN;
		int m_lowerLeftPIN;
		int m_lowerRightPIN;
		int m_bottomPIN;
		int m_tenthsPlacePIN;
		int m_onesPlacePIN;
		void _switchLED(int top, int upperLeft, int upperRight, int middle, int lowerLeft, int lowerRight, int bottom);
		void _switchPlace(E_PLACE place);
		void _writeChar(char c, E_PLACE place);
		void _writeNum(int i, E_PLACE place);
};

#endif

