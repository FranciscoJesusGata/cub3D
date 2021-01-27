/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 00:39:42 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/27 19:42:58 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_get_delta(t_ray *ray, double *deltadist_x, \
							double *deltadist_y)
{
	if (ray->dir[0] == 0)
	{
		*deltadist_x = 1;
		*deltadist_y = 0;
	}
	else if (ray->dir[1] == 0)
	{
		*deltadist_x = 0;
		*deltadist_y = 1;
	}
	else
	{
		*deltadist_x = fabs(1 / ray->dir[0]);
		*deltadist_y = fabs(1 / ray->dir[1]);
	}
}

void			ft_init_sidedist(t_ray *ray, double deltadist[])
{
	int			i;

	i = 0;
	while (i < 2)
	{
		if (ray->dir[i] < 0)
		{
			ray->step[i] = -1;
			ray->side_dist[i] = (ray->pos[i] - ray->map[i]) * deltadist[i];
		}
		else
		{
			ray->step[i] = 1;
			ray->side_dist[i] = (ray->map[i] + 1.0 - ray->pos[i]) \
								* deltadist[i];
		}
		i++;
	}
}

void			get_perpwalldist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->map[0] - ray->pos[0] + \
							(1 - ray->step[0]) / 2) / ray->dir[0];
	else
		ray->perpwalldist = (ray->map[1] - ray->pos[1] + \
							(1 - ray->step[1]) / 2) / ray->dir[1];
}

void			ft_shoot_rays(t_ray *ray, double deltadist[], t_map *data)
{
	int			hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist[0] < ray->side_dist[1])
		{
			ray->side_dist[0] += deltadist[0];
			ray->map[0] += ray->step[0];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[1] += deltadist[1];
			ray->map[1] += ray->step[1];
			ray->side = 1;
		}
		if (data->map_matrix[ray->map[0]][ray->map[1]] == '1')
			hit = 1;
	}
	get_perpwalldist(ray);
}

void			ft_get_raydir(int x, int w, t_ray *ray, t_map *data)
{
	double		camera_x;

	camera_x = 2 * x / (double)w - 1;
	ray->dir[0] = data->dir[0] + data->plane[0] * camera_x;
	ray->dir[1] = data->dir[1] + data->plane[1] * camera_x;
}
