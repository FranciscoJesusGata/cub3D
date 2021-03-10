/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:09:11 by fgata-va          #+#    #+#             */
/*   Updated: 2021/03/10 17:24:48 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		load_texture(t_map *data, t_tex_img *texture, char *path)
{
	if (ft_check_extension(path, ".xpm"))
		texture->img.img = mlx_xpm_file_to_image(data->mlx_ptr, path, \
										&texture->width, &texture->height);
	else
		texture->img.img = mlx_png_file_to_image(data->mlx_ptr, path, \
							&texture->width, &texture->height);
	texture->img.addr = mlx_get_data_addr(texture->img.img, &texture->img.bpp, \
							&texture->img.line_length, &texture->img.endian);
}

int			main_loop(t_args *args)
{
	t_map	*data;
	t_tex	*tex;

	data = args->data;
	tex = args->tex;
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img.img);
	ft_move(data);
	ft_rotate(data);
	if (BONUS)
		movement_bonus(data);
	if (data->num_sprites > 0)
		ft_update_sprites(data);
	mlx_do_sync(data->mlx_ptr);
	ft_raycasting(data, tex);
	mlx_put_image_to_window(data->mlx_ptr, data->window, \
							data->img.img, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->window);
	return (0);
}
