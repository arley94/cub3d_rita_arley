/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:02:21 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/23 16:24:18 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
//TO DELETE
#include <stdio.h>

# define BUFF_SIZE 1000

//MAP
typedef struct s_map
{
	char	**map;
	void	*img;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*size_x;
	int		*size_y;
	int		lines;
	int		px;
	int		py;
	int		columns;
	t_map	*map;
}			t_data;

//CHECK MAP
char    **read_map( char *map);
int		check_cub(char *str);
int		map_ok(t_data *data);

//EXIT & FREE
void	free_map(t_data *data);

//AUX
//check max x
int	get_biggest_lenght(t_data *data);

#endif