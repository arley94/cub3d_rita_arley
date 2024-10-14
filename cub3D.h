/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:02:21 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/14 12:05:37 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
//TO DELETE
#include <stdio.h>

# define BUFF_SIZE 1000

//KEYS
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define SCREEN_X 17

//SCREEN & TEXTURES
# define WIN_WIDTH 640
# define WIN_HEIGHT 360
# define TEXTURE_HEIGHT 64
# define TEXTURE_WIDTH 64
# define TEXTURES 4
# define FLOOR 0
# define CEILING 1
# define FOV 90 //field of vision

//DIRECTION
typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_direction;

//KEYS
typedef struct s_key
{
	int w;
	int s;
	int a;
	int d;
	int right;
	int left;
	int p;
}		t_key;

//IMG
typedef struct s_img
{
	void 			*img;
	char			*addr;
	int				line_lenght;
	int				bits_per_pixel;
	int				endian;
	int				width;
	int				height;
}			t_img;

//TEXTURE
typedef struct s_texture
{
	void 			*img;
	int				*addr;
	int				line_lenght;
	int				bits_per_pixel;
	int				endian;
	int				width;
	int				height;
}	t_texture;

//PLAYER
typedef struct s_player
{
	double			x;
	double			y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rotation_speed;
}				t_player;

//RAYCASTING
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	camera_plane;
	double wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	wall_dist;
	int		side;
	int				hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**rgb;
	char		**xpm;
	unsigned long			floor;
	unsigned long			ceiling;
	int			textures[4][TEXTURE_HEIGHT * TEXTURE_WIDTH];
	
	double			tex_position;
	int				text_number;
	int				text_y;
	int				text_x;
	unsigned int	color;
	double	frame_time;
	t_direction	player_dir;		
	t_player	player;
	t_ray		ray;
	t_img		img;
	t_texture	texture[4];
	t_key		key;
}			t_data;

//CHECK MAP
int		check_cub(char *str);
int		map_ok(t_data *data);
int	check_textures(int fd, t_data *data);
int	check_file(char *file, t_data *data);

//PLAYER
void	init_player(t_data *data);

//EXIT & FREE
void	exit_error(char *str, t_data *data);
int 	close_window(t_data *data);
void free_array(char **array);

//MOVE
void move_forward(t_data *data);
void	move_backwards(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);
void	rotate_right(t_data *data);
void	rotate_left(t_data *data);

//KEY
void	key_hooks(t_data *data);
int	key_press(int keycode, t_data *data);
int	key_release(int keycode, t_data *data);

//RAY
void ray_direction(int x, t_data *data);
void delta_distance(t_data *data);
void step_side_distance(t_data *data);
void dda_algorithm(t_data *data);
void wall_distance(t_data *data);
void	wall_data(t_data *data);
void raycasting(t_data *data);

//DRAW, COLORS & TEXTURES
int get_colors(t_data *data);
int	init_textures(t_data *data);
void	set_texture(t_data *data);
void	draw_texture(int x, t_data *data);
void	get_texture_x(t_data *data);
void	draw_floor(t_data *data);
void	draw_ceiling(t_data *data);

//INIT
void	init_win(t_data *data);
int   init_map(t_data *data);

#endif