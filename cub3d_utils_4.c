/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:10:41 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/16 13:00:53 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		buffer_pixel(t_img *frame, int x, int y, int color)
{
    char	*dst;

    dst = frame->addr + (y * frame->line_length + x * (frame->bpp / 8));
    *(unsigned int*)dst = color;
}

int			rgb_to_hex(int t, int r, int g, int b)
{
	return(t << 24 |r << 16 | g << 8 | b);
}

void		createImg(t_map *data, t_img *img)
{
	img->img = mlx_new_image(data->mlx_ptr, data->resolution[0], data->resolution[1]);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
}