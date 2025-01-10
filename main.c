/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:17:53 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 17:02:23 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	init_data(t_data **data)
{
	*data = ft_calloc(sizeof(t_data), 1);
	if (!(*data))
		exit_error("Error allocating memory", *data);
	(*data)->cub_text = ft_calloc(2, sizeof(char *));
	(*data)->rgb = ft_calloc(3, sizeof(char *));
	(*data)->xpm = ft_calloc(5, sizeof(char *));
	if (!((*data)->cub_text) || !((*data)->rgb) || !((*data)->xpm))
		exit_error("Error allocating memory", *data);
	return (0);
}

//IF IN MAC MASK 0.
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2 || !check_cub(argv[1]))
	{
		ft_printf("Error\nINVALID ARGUMENT\n");
		return (1);
	}
	init_data(&data);
	check_file(argv[1], data);
	init_win(data);
	init_player(data);
	mlx_loop_hook(data->mlx, init_map, data);
	mlx_hook(data->win, KEY_PRESS, (1L << 0), &key_press, data);
	mlx_hook(data->win, KEY_RELEASE, (1L << 1), &key_release, data);
	mlx_hook(data->win, SCREEN_X, 0, &close_window, data);
	mlx_loop(data->mlx);
	return (0);
}
