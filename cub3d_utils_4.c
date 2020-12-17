/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:10:41 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/17 11:51:27 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		    buffer_pixel(t_img *frame, int x, int y, int color)
{
    char    *dst;

    dst = frame->addr + (y * frame->line_length + x * (frame->bpp / 8));
    *(unsigned int*)dst = color;
}

int			    rgb_to_hex(int t, int r, int g, int b)
{
	return(t << 24 |r << 16 | g << 8 | b);
}

void		    createImg(t_map *data, t_img *img)
{
	img->img = mlx_new_image(data->mlx_ptr, data->resolution[0], data->resolution[1]);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
}

void            ft_set_orientation(char player, t_map *data)
{
    if (player == 'N')
    {
        data->dir[0] = -1;
	    data->dir[1] = 0;
	    data->plane[0] = 0;
	    data->plane[1] = 0.66;
    }
    else if (player == 'S')
    {
        data->dir[0] = 1;
	    data->dir[1] = 0;
	    data->plane[0] = 0;
	    data->plane[1] = -0.66;
    }
    else if (player == 'W')
    {
        data->dir[0] = 0;
	    data->dir[1] = -1;
	    data->plane[0] = -0.66;
	    data->plane[1] = 0;
    }
    else if (player == 'E')
    {
        data->dir[0] = 0;
	    data->dir[1] = 1;
	    data->plane[0] = 0.66;
	    data->plane[1] = 0;
    }
}

unsigned int    ft_get_pixel(t_img *img, int x, int y)
{
    char        *dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    return(*(unsigned int*)dst);
}