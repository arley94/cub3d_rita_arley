/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:58:00 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/25 10:34:49 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Calculate the maximum number of columns to get map size (max x)
int	get_biggest_lenght(t_data *data)
{
	int	x;
	int	y;
	int	columns;

	y = 0;
	columns = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x] && data->map->map[y][x] != '\n')
			x++;
		if (x >= columns)
			columns = x;
		y++;
	}
	return (columns);
}

//Find the direcction of the player
void	player_direction(t_data *data)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < data->lines)
	{
		while (x < data->columns)
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
		x = 0;
		y++;
	}
}
