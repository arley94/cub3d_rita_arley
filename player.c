/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:14:33 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/04 23:37:16 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//FIND PLAYER POSITION
static void	player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'W' || data->map[y][x] == 'E')
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
static void	player_direction(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N')
				data->player_dir = NORTH;
			else if (data->map[y][x] == 'S')
				data->player_dir = SOUTH;
			else if (data->map[y][x] == 'E')
				data->player_dir = EAST;
			else if (data->map[y][x] == 'W')
				data->player_dir = WEST;
			x++;
		}
		y++;
	}
}

static void	set_player_direction(double dir_x, double dir_y, t_player *player)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

static void	set_player_plane(double plane_x, double plane_y, t_player *player)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

void	init_player(t_data *data)
{
	player_position(data);
	player_direction(data);
	if (data->player_dir == NORTH)
	{
		set_player_direction(0, -1, &(data->player));
		set_player_plane(0.66, 0, &(data->player));
	}
	else if (data->player_dir == SOUTH)
	{
		set_player_direction(0, 1, &(data->player));
		set_player_plane(-0.66, 0, &(data->player));
	}
	else if (data->player_dir == EAST)
	{
		set_player_direction(1, 0, &(data->player));
		set_player_plane(0, 0.66, &(data->player));
	}
	else if (data->player_dir == WEST)
	{
		set_player_direction(-1, 0, &(data->player));
		set_player_plane(0, -0.66, &(data->player));
	}
}
