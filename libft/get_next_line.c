/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:55:17 by rivasque          #+#    #+#             */
/*   Updated: 2025/01/10 14:48:39 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_start(char **buf, int fd, int *bytesread)
{
	buf[fd] = malloc(BUFFER_SIZE + 1);
	if (!buf[fd])
		return (-1);
	*bytesread = read(fd, buf[fd], BUFFER_SIZE);
	if (*bytesread < 0)
	{
		free(buf[fd]);
		return (-1);
	}
	buf[fd][*bytesread] = 0;
	return (0);
}

int	ft_in_while_a(char **buf, char *cat, char **tmp)
{
	int	i;

	i = 0;
	while ((*buf)[i])
	{
		cat[i] = (*buf)[i];
		i++;
	}
	i = 0;
	while ((*tmp)[i])
	{
		cat[i + ft_strlen(*buf)] = (*tmp)[i];
		i++;
	}
	cat[i + ft_strlen(*buf)] = 0;
	free(*tmp);
	free(*buf);
	*buf = cat;
	return (1);
}

int	ft_in_while(char **buf, int fd, int *bytesread)
{
	char	*tmp;
	char	*cat;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (-1);
	*bytesread = read(fd, tmp, BUFFER_SIZE);
	if (*bytesread < 0)
	{
		free(tmp);
		return (-1);
	}
	tmp[*bytesread] = 0;
	cat = malloc(ft_strlen(buf[fd]) + ft_strlen(tmp) + 1);
	if (!cat)
	{
		free(tmp);
		return (-1);
	}
	return ((ft_in_while_a(&(buf[fd]), cat, &tmp)));
}

int	ft_if_new_line(char **buf, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*buf)[i] != 10)
		i++;
	*line = ft_strdup(*buf);
	if (!*line)
		return (-1);
	(*line)[i] = 0;
	tmp = ft_strdup(&((*buf)[i + 1]));
	if (!tmp)
		return (-1);
	free((*buf));
	*buf = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			bytesread;
	static char	*buf[1024];

	bytesread = BUFFER_SIZE;
	if (fd >= 0 && BUFFER_SIZE > 0 && fd < 1024)
	{
		if (!buf[fd] && ft_start(buf, fd, &bytesread))
			return (-1);
		while (!ft_new_line(buf[fd]) && BUFFER_SIZE == bytesread)
			if (ft_in_while(buf, fd, &bytesread) == -1)
				return (-1);
		if (ft_new_line(buf[fd]))
			return (ft_if_new_line(&(buf[fd]), line));
		else
		{
			*line = ft_strdup(buf[fd]);
			if (!*line)
				return (-1);
			free(buf[fd]);
			buf[fd] = NULL;
			return (0);
		}
	}
	return (-1);
}
