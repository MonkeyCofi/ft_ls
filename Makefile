NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)

INC_DIR = ./inc

SRCS_DIR := ./srcs

OBJS_DIR := ./objs

SRCS := $(addprefix $(SRCS_DIR)/, queue.c parser.c vector.c main.c)

OBJS := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -L$(LIBFT_DIR) -lft -o $@ 

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -g3 $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
	echo $(OBJS)
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re