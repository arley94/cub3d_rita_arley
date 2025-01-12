/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:05:58 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/12 11:34:40 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//both camera direction and camera plane must rotate
void	rotate_right(t_data *data)
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	rot_sp;

	rot_sp = data->player.rotation_speed;
	prev_dir_x = data->player.dir_x;
	prev_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(rot_sp) - data->player.dir_y
		* sin(rot_sp);
	data->player.dir_y = prev_dir_x * sin(rot_sp) + data->player.dir_y
		* cos(rot_sp);
	data->player.plane_x = data->player.plane_x * cos(rot_sp)
		- data->player.plane_y * sin(rot_sp);
	data->player.plane_y = prev_plane_x * sin(rot_sp) + data->player.plane_y
		* cos(rot_sp);
}

//both camera direction and camera plane must rotate
void	rotate_left(t_data *data)
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	rot_sp;

	rot_sp = data->player.rotation_speed;
	prev_dir_x = data->player.dir_x;
	prev_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(-rot_sp) - data->player.dir_y
		* sin(-rot_sp);
	data->player.dir_y = prev_dir_x * sin(-rot_sp) + data->player.dir_y
		* cos(-rot_sp);
	data->player.plane_x = data->player.plane_x * cos(-rot_sp)
		- data->player.plane_y * sin(-rot_sp);
	data->player.plane_y = prev_plane_x * sin(-rot_sp) + data->player.plane_y
		* cos(-rot_sp);
}

//Check that map rules apply
int	map_ok(t_data *data)
{
	if (check_components(data))
		return (1);
	if (check_player(data))
		return (1);
	if (check_map_walls(data))
		return (1);
	return (0);
}

//Initial map
int	init_map(t_data *data)
{
	data->frame_time = 16 / 1000.0;
	data->player.move_speed = data->frame_time * 5.0;
	data->player.rotation_speed = data->frame_time * 3.0;
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_lenght,
			&data->img.endian);
	draw_ceiling(data);
	draw_floor(data);
	raycasting(data);
	key_hooks(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
	return (0);
}

//Creates window
void	init_win(t_data *data)
{
	if (map_ok(data))
		exit_error("Invalid map!", data);
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Something wrong with mlx!", data);
	if (init_textures(data))
		exit_error("Problem with textures!", data);
	if (get_colors(data))
		exit_error("Problem with colors!", data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		exit_error("Cannot create window!", data);
}
