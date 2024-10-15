/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:14:33 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/15 12:21:23 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//FIND PLAYER POSITION
static void	player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'N' || data->map->map[y][x] == 'S' || data->map->map[y][x] == 'W' || data->map->map[y][x] == 'E')
			{
				data->player.y = y + 0.5;
				data->player.x = x + 0.5;
			}
			x++;
		}
		y++;
	}
}

//FIND DIRECTION OF PLAYER
static int	player_direction(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'N')
				data->player_dir = NORTH;
			else if (data->map->map[y][x] == 'S')
				data->player_dir = SOUTH;
			else if (data->map->map[y][x] == 'E')
				data->player_dir = EAST;
			else if (data->map->map[y][x] == 'W')
				data->player_dir = WEST;
			x++;
		}
		y++;
	}
    return (0);
}

//INIT PLAYER 
//SEPARAR VERTICAL Y HORIZONTAL
void	init_player(t_data *data)
{	
	player_position(data);
    data->player_dir = player_direction(data);
	if (data->player_dir == NORTH)
    {
       
        data->player.dir_x = 0;
        data->player.dir_y = -1;
        data->player.plane_x = 0.66;
        data->player.plane_y = 0;
    }
    else if (data->player_dir == SOUTH)
    {
        data->player.dir_x = 0;
        data->player.dir_y = 1;
        data->player.plane_x = -0.66;
        data->player.plane_y = 0;       
    }
    else if (data->player_dir == EAST)
    {
        data->player.dir_x = 1;
        data->player.dir_y = 0;
        data->player.plane_x = 0;
        data->player.plane_y = 0.66;
    } 
    else if (data->player_dir == WEST)
	{
        data->player.dir_x = -1;
        data->player.dir_y = 0;
        data->player.plane_x = 0;
        data->player.plane_y = -0.66;
	}
}
