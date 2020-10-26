/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:26:02 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/26 13:28:48 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_validator(char **map, int x, int y, int max[])
{
	if (map[y][x] != 1 && map[y][x] != 3)
	{
		if ()
	}
	(map_validator(map, x + 1, y, max);
	map_validator(map, x, y - 1, max);
	map_validator(map, x - 1, y, max);
	map_validator(map, x, y + 1, max);
	return(1);
}
