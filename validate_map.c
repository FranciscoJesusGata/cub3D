/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:11:43 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/14 12:16:46 by fgata-va         ###   ########.fr       */
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
	int	i;
	int	len;
	int	fd;
	char	*path;

	i = 2;
	len = 0;
	while(ft_strchr("\t\v\f\r ", line[i]))
		i++;
	while (!(ft_strchr("\t\v\f\r ", line[i])))
		len++;
	path = ft_substr(line, i, len);
	if((fd = open(path, O_RDONLY)) == -1)
	{
		ft_printf("Texture file doesn't exists");
		return(0);
	}
	else
		map->n_texture = path;
	return(1);
}
