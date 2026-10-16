NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes
AR			= ar rcs
RM			= rm -rf

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= ft_is/ft_isalnum.c \
			  ft_is/ft_isalpha.c \
			  ft_is/ft_isascii.c \
			  ft_is/ft_isdigit.c \
			  ft_is/ft_isprint.c \
			  ft_mem/ft_bzero.c \
			  ft_mem/ft_calloc.c \
			  ft_mem/ft_memchr.c \
			  ft_mem/ft_memcmp.c \
			  ft_mem/ft_memcpy.c \
			  ft_mem/ft_memmove.c \
			  ft_mem/ft_memset.c \
			  ft_put/ft_putchar_fd.c \
			  ft_put/ft_putendl_fd.c \
			  ft_put/ft_putnbr_fd.c \
			  ft_put/ft_putstr_fd.c \
			  ft_str/ft_split.c \
			  ft_str/ft_strchr.c \
			  ft_str/ft_strdup.c \
			  ft_str/ft_striteri.c \
			  ft_str/ft_strjoin.c \
			  ft_str/ft_strlcat.c \
			  ft_str/ft_strlcpy.c \
			  ft_str/ft_strlen.c \
			  ft_str/ft_strmapi.c \
			  ft_str/ft_strncmp.c \
			  ft_str/ft_strnstr.c \
			  ft_str/ft_strrchr.c \
			  ft_str/ft_strtrim.c \
			  ft_str/ft_substr.c \
			  ft_to/ft_atoi.c \
			  ft_to/ft_itoa.c \
			  ft_to/ft_tolower.c \
			  ft_to/ft_toupper.c \
			  ft_printf/ft_print_bx.c \
			  ft_printf/ft_print_c.c \
			  ft_printf/ft_print_d.c \
			  ft_printf/ft_printf.c \
			  ft_printf/ft_print_p.c \
			  ft_printf/ft_print_s.c \
			  ft_printf/ft_print_u.c \
			  ft_printf/ft_print_x.c \
			  ft_printf/ft_putnbr_base.c \
			  ft_printf/ft_size.c \
			  gnl/get_next_line.c

SRCS_BONUS	= ft_lst/ft_lstadd_back_bonus.c \
			  ft_lst/ft_lstadd_front_bonus.c \
			  ft_lst/ft_lstclear_bonus.c \
			  ft_lst/ft_lstdelone_bonus.c \
			  ft_lst/ft_lstiter_bonus.c \
			  ft_lst/ft_lstlast_bonus.c \
			  ft_lst/ft_lstmap_bonus.c \
			  ft_lst/ft_lstnew_bonus.c \
			  ft_lst/ft_lstsize_bonus.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)
	@touch .bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) .bonus

re: fclean all

norm:
	@norminette $(addprefix $(SRC_DIR)/, $(SRCS) $(SRCS_BONUS)) includes | grep -v Norme -B1 || true

.PHONY: all bonus clean fclean re norm
