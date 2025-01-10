/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-10 16:01:57 by acoto-gu          #+#    #+#             */
/*   Updated: 2025-01-10 16:01:57 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_position(t_data *data)
{
	data->ray.map_x = (int) data->player.x;
	data->ray.map_y = (int) data->player.y;
	data->ray.hit = 0;
}

//Calculate wall distance
void	wall_distance(t_data *data)
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
		data->ray.wall_x = data->player.y + data->ray.wall_dist
			* data->ray.dir_y;
	else
		data->ray.wall_x = data->player.x + data->ray.wall_dist
			* data->ray.dir_x;
	data->ray.wall_x -= floor(data->ray.wall_x);
}

void	raycasting(t_data *data)
{
	int	x;

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
