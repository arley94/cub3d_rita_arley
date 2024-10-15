/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:17:53 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/15 13:13:14 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_data(t_data *data)
{
	data->map = (t_map *)malloc(sizeof(t_map));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !check_cub(argv[1]))
	{
		ft_printf("Error\nINVALID ARGUMENT\n");
		return (1);
	}
	init_data(&data);
	check_file(argv[1], &data);
	init_win(&data);
	data.key.p = 1;
	mlx_loop_hook(data.mlx, init_map, NULL);
	mlx_hook(data.win, KEY_PRESS, 0, &key_press, NULL);
	mlx_hook(data.win, KEY_RELEASE, 0, &key_release, NULL);
	mlx_hook(data.win, SCREEN_X, 0, &close_window, NULL);
	mlx_loop(data.mlx);
	return (0);
}
