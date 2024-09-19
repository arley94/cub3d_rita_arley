NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmmlx -lmlx -framework OpenGL -framework Appkit

LIBFT = libft/libft.a
MLX = mlx/libmlx.a

#SOURCE FILES
SRC =	main.c \

#OBJECT FILES
OBJ = $(SRC:%.c=%.o) 

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make all -C libft/

$(MLX):
	@make all -C mlx

%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@make clean -C ./libft
	@make clean -C ./mlx

fclean: clean
	@make fclean -C ./libft
	@make fclean -C ./mlx
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re