/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:18:14 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/25 15:33:13 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void free_map(t_data *data)
{
    int i;

    i = 0;
    if (data->map->map)
	{
		while (data->map->map[i])
		{
			free(data->map->map[i]);
			i++;
		}
	}
}

int close_window(t_data *data)
{
	ft_printf("BYE BYE");
	if (data->mlx)
	{
		if (data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_map(data);
	exit (EXIT_SUCCESS);
}