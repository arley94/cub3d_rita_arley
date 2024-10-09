/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:30:38 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/09 12:53:32 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int move_forward(t_data *data)
{
	double	x;
	double	y;

	x = data->player.x + data->player.dir_x * data->player.move_speed;
	y = data->player.y + data->player.dir_y * data->player.move_speed;	
	if (data->map->map[data->player.y][(int)x] == 0)
		data->player.x += data->player.dir_x * data->player.move_speed;
	if (data->map->map[(int)y][data->player.x] == 0)
		data->player.y += data->player.dir_y * data->player.move_speed;
	return (1);
}

int	move_backwards(t_data *data)
{
	double	x;
	double	y;

	x = data->player.x - data->player.dir_x * data->player.move_speed;
	y = data->player.y - data->player.dir_y * data->player.move_speed;	
	if (data->map->map[data->player.y][(int)x] == 0)
		data->player.x -= data->player.dir_x * data->player.move_speed;
	if (data->map->map[(int)y][data->player.x] == 0)
		data->player.y -= data->player.dir_y * data->player.move_speed;
	return (-1);
}

//both camera direction and camera plane must rotate
int	rotate_right(t_data *data)
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	rot_sp;

	rot_sp = data->player.rotation_speed;
	prev_dir_x = data->player.dir_x;
	prev_plane_x = data->player.plane_x;	
	data->player.dir_x = data->player.dir_x * cos(-rot_sp) - data->player.dir_y * sin(-rot_sp);
	data->player.dir_y = prev_dir_x * sin(-rot_sp) + data->player.dir_y * cos(-rot_sp);
    data->player.plane_x = data->player.plane_x * cos(-rot_sp) - data->player.plane_y * sin(-rot_sp);
    data->player.plane_y = prev_plane_x * sin(-rot_sp) + data->player.plane_y * cos(-rot_sp);
	return (1);
}

//both camera direction and camera plane must rotate
int	rotate_left(t_data *data)
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	rot_sp;

	rot_sp = data->player.rotation_speed;
	prev_dir_x = data->player.dir_x;
	prev_plane_x = data->player.plane_x;	
	data->player.dir_x = data->player.dir_x * cos(rot_sp) - data->player.dir_y * sin(rot_sp);
	data->player.dir_y = prev_dir_x * sin(rot_sp) + data->player.dir_y * cos(rot_sp);
    data->player.plane_x = data->player.plane_x * cos(rot_sp) - data->player.plane_y * sin(rot_sp);
    data->player.plane_y = prev_plane_x * sin(rot_sp) + data->player.plane_y * cos(rot_sp);
	return (-1);
}