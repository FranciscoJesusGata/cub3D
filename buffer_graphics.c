/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:20:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/17 13:27:37 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		buffer_line(t_map *data, t_tex_img *texture, int x, int lineHeight)
{
	int		i;
	int		end;
	double	step;
	double	texPos;

	i = data->draw_start;
	step = 1.0 * texture->height / lineHeight;
	end = data->draw_end;
	texPos = (data->draw_start - data->resolution[1] / 2 + lineHeight / 2) * step;
	while (i < end)
	{
		texture->coords[1] = (int)texPos & (texture->height - 1);
		texPos += step;
		buffer_pixel(data->img.img, x, i, ft_get_pixel(&texture->img, x, i));
		i++;
	}
}

void		buffer_ceiling(t_img *frame, int x, int start, int color)
{
	int		i;

	i = 0;
	while(i < start)
	{
		buffer_pixel(frame, x, i, color);
		i++;
	}
}

void		buffer_floor(t_img *frame, int x, int end, int h, int color)
{
	int		i;

	i = end;
	while(i < h)
	{
		buffer_pixel(frame, x, i, color);
		i++;
	}
}

void	ft_get_tex(t_ray *ray, t_tex *tex, t_tex_img *texture)
{
	if (ray->side == 0)
	{
		if (ray->step < 0)
			texture = &tex->textures[0];
		else
			texture = &tex->textures[1];
	}
	else
	{
		if (ray->step < 0)
			texture = &tex->textures[3];
		else
			texture = &tex->textures[4];	
	}
}

void		ft_tex_xcoord(t_tex_img *texture, t_ray *ray)
{
	double	wallX;

	if (ray->side == 0)
		wallX = ray->pos[1] + ray->perpWallDist * ray->dir[1];
	else
		wallX = ray->pos[0] + ray->perpWallDist * ray->dir[0];
	wallX -= (int)wallX;
	texture->coords[0] =  texture->width - (int)(wallX * (double)texture->width) - 1;
}

void    ft_buffer(t_map *data, t_tex *tex, t_ray *ray, int x)
{
    int			lineHeight;
	int			start;
	int			end;
	t_tex_img	*texture;
    
    lineHeight = (int)(data->resolution[1] / ray->perpWallDist);
    start = -lineHeight / 2 + data->resolution[1] / 2;
	texture = NULL;
    if (start < 0)
        start = 0;
    end = lineHeight / 2 + data->resolution[1] / 2;
    if (end >= data->resolution[1])
        end = data->resolution[1] - 1;
	ft_get_tex(ray, tex, texture);
	ft_tex_xcoord(texture, ray);
    buffer_ceiling(&data->img, x, start, rgb_to_hex(0, data->ceiling[0], data->ceiling[1], data->ceiling[2]));
    buffer_line(data, texture, x, lineHeight);
    buffer_floor(&data->img, x, end, data->resolution[1], rgb_to_hex(0, data->floor[0], data->floor[1], data->floor[2]));
}