/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:50:28 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 15:57:32 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Calculate ray direction
void	ray_direction(int x, t_data *data)
{
	data->ray.camera_plane = 2 * x / (double) WIN_WIDTH - 1;
	data->ray.dir_x = data->player.dir_x + data->player.plane_x * data->ray.camera_plane;
	data->ray.dir_y = data->player.dir_y + data->player.plane_y * data->ray.camera_plane;
}

void	init_position(t_data *data)
{
	data->ray.map_x = (int) data->player.x;
	data->ray.map_y = (int) data->player.y;
	data->ray.hit = 0;
}

//Calculate delta distance: 
//distance ray must travel to reach the next grid line in x and y
void	delta_distance(t_data *data)
{
	data->ray.delta_dist_x = (data->ray.dir_x == 0) ? 1e30 : fabs(1 / data->ray.dir_x);
	data->ray.delta_dist_y = (data->ray.dir_y == 0) ? 1e30 : fabs(1 / data->ray.dir_y);
}

//Calculate step & side distance:
//step: direction in which the ray moves through the grid
//side distance: distance ray must travel from current position to the next grid line in the x or y direction
void	step_side_distance(t_data *data)
{
	if (data->ray.dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.x - data->ray.map_x) * data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.x) * data->ray.delta_dist_x;
	}
	if (data->ray.dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.y - data->ray.map_y) * data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.y) * data->ray.delta_dist_y;
	}
}

//loop that increments ray with 1 every time until wall hit. 0 for x and 1 for y.
void    dda_algorithm(t_data *data)
{
	while (!data->ray.hit)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_y][data->ray.map_x] == '1')
		{
		   data->ray.hit = 1;
		   set_texture(data);
		}
	}
}

//Calculate wall distance
void wall_distance(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.wall_dist = data->ray.side_dist_x - data->ray.delta_dist_x;
	else
		data->ray.wall_dist = data->ray.side_dist_y - data->ray.delta_dist_y;
}

//Calculate wall height
//Find draw start and end.
//wall_x represents the exact value where the wall was hit
void	wall_data(t_data *data)
{
	data->ray.line_height = (int)(WIN_HEIGHT / data->ray.wall_dist);
	data->ray.draw_start = (WIN_HEIGHT / 2) - (data->ray.line_height / 2);
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = (WIN_HEIGHT / 2) + (data->ray.line_height / 2);
	if (data->ray.draw_end >= WIN_HEIGHT)
		data->ray.draw_end = WIN_HEIGHT - 1;
	if (data->ray.side == 0)
		data->ray.wall_x = data->player.y + data->ray.wall_dist * data->ray.dir_y;
	else
		data->ray.wall_x = data->player.x + data->ray.wall_dist * data->ray.dir_x;
	data->ray.wall_x -= floor(data->ray.wall_x);
}

void    raycasting(t_data *data)
{
	int x;
	
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_direction(x, data);
		init_position(data);
		delta_distance(data);
		step_side_distance(data);
		dda_algorithm(data);
		wall_distance(data);
		wall_data(data);
		get_texture_x(data);
		draw_texture(x, data);
		x++;
	}
}
