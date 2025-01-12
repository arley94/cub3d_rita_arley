NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

#SOURCE FILES
SRC =	main.c \
		check_map.c \
		exit.c \
		color.c \
		draw.c \
		init.c \
		ray.c \
		ray2.c \
		move.c \
		player.c \
		textures.c \
		keys.c \
		parse_cub.c \
		check_map2.c \
		check_map3.c \
		elements.c

#OBJECT FILES
OBJ = $(SRC:%.c=%.o) 

#COMPILE IN MAC AND LINUX
ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_DIR = ./mlx_linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_DIR = ./mlx_mac
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif


MLX = $(MLX_DIR)/libmlx$(UNAME).a

LIBFT = ./libft/libft.a

all: $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME) -lm

$(LIBFT):
	@make all -C ./libft

$(MLX):
	@make all -C $(MLX_DIR)

%.o: src/%.c
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	@rm -rf $(OBJ)
	@make clean -C ./libft
	@make clean -C $(MLX_DIR)

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re