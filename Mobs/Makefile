SRCMOBS=	BydoStd.cpp	\
		BydoZigZag.cpp	\
		FastShooter.cpp	\
		BydoBoss.cpp	\

SRCDEP=		../Server/AMob.cpp		\
		../Server/AEntity.cpp		\
		../Server/BulletInfos.cpp	\
		../Server/Player.cpp		\
		../Server/UnixRandom.cpp

OBJDIR=		./obj

BINDIR=		./bin

OBJ=		$(SRCMOBS:%.cpp=$(OBJDIR)/%.o)

OBJDEP=		$(SRCDEP:../Server/%.cpp=$(OBJDIR)/%.o)

NAMES=		$(SRCMOBS:%.cpp=$(BINDIR)/%.so)

INCLUDE=	-I ../Server

all: $(NAMES)

$(OBJDIR)/%.o : %.cpp
	g++ -fPIC -c $< $(INCLUDE) -o $@

$(OBJDIR)/%.o : ../Server/%.cpp
	g++ -fPIC -c $< $(INCLUDE) -o $@

$(NAMES):	$(BINDIR)/%.so : $(OBJDIR)/%.o $(OBJDEP)
	g++ -fPIC -shared -o $@ $^

clean:
	rm -f $(OBJ) $(OBJDEP)

fclean: clean
	rm -f $(NAMES)

re:	fclean all