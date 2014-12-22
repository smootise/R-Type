##
## Makefile for Makefile in /home/sarkad_l/rendu/piscine_cpp_d01/ex01
## 
## Made by lucas sarkadi
## Login   <sarkad_l@epitech.net>
## 
## Started on  Wed Jan  8 12:46:27 2014 lucas sarkadi
## Last update Mon Dec 22 17:11:16 2014 corentin bajdek
##

CXX =	g++

RM =	rm -f

CXXFLAGS += -g -g3

NAMEONE = R-TypeServer/server

NAMETWO = RTypeLucas/client 

SRCSONE = R-TypeServer/main.cpp \
	  R-TypeServer/Message.cpp \
	  R-TypeServer/Selector.cpp \
	  R-TypeServer/Server.cpp \
	  R-TypeServer/Client.cpp \
	  R-TypeServer/TCPLinServSocket.cpp \
	  R-TypeServer/CircularBuff.cpp \
	  R-TypeServer/CommandHandler.cpp \
	  R-TypeServer/LinThread.cpp \
	  R-TypeServer/Room.cpp \
	  R-TypeServer/UDPLinServSocket.cpp

SRCSTWO = RTypeLucas/CircularBuff.cpp \
	  RTypeLucas/Client.cpp \
	  RTypeLucas/main.cpp \
	  RTypeLucas/Message.cpp \
	  RTypeLucas/Selector.cpp \
	  RTypeLucas/TCPLinSocket.cpp \
	  RTypeLucas/UDPLinSocket.cpp \
	  RTypeLucas/CommandHandler.cpp \
	  RTypeLucas/Room.cpp

OBJSONE	= $(SRCSONE:.cpp=.o)

OBJSTWO	= $(SRCSTWO:.cpp=.o)

all:	$(NAMEONE) $(NAMETWO)

server: $(NAMEONE)

client: $(NAMETWO)

$(NAMEONE): $(OBJSONE) 
	    $(CXX) $(OBJSONE) -o $(NAMEONE)  -lpthread
	    cp $(NAMEONE) .

$(NAMETWO): $(OBJSTWO)
	    $(CXX) $(OBJSTWO) -o $(NAMETWO) -lpthread
	    cp $(NAMETWO) .

clean:
	$(RM) $(OBJSONE) $(OBJSTWO)

fclean: clean
	$(RM) client server
	$(RM) $(NAMEONE) $(NAMETWO)

re: fclean all

.PHONY: all clean fclean re


