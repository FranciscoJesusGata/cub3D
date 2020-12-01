/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/01 13:00:11 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_start_screen(t_map *data, t_tex *tex)
{
	ft_print_data(data, tex);
	data->window = mlx_new_window(data->mlx_ptr, data->resolution[0],
								data->resolution[1], "Cub3D");
	mlx_loop(data->mlx_ptr);
}
