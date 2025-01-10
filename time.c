/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:15:51 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 14:45:11 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	manage_time(t_data *data)
{
	data->fps.old_time = data->fps.time;
	data->fps.time = getTicks();
	data->fps.frametime = (data->fps.time - data->fps.old_time) / 1000.0;
	data->player.move_speed = data->fps.frametime * 5.0;
	data->player.rotation_speed = data->fps.frametime * 3.0;
}
