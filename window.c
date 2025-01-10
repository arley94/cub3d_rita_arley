/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:06:04 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 14:44:42 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Creates window
void	init_win(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Something wrong with mlx!", data);
	if (map_ok(data))
		exit_error("Invalid map!", data);
	if (get_colors(data) || init_textures(data))
		exit_error("Problem with colors or textures!", data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		exit_error("Cannot create window!", data);
}
