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
	data->ray.dir_x = data->player.dir_x
		+ data->player.plane_x * data->ray.camera_plane;
	data->ray.dir_y = data->player.dir_y
		+ data->player.plane_y * data->ray.camera_plane;
}

//Calculate delta distance: 
//distance ray must travel to reach the next grid line in x and y
void	delta_distance(t_data *data)
{
	if (data->ray.dir_x == 0)
		data->ray.delta_dist_x = 1e30;
	else
		data->ray.delta_dist_x = fabs(1 / data->ray.dir_x);
	if (data->ray.dir_y == 0)
		data->ray.delta_dist_y = 1e30;
	else
		data->ray.delta_dist_y = fabs(1 / data->ray.dir_y);
}

//Calculate step & side distance:
//step: direction in which the ray moves through the grid
//side distance: distance ray must travel from current position 
//to the next grid line in the x or y direction
void	step_side_distance(t_data *data)
{
	if (data->ray.dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.y)
			* data->ray.delta_dist_y;
	}
}

//loop that increments ray with 1 every time 
//until wall hit. 0 for x and 1 for y.
void	dda_algorithm(t_data *data)
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
