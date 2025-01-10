/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:17:09 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 16:52:09 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_pixel(int x, int y, int color, t_data *data)
{
	char	*location;

	location = data->img.addr + (y * data->img.line_lenght + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)location = color;
}

void	draw_line(int x, t_data *data)
{
	int	y;

	y = data->ray.draw_start;
	while (y < data->ray.draw_end)
	{
		draw_pixel(x, y, data->color, data);
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = WIN_HEIGHT / 2 - 1;
		while (++y < WIN_HEIGHT)
			draw_pixel(x, y, data->floor, data);
		x++;
	}
}

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT / 2)
			draw_pixel(x, y, data->ceiling, data);
		x++;
	}
}

void	draw_texture(int x, t_data *data)
{
	double	step;
	double	text_position;

	step = 1.0 * TEXTURE_HEIGHT / data->ray.line_height;
	text_position = (data->ray.draw_start - WIN_HEIGHT / 2
			+ data->ray.line_height / 2) * step;
	while (data->ray.draw_start < data->ray.draw_end)
	{
		data->text_y = (int) text_position & (TEXTURE_HEIGHT - 1);
		text_position += step;
		data->color = data->textures[data->text_number][TEXTURE_HEIGHT
			* data->text_y + data->text_x];
		if (data->ray.side == 1)
			data->color = (data->color >> 1) & 8355711;
		draw_pixel(x, data->ray.draw_start, data->color, data);
		data->ray.draw_start++;
	}
}
