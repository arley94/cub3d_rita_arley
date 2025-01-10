/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:18:14 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 15:14:24 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_array(char **array)
{
	int	i;

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
	if (data)
	{
		free_array(data->xpm);
		free_array(data->rgb);
		free_array(data->map);
		free_array(data->cub_text);
		free(data);
	}
	exit(EXIT_FAILURE);
}

int	close_window(t_data *data)
{
	ft_printf("BYE BYE\n");
	if (data)
	{
		if (data->mlx)
		{
			if (data->win != NULL)
				mlx_destroy_window(data->mlx, data->win);
			free(data->mlx);
		}
		free_array(data->xpm);
		free_array(data->rgb);
		free_array(data->map);
		free_array(data->cub_text);
		free(data);
	}
	exit (EXIT_SUCCESS);
}
