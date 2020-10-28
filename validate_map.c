/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:26:02 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/28 10:55:05 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_check_elements(t_map *data)
{
	int		i;
	int		j;
	int		player_fnd;
	char	**mapa;

	i = 0;
	player_fnd = 0;
	mapa = data->map_matrix;
	while(mapa[i])
	{
		j = 0;
		while (mapa[i][j])
		{
			if (!(ft_strchr("012NSWE ", mapa[i][j])))
			{
				data->valid = 0;
				break ;
			}
			else if (ft_strchr("NSWE", mapa[i][j]))
			{
				if (player_fnd == 1)
				{
					data->valid = 0;
					break ;
				}
				data->valid = 1;
			}
			j++;
		}
		if (data->valid == 0)
			break ;
		i++;
	}
	if (player_fnd == 0)
	{
		data->valid = 0;
		return ;
	}
}


void		map_validator(char **map, int x, int y, t_map *data)
{
	if (data->valid == 0)
		return ;
	if (map[y][x] != 1 && map[y][x] != 3)
	{
		if (x == ft_strlen(map[y]) || y == data->max_y || x == 0 || y == 0)
		{
			data->valid = 0;
			return ;
		}
		map_validator(map, x + 1, y, data);
		if (x < ft_strlen(map[y - 1]))
			map_validator(map, x, y - 1, data);
		map_validator(map, x - 1, y, data);
		if (x < ft_strlen(map[y + 1]))
		map_validator(map, x, y + 1, data);
	}
}
