/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:06:04 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/09 12:39:04 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Creates window, load images and set the hooks
void	manage_win(t_data *data)
{
	data->mlx = mlx_init();
    if (!data->mlx)
        close_window(data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!data->win)
        close_window(data);
	//fill_map(data);
	//mlx_key_hook(data->win, &move_player, data);
	//mlx_hook(data->win, 17, 0, &close_window, data);
}