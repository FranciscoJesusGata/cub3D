/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/04 09:49:13 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_key_control(int key, t_map *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->window);
		exit(0);
	}
	return (0);
}

int			ft_window_closed(void)
{
	exit(0);
	return(0);
}

void		ft_start_screen(t_map *data, t_tex *tex)
{
	ft_print_data(data, tex);
	data->window = mlx_new_window(data->mlx_ptr, data->resolution[0],
								data->resolution[1], "Cub3D");
	mlx_key_hook(data->window, ft_key_control, data);
	mlx_hook(data->window, 17, 0L,(int (*)())exit, 0);
	mlx_loop(data->mlx_ptr);
}
