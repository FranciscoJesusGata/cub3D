/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2021/03/10 17:27:02 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

int			ft_key_bonus(int key, t_map *data)
{
	if (key == UP_KEY)
		data->movement->look_up = 1;
	if (key == DOWN_KEY)
		data->movement->look_down = 1;
	if (key == LEFT_CTRL)
		data->movement->crouch = 1;
	if (key == SPACE && data->movement->jump == 0 \
		&& data->movement->crouch == 0)
		data->movement->jump = 1;
	return (0);
}

int			ft_key_press(int key, t_args *args)
{
	t_map	*data;

	data = args->data;
	if (key == ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->window);
		data->window = NULL;
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
	if (BONUS)
		ft_key_bonus(key, data);
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
	if (key == UP_KEY)
		data->movement->look_up = 0;
	if (key == DOWN_KEY)
		data->movement->look_down = 0;
	if (key == LEFT_CTRL)
		data->movement->crouch = 0;
	return (0);
}

void		ft_start_screen(t_map *data, t_tex *tex, char **file)
{
	t_moves	mvnt;
	t_args	args;

	ft_init_raycast(data, &mvnt, tex, &args);
	data->vertical_angle = 0;
	data->vertical_pos = 0;
	data->vertical_total = 0;
	args.file = file;
	if (data->save == 0)
	{
		if (BONUS)
			data->music_process = start_music();
		mlx_hook(data->window, 2, (1L << 0), ft_key_press, &args);
		mlx_hook(data->window, 3, (1L << 1), ft_key_release, data);
		mlx_hook(data->window, 17, 0L, end_program, &args);
		mlx_loop_hook(data->mlx_ptr, &main_loop, &args);
		mlx_loop(data->mlx_ptr);
	}
	else
		createbmp(&args);
}

