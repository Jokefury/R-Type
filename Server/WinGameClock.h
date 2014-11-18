#pragma once

#include<Windows.h>
#include<WinBase.h>
#include"IGameClock.h"

class	gameClock : public IGameClock
{
	SYSTEMTIME		s_;
	FILETIME		f_;
	ULARGE_INTEGER	ui_;

	INT64				  lastUpdateMark_;
	INT64				  startMark_;
	unsigned int             elapsedTime;

	INT64	systemTimeToInt64(const SYSTEMTIME&);

public:
	gameClock();
	virtual	~gameClock();
	virtual unsigned int        getElapsedTime() const;
	virtual unsigned int        getTotalElapsedTime() const;
	virtual void          update();
};