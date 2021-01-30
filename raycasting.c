/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:08:27 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/30 23:39:47 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

void			ft_init_move(t_moves *mvnt)
{
	mvnt->forward = 0;
	mvnt->backward = 0;
	mvnt->left = 0;
	mvnt->right = 0;
	mvnt->l_rotation = 0;
	mvnt->r_rotation = 0;
	mvnt->look_up = 0;
	mvnt->look_down = 0;
	mvnt->crouch = 0;
	mvnt->jump = 0;
	mvnt->ascend = 0;
	mvnt->fall = 0;
}

void			load_alltextures(t_map *data, t_tex *tex)
{
	load_texture(data, &tex->textures[0], tex->n_texture);
	load_texture(data, &tex->textures[1], tex->s_texture);
	load_texture(data, &tex->textures[2], tex->w_texture);
	load_texture(data, &tex->textures[3], tex->e_texture);
	load_texture(data, &tex->textures[4], tex->sprite);
}

void			ft_init_raycast(t_map *data, t_moves *mvnt,\
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

void			ft_raycasting(t_map *data, t_tex *tex)
{
	int			x;
	int			w;
	double		deltadist[2];
	t_ray		ray;

	w = data->resolution[0];
	x = 0;
	ray.pos[0] = data->player_x;
	ray.pos[1] = data->player_y;
	while (x < w)
	{
		ray.map[0] = (int)data->player_x;
		ray.map[1] = (int)data->player_y;
		ft_get_raydir(x, w, &ray, data);
		ft_get_delta(&ray, &deltadist[0], &deltadist[1]);
		ft_init_sidedist(&ray, deltadist);
		ft_shoot_rays(&ray, deltadist, data, x);
		if (BONUS)
			data->vertical_total = data->vertical_angle + \
					(data->vertical_pos / ray.perpwalldist);
		ft_buffer(data, tex, &ray, x);
		x++;
	}
	if (data->num_sprites > 0)
		buffer_sprites(data, tex->textures[4]);
}
