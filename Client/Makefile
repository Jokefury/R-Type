NAME=		Client

SRC=		AEvent.cpp			\
		EventInput.cpp			\
		Obj.cpp				\
		Core.cpp			\
		Game.cpp			\
		GameRequestManager.cpp		\
		SFMLDisplay.cpp			\
		SFMLDrawable.cpp		\
		main.cpp			\
		RequestManager.cpp		\
		EventGeneric.cpp		\
		EventRoomList.cpp		\
		EventGameEnd.cpp		\
		MenuManager.cpp			\
		LoadingMenu.cpp			\
		MainMenu.cpp			\
		ListRoomMenu.cpp		\
		RoomMenu.cpp			\
		ErrorMenu.cpp			\
		PauseMenu.cpp			\
		ScoresMenu.cpp			\
		AMenu.cpp			\
		BackgroundDrawable.cpp		\
		PlayerAliveDrawable.cpp		\
		EnemyDrawable.cpp		\
		BulletDrawable.cpp		\
		MobBulletDrawable.cpp		\
		ExplosionDrawable.cpp		\
		FmodSoundManager.cpp		\
		../Common/UnixUDPService.cpp	\
		../Common/UnixSelect.cpp	\
		../Common/Packman.cpp		\
		../Common/UnixTCPService.cpp	\



OBJ=		$(SRC:.cpp=.o)

INCLUDE=	-I./include/ -I../Common/

CXXFLAGS=	-W -Wall -Wextra -Werror $(INCLUDE) -D UNIX

LDFLAGS=	-lsfml-graphics -lsfml-window -lsfml-system -lfmodex -L./lib/FMOD -Wl,--rpath=./lib/FMOD

CXX=		g++

RM=		rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJ) *~ *#

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
