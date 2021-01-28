/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 00:00:40 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/28 01:45:49 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		verticalrot_bonus(t_map *data)
{
	int		rot_speed;
	int		limit;

	rot_speed = 20;
	limit = data->resolution[1] / 3;
	if (data->movement->look_up == 1 && data->vertical_angle <= limit)
	{
		data->vertical_angle += rot_speed;
		data->update = 1;
	}
	else if (data->movement->look_down == 1 && data->vertical_angle >= -limit)
	{
		data->vertical_angle -= rot_speed;
		data->update = 1;
	}
}