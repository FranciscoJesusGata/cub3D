/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:11:13 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/31 21:34:24 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		load_texture(t_map *data, t_tex_img *texture, char *path)
{
	texture->img.img = mlx_xpm_file_to_image(data->mlx_ptr, path, \
											&texture->width, &texture->height);
	texture->img.addr = mlx_get_data_addr(texture->img.img, &texture->img.bpp, \
							&texture->img.line_length, &texture->img.endian);
}

void		free_mlx(t_map *data)
{
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
}