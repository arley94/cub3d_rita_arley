/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map _3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 15:16:13 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Check there's a player and only one
int	check_player(t_data *data)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' ||
			data->map[y][x] == 'S' ||
			data->map[y][x] == 'E' ||
			data->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count > 1 || count == 0)
		return (1);
	return (0);
}

int	checkwall(char *str)
{
	while (*str)
	{
		if (*str != '1' && !ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_all_sides(char **strs, int j)
{
	if (ft_isspace(strs[-1][j - 1]) || !strs[-1][j - 1])
		return (0);
	if (ft_isspace(strs[-1][j]) || !strs[-1][j])
		return (0);
	if (ft_isspace(strs[-1][j + 1]) || !strs[-1][j + 1])
		return (0);
	if (ft_isspace(strs[0][j - 1]) || !strs[0][j - 1])
		return (0);
	if (ft_isspace(strs[0][j + 1]) || !strs[0][j + 1])
		return (0);
	if (ft_isspace(strs[1][j - 1]) || !strs[1][j - 1])
		return (0);
	if (ft_isspace(strs[1][j]) || !strs[1][j])
		return (0);
	if (ft_isspace(strs[1][j + 1]) || !strs[1][j + 1])
		return (0);
	return (1);
}

int	checkmapclosed(char **strs)
{
	int	j;

	j = 0;
	while (strs[0][j])
	{
		if (ft_strchr("0NSEW", strs[0][j]))
		{
			if (!check_all_sides(strs, j))
				return (0);
		}
		j++;
	}
	return (1);
}

int	check_map_walls(t_data *data)
{
	int		i;
	char	**strs;

	i = -1;
	strs = data->map;
	while (strs[++i])
	{
		if (i == 0 && !checkwall(strs[i]))
			return (1);
		else if (!strs[i + 1] && !checkwall(strs[i]))
			return (1);
		else if (!strs[i + 1] && i < 2)
			return (1);
		else if (!checkmapclosed(&strs[i]))
			return (1);
	}
	return (0);
}
