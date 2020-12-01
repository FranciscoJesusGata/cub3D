/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:34:02 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/01 11:36:23 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_mtxdup(char **input, int lines)
{
	char	**cpy;
	int		i;

	if (!input || lines == 0 || !(cpy = malloc(lines * sizeof(char *))))
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
		{
			free(s);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_print_map(char **map, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	ft_destroy_everything(t_map *map, t_tex *tex, void **file)
{
	ft_free_matrix(file, map->lines);
	free(map->mlx_ptr);
	if (map->map_matrix != NULL)
		free(map->map_matrix);
	if (tex->n_texture)
		free(tex->n_texture);
	if (tex->s_texture)
		free(tex->s_texture);
	if (tex->w_texture)
		free(tex->w_texture);
	if (tex->e_texture)
		free(tex->e_texture);
	if (tex->sprite)
		free(tex->sprite);
}

void	ft_print_data(t_map *data, t_tex *tex)
{
	ft_printf("R  %d, %d\n", data->resolution[0], data->resolution[1]);
	ft_printf("F  %d, %d, %d\n", data->floor[0], data->floor[1],
				data->floor[2]);
	ft_printf("C  %d, %d, %d\n", data->ceiling[0], data->ceiling[1],
				data->ceiling[2]);
	ft_printf("NO %s\n", tex->n_texture);
	ft_printf("SO %s\n", tex->s_texture);
	ft_printf("WE %s\n", tex->w_texture);
	ft_printf("EA %s\n", tex->e_texture);
	ft_printf("S  %s\n\n", tex->sprite);
	ft_print_map(data->map_matrix, data->max_y);
}
