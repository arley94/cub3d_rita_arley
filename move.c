/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:30:38 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 16:57:48 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *data)
{
	double	x;
	double	y;

	x = data->player.x + data->player.dir_x * data->player.move_speed;
	y = data->player.y + data->player.dir_y * data->player.move_speed;
	if (data->map[(int)data->player.y][(int)x] != '1')
		data->player.x += data->player.dir_x * data->player.move_speed;
	if (data->map[(int)y][(int)data->player.x] != '1')
		data->player.y += data->player.dir_y * data->player.move_speed;
}

void	move_backwards(t_data *data)
{
	double	x;
	double	y;

	x = data->player.x - data->player.dir_x * data->player.move_speed;
	y = data->player.y - data->player.dir_y * data->player.move_speed;
	if (data->map[(int)data->player.y][(int)x] != '1')
		data->player.x -= data->player.dir_x * data->player.move_speed;
	if (data->map[(int)y][(int)data->player.x] != '1')
		data->player.y -= data->player.dir_y * data->player.move_speed;
}

void	move_right(t_data *data)
{
	double	x;
	double	y;

	x = data->player.x - data->player.dir_y * data->player.move_speed;
	y = data->player.y + data->player.dir_x * data->player.move_speed;
	if (data->map[(int)data->player.y][(int)x] != '1')
		data->player.x -= data->player.dir_y * data->player.move_speed;
	if (data->map[(int)y][(int)data->player.x] != '1')
		data->player.y += data->player.dir_x * data->player.move_speed;
}

void	move_left(t_data *data)
{
	double	x;
	double	y;

	x = data->player.x + data->player.dir_y * data->player.move_speed;
	y = data->player.y - data->player.dir_x * data->player.move_speed;
	if (data->map[(int)data->player.y][(int)x] != '1')
		data->player.x += data->player.dir_y * data->player.move_speed;
	if (data->map[(int)y][(int)data->player.x] != '1')
		data->player.y -= data->player.dir_x * data->player.move_speed;
}
