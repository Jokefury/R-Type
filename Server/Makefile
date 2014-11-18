NAME=		server

SRCXX=		ABullet.cpp			\
		AEntity.cpp  			\
		BulletSimple.cpp		\
		BulletPlayer0.cpp		\
		BulletPlayer1.cpp		\
		BulletPlayer2.cpp		\
		AMob.cpp			\
		BulletInfos.cpp			\
		BulletManager.cpp		\
		MobManager.cpp			\
		UDPNetworkManager.cpp		\
		UnixGameClock.cpp		\
		main.cpp			\
		Player.cpp			\
		Tile.cpp			\
		Game.cpp			\
		Core.cpp			\
		Room.cpp			\
		GameRequestManager.cpp		\
		TCPNetworkManager.cpp		\
		RoomRequestManager.cpp		\
		Bydo.cpp			\
		MobSpawner.cpp			\
		UnixRandom.cpp			\
		../Common/UnixSelect.cpp	\
		../Common/UnixServerService.cpp	\
		../Common/UnixUDPService.cpp	\
		../Common/UnixTCPService.cpp	\
		../Common/Packman.cpp		\
		../Common/ThreadPool.cpp	\
		../Common/UnixMutex.cpp		\
		../Common/UnixCondVar.cpp	\
		../Common/SafeBool.cpp		\
		../Common/Worker.cpp


OBJXX=		$(SRCXX:.cpp=.o)

INCLUDE=	-I../Common/

CXXFLAGS=	-W -Wall -Wextra -Werror $(INCLUDE) -D UNIX

all:		$(NAME)

$(NAME):	$(OBJXX)
	g++ -o $(NAME) $(OBJXX) -lpthread -ldl

clean:
	rm -f $(OBJXX)

fclean:		clean
	rm -f $(NAME)

re:	fclean all
