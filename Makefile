SRCS			= main.cpp matrices.cpp utils.cpp vec.cpp init.cpp control.cpp objloader.cpp vboindexer.cpp texture.cpp coordinate_systems.cpp
INC_HEADERS		= common.hpp
ALL_HEADERS		= $(addprefix includes/,$(INC_HEADERS))
FILES			= $(addprefix srcs/,$(SRCS))
OBJS			= ${FILES:.cpp=.o}
CXX				= g++
NAME			= scop
CXXFLAGS		= -Wall -Wextra -Werror

INC				= ./includes
GLFW			= ./libs/glfw
GLEW			= ./libs/glew

CCLIBS			= `pkg-config --static --libs glfw3 glew`
CCHEADERS		= -I$(INC) -I$(GLFW)/include -I$(GLEW)/include

$(NAME): ${OBJS} 
	${CXX} ${OBJS} -o $(NAME) $(CCLIBS)

all: ${NAME}

%.o: %.cpp $(ALL_HEADERS)
	${CXX} -c ${CXXFLAGS} $< $(CCHEADERS) -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean re fclean
