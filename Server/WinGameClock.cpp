#include"WinGameClock.h"

gameClock::gameClock() :
elapsedTime (0)
{
	SYSTEMTIME	s;

	GetSystemTime(&s);
	startMark_ = systemTimeToInt64 (s);
	lastUpdateMark_ = startMark_;
}

gameClock::~gameClock()
{

}

INT64	gameClock::systemTimeToInt64(const SYSTEMTIME & s)
{
	FILETIME		f;
	ULARGE_INTEGER	ui;

	SystemTimeToFileTime (&s, &f);
	ui.LowPart = f.dwLowDateTime;
	ui.HighPart = f.dwHighDateTime;
	return ui.QuadPart;
}

unsigned int  gameClock::getTotalElapsedTime() const
{
	return static_cast<unsigned int>((lastUpdateMark_ - startMark_) / 10000);
}

unsigned int  gameClock::getElapsedTime() const
{
	return elapsedTime;
}

void    gameClock::update()
{
	SYSTEMTIME        s;
	INT64			  ui;

	GetSystemTime(&s);
	ui = systemTimeToInt64 (s);
	elapsedTime = static_cast<unsigned int>((ui - lastUpdateMark_) / 10000);
	lastUpdateMark_ = ui;
}
