/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:52:49 by acoto-gu          #+#    #+#             */
/*   Updated: 2025/01/10 15:15:03 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	add_new_line(t_data *data, int *lnbr)
{
	char	**temp;
	int		i;

	i = 0;
	(*lnbr)++;
	temp = malloc(sizeof(char *) * ((*lnbr) + 2));
	if (!temp)
	{
		free_array(data->cub_text);
		return (0);
	}
	while (data->cub_text[i])
	{
		temp[i] = data->cub_text[i];
		i++;
	}
	temp[*lnbr] = 0;
	temp[*lnbr + 1] = 0;
	free(data->cub_text);
	data->cub_text = temp;
	return (1);
}

int	parse_cub(int fd, t_data *data)
{
	int	i;

	i = 0;
	while (get_next_line(fd, data->cub_text + i) > 0)
	{
		if (!add_new_line(data, &i))
			return (1);
	}
	return (0);
}
