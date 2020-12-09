/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:40:14 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/01 11:02:56 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_check_resol(t_map *map, int j)
{
	if (j < 2)
		return (0);
	j = 0;
	while (j < 2)
	{
		if (map->resolution[j] > map->max_r[j])
			map->resolution[j] = map->max_r[j];
		else if (map->resolution[j] <= 0)
			return (0);
		j++;
	}
	return (1);
}

int			ft_save_resol(char *line, t_map *map)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && j < 2)
		{
			map->resolution[j] = ft_atoi(line + i);
			while (ft_isdigit(line[i]))
				i++;
			i--;
			j++;
		}
		else if ((ft_isdigit(line[i]) && j >= 2) ||
				!(ft_strchr("\t\v\f\r ", line[i])))
			return (0);
		i++;
	}
	return (ft_check_resol(map, j));
}

int			ft_check_rgb(int *nums)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (nums[i] > 255 || nums[i] < 0)
			return (0);
		i++;
	}
	return (1);
}

int			*ft_save_rgb(char **args)
{
	int		i;
	char	*nbr;
	int		*nums;

	i = 0;
	if (!(nums = malloc(sizeof(int) * 3)))
		return (NULL);
	while (args[i])
	{
		if (!(nbr = ft_strtrim(args[i], "\t\v\f\r ")) || !(ft_isnumber(nbr)))
			return (NULL);
		nums[i] = ft_atoi(nbr);
		free(nbr);
		free(args[i]);
		i++;
	}
	free(args);
	if (i != 3 || !(ft_check_rgb(nums)))
	{
		free(nums);
		return (NULL);
	}
	return (nums);
}