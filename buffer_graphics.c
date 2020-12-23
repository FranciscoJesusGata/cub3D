/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:20:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/21 12:06:58 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		    get_pixel(t_img *frame, int x, int y)
{
    char	*dst;

    dst = frame->addr + (y * frame->line_length + x * (frame->bpp / 8));
    return(*(unsigned int*)dst);
}

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
		texture->coords[1] = (int)texPos;
		texPos += step;
		buffer_pixel(&data->img, x, i, get_pixel(&texture->img, texture->coords[0], texture->coords[1]));
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

void	ft_get_tex(t_ray *ray, t_tex *tex, t_tex_img **texture)
{
	if (ray->side == 0)
	{
		if (ray->step[0] < 0)
			*texture = &tex->textures[0];
		else
			*texture = &tex->textures[1];
	}
	else
	{
		if (ray->step[1] < 0)
			*texture = &tex->textures[2];
		else
			*texture = &tex->textures[3];	
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
	t_tex_img	*texture;

	texture = NULL;
    lineHeight = (int)(data->resolution[1] / ray->perpWallDist);
    data->draw_start = -lineHeight / 2 + data->resolution[1] / 2;
    if (data->draw_start < 0)
        data->draw_start = 0;
    data->draw_end = lineHeight / 2 + data->resolution[1] / 2;
    if (data->draw_end >= data->resolution[1])
		data->draw_end = data->resolution[1] - 1;
	ft_get_tex(ray, tex, &texture);
	ft_tex_xcoord(texture, ray);
    buffer_ceiling(&data->img, x, data->draw_start, rgb_to_hex(0, data->ceiling[0], data->ceiling[1], data->ceiling[2]));
    buffer_line(data, texture, x, lineHeight);
    buffer_floor(&data->img, x, data->draw_end, data->resolution[1], rgb_to_hex(0, data->floor[0], data->floor[1], data->floor[2]));
}