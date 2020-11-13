/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:39:56 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/12 12:31:24 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_save_map(t_map *data, char **file, int *i)
{
	int	x;
	int	lines;

	x = *i;
	lines = 0;
	while (file[x])
	{
		data->map_matrix = ft_newline(data->map_matrix, file[x], lines);
		lines++;
		x++;
	}
	data->max_y = lines;
	*i = x;
}

int		ft_ismap(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if(!(ft_strchr(" 012NSWE", line[i])))
			return (0);
		i++;
	}
	return (1);
}