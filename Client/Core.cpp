#include "Core.h"
#include "SFMLDisplay.h"
#include "EventGeneric.h"
#if defined(_WIN32) || defined(_WIN64)
#include "WinTCPService.h"
#include "WinUDPService.h"
#include "WinSelect.h"
#elif UNIX
#include "UnixTCPService.h"
#include "UnixUDPService.h"
#include "UnixSelect.h"
#endif
#include "ServiceClosedException.h"

Core::Core(std::string const& username, std::string const& host, int port)
  : networkTCP_(0), networkUDP_(0), gui_(0), ip_(host), portTCP_(port), username_(username)
{
}

Core::~Core()
{
}

void    Core::init()
{
	this->gui_ = new SFMLDisplay(this->items_, this->username_);
	this->gui_->init();
	this->select_ = new Select;
	this->select_->setTimeout(0);
	this->rm_ = new RequestManager(this->gui_);
	this->initNetworkTCP();
	this->sound_ = new SoundManager;
}

void	Core::initNetworkTCP()
{
	this->networkTCP_ = new TCPService;
	if (!this->networkTCP_->connectTo(this->ip_, this->portTCP_))
	{
		AEvent* tmp = new AEvent;
		tmp->setType(RTCP::NETWORK_DISCONNECTED);
		this->gui_->setEvent(tmp);
		this->networkTCP_ = 0;
		return ;
	}
	this->select_->initSocket(this->networkTCP_, true, false);
	AEvent* tmp = new AEvent;
	tmp->setType(RTCP::NETWORK_CONNECTED);
	this->gui_->setEvent(tmp);
}

void	Core::initNetworkUDP(AEvent const* event)
{
 	this->networkUDP_ = new UDPService;
	if (!this->networkUDP_->connectTo("", dynamic_cast<EventGeneric const*>(event)->getShort()))
	  {
	    delete this->networkUDP_;
	    this->networkUDP_ = 0;
	    delete event;
	    this->destroyNetworkTCP();
	    AEvent* tmp = new AEvent;
	    tmp->setType(RTCP::NETWORK_DISCONNECTED);
	    this->gui_->setEvent(tmp);
	    return ;
	  }
	this->select_->initSocket(this->networkUDP_, true, false);
	this->grm_ = new GameRequestManager(this->items_, this->gui_, this->sound_, dynamic_cast<EventGeneric const*>(event)->getChar());
	this->portUDP_ = dynamic_cast<EventGeneric const*>(event)->getLong();
	delete event;
	AEvent* tmp = new AEvent;
	tmp->setType(RTCP::ROOM_CONNECTION_READY);
	DataPacket* packet = this->rm_->treatmentEvent(tmp);
	this->networkTCP_->pushPacket(packet);
	this->networkTCP_->flushSend();
	this->sound_->playMusic(SoundType::MUSIC_LVL1);
}

void	Core::destroyNetworkTCP()
{
  if (this->networkTCP_)
    {
      this->select_->initSocket(this->networkTCP_, false, false);
      this->networkTCP_->closeService();
      delete this->networkTCP_;
      this->networkTCP_ = 0;
    }
}

void	Core::destroyNetworkUDP()
{
  if (this->networkUDP_)
    {
      this->select_->initSocket(this->networkUDP_, false, false);
      this->networkUDP_->closeService();
      delete this->networkUDP_;
      delete this->grm_;
      this->grm_ = 0;
      this->networkUDP_ = 0;
    }
}

void	Core::updateNetwork(AEvent const* event)
{
	DataPacket* packet;
	DataPacket const* cPacket;

	try
	{
		this->select_->selectSocket();
		if (this->networkTCP_)
		{
			if (this->select_->canRead(this->networkTCP_->getId()))
				if (!this->networkTCP_->flushRecv())
					throw ServiceClosedException();
			this->select_->initSocket(this->networkTCP_, true, false);
			if ((cPacket = this->networkTCP_->getPacket()))
			  this->rm_->treatmentTCP(cPacket);
		}
		if (this->networkUDP_)
		{
			if (this->select_->canRead(this->networkUDP_->getId()))
				this->networkUDP_->flushRecv();
			this->select_->initSocket(this->networkUDP_, true, false);
			if ((cPacket = this->networkUDP_->getPacket()))
				this->grm_->treatmentUDP(cPacket);
		}
		if (event)
		{
			if (!this->networkTCP_ && !this->networkUDP_)
			{
				delete event;
				return ;
			}
			if (event->getType() == RTCP::GAME_MOVE || event->getType() == RTCP::GAME_LAUNCH_SHOT)
				packet = this->grm_->treatmentEvent(event);
			else
				packet = this->rm_->treatmentEvent(event);
			packet->endpoint.host = this->ip_;
			packet->endpoint.port = this->portUDP_;
			if (this->networkUDP_)
			{
				this->networkUDP_->pushPacket(packet);
				this->networkUDP_->flushSend();
			}
			else if (this->networkTCP_)
			{
				this->networkTCP_->pushPacket(packet);
				this->networkTCP_->flushSend();
			}
		}
	}
	catch (ServiceClosedException e)
	{
		delete event;
		this->destroyNetworkUDP();
		this->destroyNetworkTCP();
		AEvent* tmp = new AEvent;
		tmp->setType(RTCP::NETWORK_DISCONNECTED);
		this->gui_->setEvent(tmp);
		this->sound_->stop(SoundType::MUSIC_LVL1);
		this->sound_->stop(SoundType::MUSIC_BOSS);
	}
}

void    Core::run()
{
	AEvent        *event = 0;

	while (this->gui_->isOpened())
	{
		event = this->gui_->getEvent();
		if (event && !this->networkTCP_ && !this->networkUDP_)
		{
			this->initNetworkTCP();
			delete event;
		}
		else if (event && (event->getType() == RTCP::GAME_NOTIFY_END || event->getType() == RTCP::LAUNCH_GAME))
		  {
		    if (event->getType() == RTCP::GAME_NOTIFY_END)
		      {
			delete event;
			this->destroyNetworkUDP();
			this->destroyNetworkTCP();
			this->sound_->stop(SoundType::MUSIC_LVL1);
			this->sound_->stop(SoundType::MUSIC_BOSS);
			this->networkTCP_ = new TCPService;
			if (!this->networkTCP_->connectTo(this->ip_, this->portTCP_))
			  {
			    AEvent* tmp = new AEvent;
			    tmp->setType(RTCP::NETWORK_DISCONNECTED);
			    this->gui_->setEvent(tmp);
			    this->networkTCP_ = 0;
			  }
			else
			  this->select_->initSocket(this->networkTCP_, true, false);
		      }
		    else if (event->getType() == RTCP::LAUNCH_GAME)
		      this->initNetworkUDP(event);
		  }
		else
		    this->updateNetwork(event);
		event = 0;
		this->gui_->update();
		this->gui_->draw();
	}
}
