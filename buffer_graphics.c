/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:20:34 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/15 11:10:13 by fgata-va         ###   ########.fr       */
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

void	print_sprites(t_map *data, t_sprite sprite, double transform[], int spriteScreenX, t_tex_img texture)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	d;
	int	color;

	x = sprite.drawX[0];
	while (x < sprite.drawX[1])
	{
		tex_x = (int) (256 * (x - (-sprite.width / 2 + spriteScreenX)) * texture.width / sprite.width) / 256;
		if (transform[1] > 0 && x > 0 && x < data->resolution[0] && transform[1] < data->rayBuffer[x])
		{
			y = sprite.drawY[0];
			while (y < sprite.drawY[1])
			{
				d = y * 256 - data->resolution[1] * 128 + sprite.height * 128;
				tex_y = ((d * texture.height) / sprite.height) / 256;
				color = get_pixel(&texture.img, tex_x, tex_y);
				if ((color & 0x00FFFFFF) != 0)
					buffer_pixel(&data->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void	buffer_sprites(t_map *data, t_tex_img texture)
{
	int	i;
	double	spritePos[2];
	double	invCamMatrix;
	double	transform[2];
	int		spriteScreenX;

	i = 0;
	while (i < data->savedSprites)
	{
		spritePos[0] = data->sprites[i].x - data->player_x;
		spritePos[1] = data->sprites[i].y - data->player_y;
		invCamMatrix = 1.0 / (data->plane[0] * data->dir[1] - data->dir[0] * data->plane[1]);
		transform[0] = invCamMatrix * (data->dir[1] * spritePos[0] - data->dir[0] * spritePos[1]);
		transform[1] = invCamMatrix * (-data->plane[1] * spritePos[0] - data->plane[0] * spritePos[1]);
		spriteScreenX = (int)((data->resolution[0] / 2) * (1 + transform[0] / transform[1]));
		data->sprites[i].width = fabs((int)(data->resolution[1] / transform[1]));
		data->sprites[i].drawX[0] = (-1 * data->sprites[i].width) / 2 + spriteScreenX;
		if (data->sprites[i].drawX[0] < 0)
			data->sprites[i].drawX[0] = 0;
		data->sprites[i].drawX[1] = data->sprites[i].width / 2 + spriteScreenX;
		if (data->sprites[i].drawX[1] >= data->resolution[0])
			data->sprites[i].drawX[1] = data->resolution[0] - 1;
		data->sprites[i].height = fabs((int)(data->resolution[1] / transform[1]));
		data->sprites[i].drawY[0] = (-1 * data->sprites[i].height) / 2 + data->resolution[1] / 2;
		if (data->sprites[i].drawY[0] < 0)
			data->sprites[i].drawY[0] = 0;
		data->sprites[i].drawY[1] = data->sprites[i].height / 2 + spriteScreenX;
		if (data->sprites[i].drawY[1] >= data->resolution[1])
			data->sprites[i].drawY[1] = data->resolution[1] - 1;
		print_sprites(data, data->sprites[i], transform, spriteScreenX, texture);
		i++;
	}
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