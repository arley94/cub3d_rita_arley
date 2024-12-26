/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:18:14 by ritavasques       #+#    #+#             */
/*   Updated: 2024/12/26 18:26:09 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void free_array(char **array)
{
	int i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	exit_error(char *str, t_data *data)
{
	ft_printf("Error\n");
	ft_printf(str);
	ft_printf("\n");
	free_array(data->xpm);
	free_array(data->rgb);
	free_array(data->map);
	exit(EXIT_SUCCESS);
}

int close_window(t_data *data)
{
	ft_printf("BYE BYE\n");
	if (data->mlx)
	{
		if (data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
	}
	free_array(data->xpm);
	free_array(data->rgb);
	free_array(data->map);
	exit (EXIT_SUCCESS);
}