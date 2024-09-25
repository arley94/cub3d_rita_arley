/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:02:21 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/25 13:36:35 by ritavasques      ###   ########.fr       */
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
# define WIN_WIDTH 640
# define WIN_HEIGHT 360

//DIRECTION
typedef enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}	t_direction;

//MAP
typedef struct s_map
{
	char	**map;
	void	*img;
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
	
}	t_player;

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

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*size_x;
	int			*size_y;
	int			lines;
	int			columns;
	t_direction	player_dir;		
	t_map		*map;
	t_player	player;
	t_ray		ray;
}			t_data;

//CHECK MAP
char    **read_map( char *map);
int		check_cub(char *str);
int		map_ok(t_data *data);

//EXIT & FREE
void	free_map(t_data *data);

//AUX
int	get_biggest_lenght(t_data *data);

//RAY
void ray_direction(t_data *data, int x);
void delta_distance(t_data *data);
void step_side_distance(t_data *data);
void dda_algorithm(t_data *data);

#endif