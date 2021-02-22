/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:20:34 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/22 10:14:29 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

void			buffer_floor_ceiling(t_img *img, int x, int y, int rgb[])
{
	buffer_pixel(img, x, y, rgb_to_hex(0, rgb[0], rgb[1], rgb[2]));
}

void			buffer_line(t_map *data, t_tex_img *tex, \
							int x, int line_height)
{
	int			i;
	double		step;
	double		tex_pos;

	i = 0;
	step = 1.0 * tex->height / line_height;
	tex_pos = (data->draw_start - data->vertical_total - \
			data->resolution[1] / 2 + line_height / 2) * step;
	while (i < data->resolution[1])
	{
		if (i < data->draw_start)
			buffer_floor_ceiling(&data->img, x, i, data->ceiling);
		else if (i > data->draw_end)
			buffer_floor_ceiling(&data->img, x, i, data->floor);
		else if (i >= data->draw_start && i <= data->draw_end)
		{
			if ((tex->coords[1] = (int)tex_pos) < 0)
				tex->coords[1] = 0;
			tex_pos += step;
			buffer_pixel(&data->img, x, i, get_pixel(&tex->img, \
						tex->coords[0], tex->coords[1]));
		}
		i++;
	}
}

void			ft_get_tex(t_ray *ray, t_tex *tex, t_tex_img **texture)
{
	if (ray->side == 0)
	{
		if (ray->step[0] < 0)
			*texture = &tex->textures[1];
		else
			*texture = &tex->textures[0];
	}
	else
	{
		if (ray->step[1] < 0)
			*texture = &tex->textures[3];
		else
			*texture = &tex->textures[2];
	}
}

void			ft_tex_xcoord(t_tex_img *texture, t_ray *ray)
{
	double		wall_x;

	if (ray->side == 0)
		wall_x = ray->pos[1] + ray->perpwalldist * ray->dir[1];
	else
		wall_x = ray->pos[0] + ray->perpwalldist * ray->dir[0];
	wall_x -= (int)wall_x;
	texture->coords[0] = texture->width - \
							(int)(wall_x * (double)texture->width) - 1;
}

void			ft_buffer(t_map *data, t_tex *tex, t_ray *ray, int x)
{
	int			line_height;
	t_tex_img	*texture;

	texture = NULL;
	line_height = (int)(data->resolution[1] / ray->perpwalldist);
	if ((data->resolution[1] / ray->perpwalldist) > 2147483647)
		line_height = 2147483647;
	data->draw_start = -line_height / 2 + data->resolution[1] / 2 \
					+ data->vertical_total;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = line_height / 2 + data->resolution[1] / 2 \
					+ data->vertical_total;
	if (data->draw_end >= data->resolution[1])
		data->draw_end = data->resolution[1] - 1;
	ft_get_tex(ray, tex, &texture);
	ft_tex_xcoord(texture, ray);
	buffer_line(data, texture, x, line_height);
}
