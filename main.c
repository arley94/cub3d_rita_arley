/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:17:53 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/26 13:20:06 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_data(t_data *data)
{
	data->map = ft_calloc(sizeof(char *), 1);
	
}

//CHECKER
void	printmap(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	while (data->map->map[y])
	{
		printf("\n");
		x = 0;
		while (data->map->map[y][x])
		{
			printf("%c", data->map->map[y][x]);
			x++;
		}
		y++;
	}
	printf("\n");
}

//IF IN MAC MASK 0.
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
	init_player(&data);
	init_win(&data);
	data.key.p = 1;
	mlx_loop_hook(data.mlx, init_map, &data);
	//mlx_key_hook(data.win, &key_press, &data);
	mlx_hook(data.win, KEY_PRESS, (1L<<0), &key_press, &data);
	mlx_hook(data.win, KEY_RELEASE, (1L<<1), &key_release, &data);
	mlx_hook(data.win, SCREEN_X, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
