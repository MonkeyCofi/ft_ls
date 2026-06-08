NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS := main.c queue.c

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)