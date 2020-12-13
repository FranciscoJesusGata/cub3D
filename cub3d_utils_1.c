/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 10:55:24 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/30 12:16:18 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_check_extension(char *check, char *expected)
{
	int		i;
	char	*extension;

	if (!check)
		return (0);
	i = ft_strlen(check);
	while (i > 0 && check[i] != '.')
		i--;
	if (check[i] == '\0')
		return (0);
	extension = check + i;
	if (!(ft_strnstr(extension, expected, ft_strlen(expected))))
		return (0);
	return (1);
}

void		ft_error(const char *msg)
{
	ft_printf("Error\n");
	if (msg)
		ft_printf("%s\n", msg);
}

void		ft_init_map(t_map *map)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		map->floor[i] = 0;
		map->ceiling[i] = 0;
		i++;
	}
	map->resolution[0] = 0;
	map->resolution[1] = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->mlx_ptr = mlx_init();
	mlx_get_screen_size(map->mlx_ptr, &(map->max_r[0]), &(map->max_r[1]));
	map->window = NULL;
	map->max_y = 0;
	map->save = 0;
	map->lines = 0;
	map->valid_map = 1;
	map->map_matrix = NULL;
}

void		ft_init_flags(t_cflags *flags)
{
	flags->has_resol = 0;
	flags->has_n_tex = 0;
	flags->has_w_tex = 0;
	flags->has_e_tex = 0;
	flags->has_s_tex = 0;
	flags->has_sprite = 0;
	flags->has_floor = 0;
	flags->has_clng = 0;
}

void		ft_init_tex(t_tex *tex)
{
	tex->n_texture = NULL;
	tex->s_texture = NULL;
	tex->w_texture = NULL;
	tex->e_texture = NULL;
	tex->sprite = NULL;
}
