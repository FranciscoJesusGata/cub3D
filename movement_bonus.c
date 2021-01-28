/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 00:00:40 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/29 00:13:14 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		verticalrot_bonus(t_map *data)
{
	int		rot_speed;
	int		limit;

	rot_speed = 30;
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

void		crouch_bonus(t_map *data)
{
	if (data->movement->crouch == 1)
	{
		data->vertical_pos = -250;
		data->update = 1;
	}
	else if (data->movement->crouch == 0 && data->vertical_pos < 0)
	{
		data->vertical_pos = 0;
		data->update = 1;
	}
}

void		jump_bonus(t_map *data)
{
	if (data->vertical_pos == 600)
	{
		data->movement->ascend = 0;
		data->movement->fall = 1;
	}
	else if (data->vertical_pos == 0)
	{
		if (data->movement->fall == 1)
		{
			data->movement->jump = 0;
			data->movement->fall = 0;
		}
		else if(data->movement->jump == 1)
			data->movement->ascend = 1;
	}
	if (data->movement->ascend == 1 && data->vertical_pos < 600)
	{
		data->vertical_pos += 150;
		if (data->vertical_pos > 600)
			data->vertical_pos = 600;
		data->update = 1;
	}
	else if (data-> movement->fall == 1 && data->vertical_pos > 0)
	{
		data->vertical_pos -= 150;
		if (data->vertical_pos < 0)
			data->vertical_pos = 0;
		data->update = 1;
	}
}