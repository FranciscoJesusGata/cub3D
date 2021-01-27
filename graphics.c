/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/27 20:38:07 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_key_press(int key, t_args *args)
{
	t_map	*data;

	data = args->data;
	if (key == ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->window);
		end_program(args);
	}
	if (key == W_KEY)
		data->movement->forward = 1;
	if (key == S_KEY)
		data->movement->backward = 1;
	if (key == D_KEY)
		data->movement->right = 1;
	if (key == A_KEY)
		data->movement->left = 1;
	if (key == RIGHT_KEY)
		data->movement->r_rotation = 1;
	if (key == LEFT_KEY)
		data->movement->l_rotation = 1;
	return (0);
}

int			ft_key_release(int key, t_map *data)
{
	if (key == W_KEY)
		data->movement->forward = 0;
	if (key == S_KEY)
		data->movement->backward = 0;
	if (key == D_KEY)
		data->movement->right = 0;
	if (key == A_KEY)
		data->movement->left = 0;
	if (key == RIGHT_KEY)
		data->movement->r_rotation = 0;
	if (key == LEFT_KEY)
		data->movement->l_rotation = 0;
	return (0);
}

void		ft_start_screen(t_map *data, t_tex *tex, char **file)
{
	t_moves	mvnt;
	t_args	args;

	ft_init_raycast(data, &mvnt, tex, &args);
	args.file = file;
	ft_raycasting(data, tex);
	if (data->save == 0)
	{
		mlx_hook(data->window, 2, (1L << 0), ft_key_press, &args);
		mlx_hook(data->window, 3, (1L << 1), ft_key_release, data);
		mlx_hook(data->window, 17, 0L, (int (*)())end_program, &args);
		mlx_put_image_to_window(data->mlx_ptr, data->window,\
							data->img.img, 0, 0);
		mlx_loop_hook(data->mlx_ptr, &main_loop, &args);
		mlx_loop(data->mlx_ptr);
	}
	else
		createbmp(data);
}

int			main_loop(t_args *args)
{
	t_map	*data;
	t_tex	*tex;

	data = args->data;
	tex = args->tex;
	ft_move(data);
	ft_rotate(data);
	if (data->update)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		data->img.img = NULL;
		create_img(data, &data->img);
		if (data->num_sprites > 0)
			ft_update_sprites(data);
		ft_raycasting(data, tex);
		data->update = 0;
		mlx_put_image_to_window(data->mlx_ptr, data->window, \
								data->img.img, 0, 0);
	}
	return (0);
}
