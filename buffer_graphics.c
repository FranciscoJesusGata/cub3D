/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:20:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/16 13:05:54 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		buffer_line(t_img *frame, int x, int start, int end, int color)
{
	int		i;

	i = start;
	while(i <= end)
	{
		buffer_pixel(frame, x, i, color);
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


void    ft_buffer(t_map *data, t_ray *ray, int x)
{
    int		lineHeight;
	int		start;
	int		end;
	int		color;
    
    lineHeight = (int)(data->resolution[1] / ray->perpWallDist);
    start = -lineHeight / 2 + data->resolution[1] / 2;
    if (start < 0)
        start = 0;
    end = lineHeight / 2 + data->resolution[1] / 2;
    if (end >= data->resolution[1])
        end = data->resolution[1] - 1;
    if (ray->side == 1)
        color = rgb_to_hex(0, 255 / 2, 255 / 2, 255 / 2);
    else
        color = rgb_to_hex(0, 255, 255, 255);
    buffer_ceiling(&data->img, x, start, rgb_to_hex(0, data->ceiling[0], data->ceiling[1], data->ceiling[2]));
    buffer_line(&data->img, x, start, end, color);
    buffer_floor(&data->img, x, end, data->resolution[1], rgb_to_hex(0, data->floor[0], data->floor[1], data->floor[2]));
}