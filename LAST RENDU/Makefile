##
## Makefile for Makefile in /home/sarkad_l/rendu/piscine_cpp_d01/ex01
## 
## Made by lucas sarkadi
## Login   <sarkad_l@epitech.net>
## 
## Started on  Wed Jan  8 12:46:27 2014 lucas sarkadi
## Last update Sat Dec 27 16:10:56 2014 thibaud dahan
##

CXX =	g++

RM =	rm -f

CXXFLAGS += -g -g3

NAMEONE = RTypeServLast/server

NAMETWO = RTypeLucas/client 

SRCSONE = RTypeServLast/main.cpp \
	  RTypeServLast/Message.cpp \
	  RTypeServLast/Selector.cpp \
	  RTypeServLast/Server.cpp \
	  RTypeServLast/Client.cpp \
	  RTypeServLast/TCPLinServSocket.cpp \
	  RTypeServLast/CircularBuff.cpp \
	  RTypeServLast/CommandHandler.cpp \
	  RTypeServLast/LinThread.cpp \
	  RTypeServLast/Room.cpp \
	  RTypeServLast/UDPLinServSocket.cpp \
	  RTypeServLast/LinDllLoader.cpp \
	  RTypeServLast/Spawner.cpp \
	  RTypeServLast/Shots.cpp \
	  RTypeServLast/ClockObj.cpp \

SRCSTWO = RTypeLucas/CircularBuff.cpp \
	  RTypeLucas/Client.cpp \
	  RTypeLucas/main.cpp \
	  RTypeLucas/Message.cpp \
	  RTypeLucas/Selector.cpp \
	  RTypeLucas/TCPLinSocket.cpp \
	  RTypeLucas/UDPLinSocket.cpp \
	  RTypeLucas/CommandHandler.cpp \
	  RTypeLucas/Room.cpp \
	  RTypeLucas/AMenu.cpp \
	  RTypeLucas/AMovingObject.cpp \
	  RTypeLucas/BaseMenu.cpp \
	  RTypeLucas/CreateRoomMenu.cpp \
	  RTypeLucas/Gui.cpp \
	  RTypeLucas/HeroObject.cpp \
	  RTypeLucas/HudTextField.cpp \
	  RTypeLucas/HudWindow.cpp \
	  RTypeLucas/InRoomMenu.cpp \
	  RTypeLucas/JoinRoomMenu.cpp \
	  RTypeLucas/LoginMenu.cpp \
	  RTypeLucas/RoomFirstMenu.cpp \
	  RTypeLucas/ScrollingBg.cpp \
	  RTypeLucas/AllyObject.cpp \
	  RTypeLucas/ShotEntity.cpp \
	  RTypeLucas/ShotsObject.cpp \
	  RTypeLucas/MonsterEntity.cpp \
	  RTypeLucas/MonstersObject.cpp \


OBJSONE	= $(SRCSONE:.cpp=.o)

OBJSTWO	= $(SRCSTWO:.cpp=.o)

all:	$(NAMEONE) $(NAMETWO)

server: $(NAMEONE)

client: $(NAMETWO)

$(NAMEONE): $(OBJSONE) 
	    $(CXX) $(OBJSONE) -o $(NAMEONE)  -lpthread -export-dynamic -ldl
	    cp $(NAMEONE) .

$(NAMETWO): $(OBJSTWO)
	    $(CXX) $(OBJSTWO) -o $(NAMETWO) -lpthread -lsfml-graphics -lsfml-window -lsfml-system
	    cp $(NAMETWO) .

clean:
	$(RM) $(OBJSONE) $(OBJSTWO)

fclean: clean
	$(RM) client server
	$(RM) $(NAMEONE) $(NAMETWO)

re: fclean all

.PHONY: all clean fclean re


