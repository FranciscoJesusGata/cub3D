/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:14:20 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/27 19:15:24 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_swap(t_sprite *ptr1, t_sprite *ptr2)
{
	t_sprite	aux;

	aux = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = aux;
}

void			ft_sort_sprites(t_map *data)
{
	int			i;
	int			j;

	i = 0;
	while (i < data->num_sprites)
	{
		j = 0;
		while (j < data->num_sprites - i - 1)
		{
			if (data->sprites[j].perpdist < data->sprites[j + 1].perpdist)
				ft_swap(data->sprites + j, data->sprites + j + 1);
			j++;
		}
		i++;
	}
}

void			ft_update_sprites(t_map *data)
{
	int			i;

	i = 0;
	while (i < data->num_sprites)
	{
		data->sprites[i].perpdist =
		pow((data->player_x - data->sprites[i].x), 2.0) \
		+ pow((data->player_y - data->sprites[i].y), 2.0);
		i++;
	}
	ft_sort_sprites(data);
}

void			ft_save_sprites(t_map *data)
{
	int			i;
	int			j;
	int			sprites;

	i = 0;
	sprites = 0;
	while (i < data->lines && sprites < data->num_sprites)
	{
		j = 0;
		while (data->map_matrix[i][j])
		{
			if (data->map_matrix[i][j] == '2')
			{
				data->sprites[sprites].x = i;
				data->sprites[sprites].y = j;
				data->sprites[sprites].perpdist =
				pow((data->player_x - i), 2.0) + pow((data->player_y - j), 2.0);
				sprites++;
			}
			j++;
		}
		i++;
	}
	ft_sort_sprites(data);
}
