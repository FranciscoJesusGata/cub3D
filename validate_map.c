/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:26:02 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/09 18:25:13 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_check_player(char **map)
{
	int		i;
	int		j;
	int		fnd;

	fnd = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				if (fnd == 1)
					return (0);
				fnd = 1;
			}
			j++;
		}
		i++;
	}
	if (fnd == 0)
		return (0);
	return (1);
}


int		ft_check_elements(t_map *data, t_cub_flags *flags)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->map_matrix;
	flags->valid_map = 1;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!(ft_strchr("012NSWE ", map[i][j])))
				return (0);
			j++;
		}
		i++;
	}
	if (ft_check_player(map))
		return (0);
}


int		map_validator(char **map, int x, int y, t_map *data)
{
	int	valid;

	valid = 1;
	if (map[y][x] != 1 && map[y][x] != 3 && valid == 1)
	{
		if (x == ft_strlen(map[y]) || y == data->max_y || x == 0 || y == 0)
		{
			return (0);
		}
		map[y][x] = 3;
		valid =map_validator(map, x + 1, y, data);
		if (x < ft_strlen(map[y - 1]))
			valid = map_validator(map, x, y - 1, data);
		valid = map_validator(map, x - 1, y, data);
		if (x < ft_strlen(map[y + 1]))
			valid =map_validator(map, x, y + 1, data);
	}
	return (valid);
}

void		ft_valid_map(t_map *data, t_cub_flags *flags)
{
	
}
