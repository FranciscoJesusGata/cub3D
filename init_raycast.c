/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:20:48 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/27 19:37:59 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_move(t_moves *mvnt)
{
	mvnt->forward = 0;
	mvnt->backward = 0;
	mvnt->left = 0;
	mvnt->right = 0;
	mvnt->l_rotation = 0;
	mvnt->r_rotation = 0;
}

void	load_alltextures(t_map *data, t_tex *tex)
{
	load_texture(data, &tex->textures[0], tex->n_texture);
	load_texture(data, &tex->textures[1], tex->s_texture);
	load_texture(data, &tex->textures[2], tex->w_texture);
	load_texture(data, &tex->textures[3], tex->e_texture);
	load_texture(data, &tex->textures[4], tex->sprite);
}

void	ft_init_raycast(t_map *data, t_moves *mvnt,\
						t_tex *tex, t_args *args)
{
	if (data->save == 0)
	{
		data->window = mlx_new_window(data->mlx_ptr, data->resolution[0],
									data->resolution[1], "Cub3D");
	}
	data->player_x += 0.5;
	data->player_y += 0.5;
	ft_init_move(mvnt);
	data->movement = mvnt;
	data->update = 0;
	create_img(data, &data->img);
	data->ray_buffer = malloc(sizeof(int) * data->resolution[0]);
	load_alltextures(data, tex);
	args->data = data;
	args->tex = tex;
	if (data->num_sprites > 0)
	{
		data->sprites = (t_sprite *)malloc(sizeof(t_sprite) * \
						data->num_sprites);
		ft_save_sprites(data);
	}
	else
		data->sprites = NULL;
}
