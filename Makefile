NAME    = ft_select
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
INC     = -I includes -I libft/includes
LIBFT   = libft/libft.a
LDLIBS  = -lncurses
SRCS    = src/main.c src/state.c

OBJS    = $(SRCS:src/%.c=obj/%.o)

all: libft $(NAME)

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)

obj/%.o: src/%.c includes/ft_select.h
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -rf obj

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all libft clean fclean re