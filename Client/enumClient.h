#ifndef __ENUMCLIENT_H__
#define __ENUMCLIENT_H__

namespace	Menus
{
	enum	eMenus
	{
		LOADING,
		MAIN,
		LIST_ROOM,
		CREATE_ROOM,
		ROOM,
		EXIT,
		ERROR_NETWORK,
		SCORES,
		PAUSE,
		LAST,
	};
}

enum eEvents
{
	NOTHING = -1,
	NOCHANGE = 1,
	UP = 90,
	UPLEFT = 135,
	UPRIGHT = 45,
	DOWN =  270,
	DOWNLEFT = 225,
	DOWNRIGHT = 315,
	RIGHT = 0,
	LEFT = 180,
	BONUS,
	FIRE,
	ENTER,
	ESCAPE
};

#endif
