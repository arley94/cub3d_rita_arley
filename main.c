/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:17:53 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/16 17:14:46 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_data(t_data *data)
{
	data->map = (t_map *)malloc(sizeof(t_map));
	data->xpm = malloc(sizeof(char *) * 5);
	data->rgb = malloc(sizeof(char *) * 3);
}

//CHECKER
void	printmap(t_data *data)
{
	int x;
	int y;
	
	y = data->map->start_y;
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
	data.map->start_y = get_map_start(&data);
	init_win(&data);
	/*data.key.p = 1;
	mlx_loop_hook(data.mlx, init_map, NULL);
	mlx_hook(data.win, KEY_PRESS, 0, &key_press, NULL);
	mlx_hook(data.win, KEY_RELEASE, 0, &key_release, NULL);
	mlx_hook(data.win, SCREEN_X, 0, &close_window, NULL);
	mlx_loop(data.mlx);*/
	return (0);
}
