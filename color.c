/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:05:08 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/04 15:24:36 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//check if rgb between 0 and 255
static int  *check_rgb(char **array)
{
    int i;
    int *rgb;
    
    i = 0;
    rgb = malloc(sizeof(int) * 4);
    if (!rgb)
        return (NULL);
    while (array[i])
    {
        rgb[i] = ft_atoi(array[i]);
        if (rgb[i] < 0 || rgb[i] > 255)
            return (NULL);
        i++;
    }
    rgb[i] = 0;
    return (rgb);
}

unsigned long convert_rgb(int rgb0, int rgb1, int rgb2)
{
    return (((rgb0 & 0xff) << 16) + ((rgb1 & 0xff) << 8) + (rgb2 & 0xff));
}

void    define_colors(int *rgb, int i, t_data *data)
{
    unsigned long   color;
    
    if (i == 0)
    {
        color = convert_rgb(rgb[0], rgb[1], rgb[2]);
        data->floor = color;
    }
    if (i == 1)
    {
        color = convert_rgb(rgb[0], rgb[1], rgb[2]);
        data->ceiling = color;
    }
}

int get_colors(t_data *data)
{
    int		i;
    char    **array;
	int		*rgb;
	
    i = 0;
	while (i < 2)
	{
        array = ft_split(data->rgb[i], ',');
		if (!array)
			return (1);
        rgb = check_rgb(array);
		if (!rgb)
		{
			free(rgb);
			return (1);
		}
		define_colors(rgb, i, data);
		free_array(array);
		free(rgb);
		i++;
	}
	return (0);
}
