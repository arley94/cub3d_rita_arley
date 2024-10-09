/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:17:53 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/09 11:23:34 by ritavasques      ###   ########.fr       */
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
		return (ft_printf("Error\nINVALID ARGUMENT\n"));
	init_data(&data);
	data.map->map = read_map(argv[1]);
	data.lines = ft_line_count(data.map->map);
	data.columns = get_biggest_lenght(&data);
	if (!map_ok(&data))
	{
		free_map(&data);
		free(data.map->map);
		ft_printf("Error\nINVALID MAP\n");
		exit(EXIT_SUCCESS);
	}
	
	return (0);
}
