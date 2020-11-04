/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 10:55:24 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/03 11:57:20 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_free_matrix(void **matrix)
{
	int		i;

	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int			ft_check_extension(char *check, char *expected)
{
	int		i;
	char	*extension;

	i = 0;
	if (!check)
		return (0);
	while (check[i] && check[i] != '.')
		i++;
	if (check[i] == '\0')
		return (0);
	extension = check + i;
	if (!(ft_strnstr(extension, expected, ft_strlen(expected))))
		return (0);
	return (1);
}

void	ft_error(const char *msg)
{
	ft_printf("Error\n");
	if (msg)
		ft_printf(msg);
}

void	ft_init_map(t_map *map)
{
	int	i;
	int max_x;
	int max_y;

	i = 0;
	while(i < 3)
	{
		map->floor[i] = 0;
		map->ceiling[i] = 0;
		i++;
	}
	i = 0;
	while(i < 8)
	{
		map->flags[i] = 0;
		i++;
	}
	map->mlx_ptr = mlx_init();
	mlx_get_screen_size(map->mlx_ptr, &(map->max_r[0]), &(map->max_r[1]));
	map->window = NULL;
	map->max_y = 0;
}

void	ft_init_tex(t_textures *tex)
{
	tex->n_texture = NULL;
	tex->s_texture = NULL;
	tex->w_texture = NULL;
	tex->e_texture = NULL;
	tex->sprite = NULL;
}

