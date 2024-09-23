/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:58:00 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/23 13:57:17 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

