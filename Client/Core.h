#ifndef __CORE_H__
#define __CORE_H__

#include <list>
#include "IGui.h"
#include "IService.h"
#include "ISelect.h"
#include "AEvent.h"
#include "Obj.h"
#include "RequestManager.h"
#include "GameRequestManager.h"
#include "FmodSoundManager.h"

class	Core
{
private:
	std::list<Obj *>	items_;
	IService		*networkTCP_;
	IService		*networkUDP_;
	ISelect			*select_;
	ISoundManager		*sound_;
	RequestManager		*rm_;
	GameRequestManager	*grm_;
	IGui			*gui_;
	std::string		ip_;
	int			portTCP_;
	int			portUDP_;
	std::string		username_;

private:
	void initNetworkUDP(AEvent const* event);
	void initNetworkTCP();
	void destroyNetworkTCP();
	void destroyNetworkUDP();
	void updateNetwork(AEvent const* event);

public:
	Core(std::string const& username, std::string const& host, int port);
	~Core();

	void	init();
	void	run();
};

#else

class	Core;

#endif
