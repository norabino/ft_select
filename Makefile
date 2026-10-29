NAME    = ft_select
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
INC     = -I includes -I libft/includes
LIBFT   = libft/libft.a
LDLIBS  = -lncurses
VGFLAGS = --leak-check=full --show-leak-kinds=all --track-fds=yes \
		  --suppressions=ncurses.supp --log-file=valgrind.log
ARGS    ?= a b c d
SRCS    = src/input/arrows.c src/input/keycaps.c src/signal/handlers.c src/signal/init_signals.c \
			src/terminal/terminal_utils.c src/terminal/terminfo.c src/ft_select.c src/init.c \
				src/main.c src/parsing.c src/print.c src/utils.c

OBJS    = $(SRCS:src/%.c=obj/%.o)

all: libft $(NAME)

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)

obj/%.o: src/%.c includes/ft_select.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -rf obj

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME) valgrind.log

re: fclean all

#utilisation : make valgrind ARGS="un deux trois" avec tes propres arguments
valgrind: all
	-valgrind $(VGFLAGS) ./$(NAME) $(ARGS)
	@cat valgrind.log

.PHONY: all libft clean fclean re valgrind