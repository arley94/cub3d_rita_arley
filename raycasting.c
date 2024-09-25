/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:15:51 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/25 13:40:38 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Calculate wall distance
//wall_x represents the exact value where the wall was hit
static void wall_distance(t_data *data)
{
	if (data->ray.side == 0)
	{
		data->ray.wall_dist = data->ray.side_dist_x - data->ray.delta_dist_x;
		data->ray.wall_x = data->player.y + data->ray.wall_dist * data->ray.dir_y;
	}
	else
	{
		data->ray.wall_dist = data->ray.side_dist_y - data->ray.side_dist_y;
		data->ray.wall_x = data->player.x + data->ray.wall_dist * data->ray.dir_x;
	}
	data->ray.wall_x -= floor(data->ray.wall_x);
}

//Calculate wall height:
//based on distance to the wall and player view, find draw start and end.
static void	wall_height(t_data *data)
{
	data->ray.line_height = (int)(WIN_HEIGHT / data->ray.wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + WIN_HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + WIN_HEIGHT / 2;
	if (data->ray.draw_end >= WIN_HEIGHT)
		data->ray.draw_end = WIN_HEIGHT - 1;
}

void raycasting(t_data *data)
{
	int i;

	i = 0;
	while ( i < WIN_WIDTH)
	{
		data->ray.hit = 0;
		ray_direction(data, i);
		delta_distance(data);
		step_side_distance(data);
		dda_algorithm(data);
		wall_distance(data);
		wall_height(data);
		//missing draw/textures
		i++;
	}	
}