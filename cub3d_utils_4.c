/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:10:41 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/12 16:10:54 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		buffer_pixel(t_img *frame, int x, int y, int color)
{
    char	*dst;

    dst = frame->addr + (y * frame->line_length + x * (frame->bpp / 8));
    *(unsigned int*)dst = color;
}

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

int			rgb_to_hex(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void		createImg(t_map *data, t_img *frame)
{
	frame->img = mlx_new_image(data->mlx_ptr, data->resolution[0], data->resolution[1]);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp, &frame->line_length, &frame->endian);
}