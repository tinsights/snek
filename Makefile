NAME = snek

CFLAGS = -Wall -Werror -Wextra -O3
INC = -I $(INCDIR)

SRCDIR = srcs/
INCDIR = incs/

SRCS = $(addprefix $(SRCDIR), snek.c)
HDRS = $(addprefix $(INCDIR), snek.h)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	cc $(CFLAGS) $(OBJS) $(INC) -lncurses -o $(NAME)

$(SRCDIR)%.o: $(SRCDIR)%.c $(HDRS)
	cc $(CFLAGS) -c $< $(INC) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re