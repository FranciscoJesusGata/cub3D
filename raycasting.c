/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:08:27 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/27 19:16:39 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ft_shoot_rays(&ray, deltadist, data);
		data->ray_buffer[x] = ray.perpwalldist;
		ft_buffer(data, tex, &ray, x);
		x++;
	}
	if (data->num_sprites > 0)
		buffer_sprites(data, tex->textures[4]);
}
