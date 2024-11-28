NAME = snek

CXXFLAGS = -Wall -Werror -Wextra -O3

SRCDIR = ./srcs/
INCDIR = ./incs/

INC = -I $(INCDIR)

SRCS = $(addprefix $(SRCDIR), snek.cpp)
HDRS = $(addprefix $(INCDIR), snek.hpp)

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	c++ $(CXXFLAGS) $(OBJS) $(INC) -lncurses -o $(NAME)

$(SRCDIR)%.o: $(SRCDIR)%.cpp $(HDRS)
	c++ $(CXXFLAGS) $(INC) -c $<  -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re