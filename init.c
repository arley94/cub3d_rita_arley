/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:05:58 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/24 11:34:48 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Initial map
int   init_map(t_data *data)
{
	data->frame_time = 16 / 1000.0;
	data->player.move_speed = data->frame_time * 5.0;
	data->player.rotation_speed = data->frame_time * 3.0;
    data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_lenght, &data->img.endian);
	draw_ceiling(data);
	draw_ceiling(data);
	raycasting(data);
	key_hooks(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
	return (0);
}

//Creates window
void	init_win(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Something wrong with mlx!", data);
	if (init_textures(data))
		exit_error("Problem with textures!", data);
	if (get_colors(data))
		exit_error("Problem with colors!", data);
	if (map_ok(data))
		exit_error("Invalid map!", data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!data->win)
		exit_error("Cannot create window!", data);
}
