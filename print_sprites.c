/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:28:15 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/13 17:48:01 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			print_spriteline(t_map *data, t_sprite *sprite, \
								t_tex_img tex, int x)
{
	int			y;
	int			d;
	int			color;

	y = sprite->draw_y[0];
	while (y < sprite->draw_y[1])
	{
		d = (y - data->vertical_total) * 256 - (data->resolution[1] * 128) \
						+ (sprite->height * 128);
		sprite->tex[1] = ((d * tex.height) / sprite->height) / 256;
		if (sprite->tex[1] < 0)
			sprite->tex[1] = 0;
		color = get_pixel(&tex.img, sprite->tex[0], sprite->tex[1]);
		if ((color & 0x00FFFFFF) != 0)
			buffer_pixel(&data->img, x, y, color);
		y++;
	}
}

void			print_sprite(t_map *data, t_sprite *sprite, \
							double transform[], t_tex_img tex)
{
	int			x;

	x = sprite->draw_x[0];
	while (x < sprite->draw_x[1])
	{
		sprite->tex[0] = (int)(256 * (x - (-sprite->width / 2 \
						+ sprite->print_x)) * tex.width / sprite->width) / 256;
		if (transform[1] > 0 && x > 0 && x < data->resolution[0] \
			&& transform[1] < data->ray_buffer[x])
			print_spriteline(data, sprite, tex, x);
		x++;
	}
}

void			sprite_size(t_map *data, t_sprite sprite, \
							double transform[], t_tex_img texture)
{
	if (BONUS)
		data->vertical_total = data->vertical_angle + \
		(data->vertical_pos / transform[1]);
	sprite.print_x = (int)((data->resolution[0] / 2) \
						* (1 + transform[0] / transform[1]));
	sprite.height = ABS((int)(data->resolution[1] / transform[1]));
	sprite.draw_y[0] = (-sprite.height / 2) + (data->resolution[1] / 2) + \
						data->vertical_total;
	if (sprite.draw_y[0] < 0)
		sprite.draw_y[0] = 0;
	sprite.draw_y[1] = (sprite.height / 2) + (data->resolution[1] / 2) + \
						data->vertical_total;
	if (sprite.draw_y[1] >= data->resolution[1])
		sprite.draw_y[1] = data->resolution[1] - 1;
	sprite.width = sprite.height;
	sprite.draw_x[0] = (-sprite.width / 2) + sprite.print_x;
	if (sprite.draw_x[0] < 0)
		sprite.draw_x[0] = 0;
	sprite.draw_x[1] = (sprite.width / 2) + sprite.print_x;
	if (sprite.draw_x[1] >= data->resolution[0])
		sprite.draw_x[1] = data->resolution[0] - 1;
	print_sprite(data, &sprite, transform, texture);
}

void			buffer_sprites(t_map *data, t_tex_img texture)
{
	int			i;
	double		sprite_coords[2];
	double		inv_cam;
	double		transform[2];

	i = 0;
	while (i < data->num_sprites)
	{
		sprite_coords[0] = data->sprites[i].x - (data->player_x - 0.5);
		sprite_coords[1] = data->sprites[i].y - (data->player_y - 0.5);
		inv_cam = 1.0 / ((data->plane[0] * data->dir[1]) \
						- (data->dir[0] * data->plane[1]));
		transform[0] = inv_cam * ((data->dir[1] * sprite_coords[0]) \
						- (data->dir[0] * sprite_coords[1]));
		transform[1] = inv_cam * (-(data->plane[1] * sprite_coords[0]) \
						+ (data->plane[0] * sprite_coords[1]));
		sprite_size(data, data->sprites[i], transform, texture);
		i++;
	}
}
