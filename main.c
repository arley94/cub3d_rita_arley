/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:17:53 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/25 11:04:24 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_data(t_data *data)
{
	data->map = (t_map *)malloc(sizeof(t_map));
}

static void	init_map(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	while (y < data->lines)
	{
		x = 0;
		while (x < data->columns)
		{
			if (data->map->map[y][x] == 'N' || data->map->map[y][x] == 'S' ||
				data->map->map[y][x] == 'E' || data->map->map[y][x] == 'W')
			{
				data->player.y = y;
				data->player.x = x;
			}
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !check_cub(argv[1]))
		return (ft_printf("Error\nINVALID ARGUMENT\n"));
	init_data(&data);
	data.map->map = read_map(argv[1]);
	data.lines = ft_line_count(data.map->map);
	printf("lines: %d\n", data.lines);
	data.columns = get_biggest_lenght(&data);
	printf("communs: %d\n", data.columns);
	init_map(&data);
	if (!map_ok(&data))
	{
		free_map(&data);
		free(data.map->map);
		ft_printf("Error\nINVALID MAP\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_printf("MAP OK\n");
		free_map(&data);
		free(data.map->map);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
