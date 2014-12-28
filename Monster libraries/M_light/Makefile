NAME_LIBA = M_light.so
SRC_LIBA =  M_light/AMonster.cpp \
	   M_light/M_light.cpp

NAME_LIBB = M_medium.so
SRC_LIBB =  M_medium/AMonster.cpp \
	    M_medium/M_medium.cpp

NAME_LIBC = M_heavy.so
SRC_LIBC =  M_heavy/AMonster.cpp \
	   M_heavy/M_heavy.cpp

NAME_LIBD = M_boss.so
SRC_LIBD =  M_boss/AMonster.cpp \
	   M_boss/M_boss.cpp

OBJ_LIBA = $(SRC_LIBA:.cpp=.o)
OBJ_LIBB = $(SRC_LIBB:.cpp=.o)
OBJ_LIBC = $(SRC_LIBC:.cpp=.o)
OBJ_LIBD = $(SRC_LIBD:.cpp=.o)

CXX = g++

CXXFLAGS += -fPIC

all: $(NAME_LIBA) $(NAME_LIBB) $(NAME_LIBC) $(NAME_LIBD)

$(NAME_LIBA): $(OBJ_LIBA)
	$(CXX) -shared  -o $(NAME_LIBA) $(OBJ_LIBA) 

$(NAME_LIBB): $(OBJ_LIBB)
	$(CXX) -shared  -o $(NAME_LIBB) $(OBJ_LIBB) 

$(NAME_LIBC): $(OBJ_LIBC)
	$(CXX) -shared  -o $(NAME_LIBC) $(OBJ_LIBC) 

$(NAME_LIBD): $(OBJ_LIBD)
	$(CXX) -shared  -o $(NAME_LIBD) $(OBJ_LIBD) 

clean:
	rm -f $(OBJ_LIBA)
	rm -f $(OBJ_LIBB)
	rm -f $(OBJ_LIBC)
	rm -f $(OBJ_LIBD)

fclean: clean
	rm -f $(NAME_LIBA)
	rm -f $(NAME_LIBB)
	rm -f $(NAME_LIBC)
	rm -f $(NAME_LIBD)

re: clean fclean all
