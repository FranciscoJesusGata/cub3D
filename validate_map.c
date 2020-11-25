/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:26:02 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/25 20:19:28 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_check_player(char **map, int lines)
{
	int		i;
	int		j;
	int		fnd;

	fnd = 0;
	i = 0;
	while (i < lines)
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

int			ft_player_pos(char **map, int *x, int *y, int lines)
{
	int		i;
	int		j;

	i = 0;
	while (i < lines)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				if (j == 0 || i == 0 || i == lines || j == (int)ft_strlen(map[i]))
					return (0);
				*x = j;
				*y = i;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_check_elements(t_map *data)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->map_matrix;
	while(i < data->max_y)
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
	if (!ft_check_player(map, data->max_y))
		return (0);
	return (1);
}


void		map_validator(char ***mapa, int x, int y, t_map *data)
{
	char	**map;
	int		max_x;

	map = *mapa;
	if (data->valid_map == 0 || x < 0 || y < 0 || y >= data->max_y || x >= (max_x = (int)(ft_strlen(map[y]) - 1)) || map[y][x] == '1' || map[y][x] == '3')
		return ;
	if (x == 0 || y == 0 || y == (data->max_y - 1) || x == (max_x - 1))
		data->valid_map = 0;
	map[y][x] = '3';
	map_validator(mapa, x - 1, y, data);
	map_validator(mapa, x + 1, y, data);
	map_validator(mapa, x, y - 1, data);
	map_validator(mapa, x, y + 1, data);
	map_validator(mapa, x + 1, y + 1, data);
	map_validator(mapa, x - 1, y + 1, data);
	map_validator(mapa, x + 1, y - 1, data);
	map_validator(mapa, x - 1, y - 1, data);
}

int		ft_valid_map(t_map *data)
{
	int	valid;
	char **map_cpy;

	map_cpy = ft_mtxdup(data->map_matrix, data->max_y);
	valid = ft_check_elements(data);
	if (valid)
	{
		data->valid_map = ft_player_pos(data->map_matrix, &(data->player_x), &(data->player_y), data->max_y);
		map_validator(&map_cpy, data->player_x, data->player_y, data);
		ft_print_map(map_cpy, data->max_y);
		valid = data->valid_map;
	}
	ft_free_matrix((void **)map_cpy, data->max_y);
	return (valid);
}
