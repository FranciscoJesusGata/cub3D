/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/16 18:08:01 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_key_press(int key, t_map *data)
{
	if (key == ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->window);
		exit(0);
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

int			ft_window_closed(void)
{
	exit(0);
	return(0);
}

void			clearImg(t_map *data, t_img *img)
{
	int		i;

	i = 0;
	while(i < data->resolution[0])
	{
		buffer_line(img, i, 0, data->resolution[1] - 1, 0);
		i++;
	}
}

void		ft_init_raycast(t_map *data, t_moves *mvnt)
{
	data->window = mlx_new_window(data->mlx_ptr, data->resolution[0],
								data->resolution[1], "Cub3D");
	data->player_x += 0.5;
	data->player_y += 0.5;
	mvnt->forward = 0;
	mvnt->backward = 0;
	mvnt->left = 0;
	mvnt->right = 0;
	mvnt->l_rotation = 0;
	mvnt->r_rotation = 0;
	data->movement = mvnt;
	data->update = 0;
	createImg(data, &data->img);
}

void		ft_start_screen(t_map *data, t_tex *tex)
{
	t_moves	mvnt;

	ft_print_data(data, tex);
	ft_init_raycast(data, &mvnt);
	mlx_hook(data->window, 2, (1L << 0), ft_key_press, data);
	mlx_hook(data->window, 3, (1L << 1), ft_key_release, data);
	mlx_hook(data->window, 17, 0L,(int (*)())exit, 0);
	ft_raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img.img, 0, 0);
	mlx_loop_hook(data->mlx_ptr, &main_loop, data);
	mlx_loop(data->mlx_ptr);
}