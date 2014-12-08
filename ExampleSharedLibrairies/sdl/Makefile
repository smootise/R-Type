NAME_LIB = lib_nibbler_SDL.so
SRC_LIB = sdl.cpp \

OBJ_LIB = $(SRC_LIB:.cpp=.o)

CXXFLAGS += -fPIC

CXX = g++

all: $(NAME_LIB)

$(NAME_LIB): $(OBJ_LIB)
	$(CXX) -shared -o $(NAME_LIB) $(OBJ_LIB) -lSDL

clean:
	rm -f $(OBJ_LIB)

fclean: clean
	rm -f $(NAME_LIB)

re: clean fclean all
