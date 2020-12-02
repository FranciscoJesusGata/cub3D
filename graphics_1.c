/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/02 10:23:39 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_pixel_put(char *addr, int offset, int color)
{
	char	*dst;

	dst = addr + offset;
	*dst = color;
}

void		ft_start_screen(t_map *data, t_tex *tex)
{
	void	*img;
	char	*addr;
	int		bpp = 0;
	int		line_len = 0;
	int		endian;
	int		offset;
	int		x = 5;
	int		y = 5;

	ft_print_data(data, tex);
	data->window = mlx_new_window(data->mlx_ptr, data->resolution[0],
								data->resolution[1], "Cub3D");
	img = mlx_new_image(data->mlx_ptr, data->resolution[0], data->resolution[1]);
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	offset = y * line_len + x * (bpp / 8);
	ft_pixel_put(addr, offset, 0x00FF0000);
	mlx_put_image_to_window(data->mlx_ptr, data->window, img, 0, 0);
	mlx_loop(data->mlx_ptr);
}
