NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

#SOURCE FILES
SRC =	main.c \
		check_map.c \
		exit.c \
		aux.c

#OBJECT FILES
OBJ = $(SRC:%.c=%.o) 

#COMPILE IN MAC AND LINUX
ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx$(UNAME).a

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

LIBFT = ./libft/libft.a

all: $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $^ $(CFLAGS) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make all -C ./libft

$(MLX):
	@make all -C $(MLX_DIR)

%.o: src/%.c
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	@rm -rf $(OBJ)
	@make clean -C ./libft
	@make clean -C ./mlx

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re