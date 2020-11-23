/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:39:56 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/23 09:30:02 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_save_map(t_map *data, char **file, int *i)
{
	int	x;
	int	y;

	x = *i;
	y = 0;
	data->map_matrix = NULL;
	while (x < data->lines)
	{
		data->map_matrix = ft_newline(data->map_matrix, file[x], y);
		y++;
		x++;
	}
	data->max_y = y;
	*i = x;
}

int		ft_ismap(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_strchr(" 012NSWE", line[i])))
			return (0);
		i++;
	}
	return (1);
}
