/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:34:02 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/19 09:44:18 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_mtxdup(char **input, int lines)
{
	char	**cpy;
	int		i;

	if(!input || lines == 0 || !(cpy = malloc(lines * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < lines)
	{
		cpy[i] = ft_strdup(input[i]);
		i++;
	}
	return (cpy);
}

int		ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_map(char **map, int lines)
{
	int	i;

	i = 0;
	while(i < lines)
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}
