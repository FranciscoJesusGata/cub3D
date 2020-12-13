/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:20:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/13 13:04:45 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_buffer(t_map *data, t_ray *ray, t_img *frame, int x)
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
    buffer_line(frame, x, start, end, color);
}