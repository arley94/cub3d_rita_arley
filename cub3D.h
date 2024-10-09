/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:02:21 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/09 12:39:46 by ritavasques      ###   ########.fr       */
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

//SCREEN & TEXTURES
# define WIN_WIDTH 640
# define WIN_HEIGHT 360
# define TEXTURE_SIZE 64
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

typedef enum e_arrow
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_arrow;

//TEXTURES - IMG
typedef struct s_img
{
	char			*path;
	void 			*img;
	int				*addr;
	int				line_lenght;
	int				bits_per_pixel;
	int				endian;
	int				width;
	int				height;
}			t_img;

//MAP
typedef struct s_map
{
	char	**map;
	int		start_x;
	int		start_y;
}			t_map;

//PLAYER
typedef struct s_player
{
	int			x;
	int			y;
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
	double	camera_plane;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}	t_ray;

//FRAMES PER SECOND
typedef struct s_fps
{
	double	time;
	double	old_time;
	double	frametime;
}			t_fps;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			lines; //Map height
	int			columns; //Map width
	int			**pixels;
	int			floor;
	int			ceiling;
	t_direction	player_dir;		
	t_map		*map;
	t_player	player;
	t_ray		ray;
	t_fps		fps;
	t_img		img;
}			t_data;

//CHECK MAP
char    **read_map( char *map);
int		check_cub(char *str);
int		map_ok(t_data *data);

//PLAYER
void	init_player(t_data *data);

//EXIT & FREE
void	free_map(t_data *data);
int 	close_window(t_data *data);

//AUX
int	get_biggest_lenght(t_data *data);

//RAY
void ray_direction(t_data *data, int x);
void delta_distance(t_data *data);
void step_side_distance(t_data *data);
void dda_algorithm(t_data *data);
double wall_distance(t_data *data);
void	wall_data(t_data *data);
void raycasting(t_data *data);

//DRAW

#endif