/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:15:51 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 14:52:00 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	else if (keycode == W)
		data->key.w = 1;
	else if (keycode == S)
		data->key.s = 1;
	else if (keycode == A)
		data->key.a = 1;
	else if (keycode == D)
		data->key.d = 1;
	else if (keycode == LEFT)
		data->key.left = 1;
	else if (keycode == RIGHT)
		data->key.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->key.w = 0;
	else if (keycode == S)
		data->key.s = 0;
	else if (keycode == A)
		data->key.a = 0;
	else if (keycode == D)
		data->key.d = 0;
	else if (keycode == LEFT)
		data->key.left = 0;
	else if (keycode == RIGHT)
		data->key.right = 0;
	return (0);
}

void	key_hooks(t_data *data)
{
	if (data->key.w == 1)
		move_forward(data);
	if (data->key.s == 1)
		move_backwards(data);
	if (data->key.a == 1)
		move_left(data);
	if (data->key.d == 1)
		move_right(data);
	if (data->key.left == 1)
		rotate_left(data);
	if (data->key.right == 1)
		rotate_right(data);
}
