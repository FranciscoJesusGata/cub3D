/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:11:43 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/13 11:55:24 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_resol(char *line ,t_map *map)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while(line[i])
	{
		if(ft_isdigit(line[i]) && j < 2)
		{
			map->resolution[j] = ft_atoi(line + i);
			j++;
		}
		else if ((ft_isdigit(line[i])&& j >= 2) || 
				!(ft_strchr("\t\v\f\r ", line[i])))
			return (0);
		i++;
	}
	if (j < 2)
		return (0);
	return (1);
}

int		ft_check_texture(char *line, t_map *map)
{
	
	return(1);
}
