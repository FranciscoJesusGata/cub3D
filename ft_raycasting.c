/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:08:27 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/14 13:56:48 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_get_ray(t_map *data, t_ray *ray, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)data->resolution[0] - 1;
	ray->dir[0] = data->dir[0] + data->plane[0] * cameraX;
	ray->dir[1] = data->dir[1] + data->plane[1] * cameraX;
}

void		ft_get_dir(t_ray *ray, double *sideDistX, double *sideDistY, double deltaDist[])
{
	if (ray->dir[0] < 0)
	{
		ray->step[0] = -1;
		*sideDistX = (ray->pos[0] - ray->map[0]) * deltaDist[0];
	}
	else
	{
		ray->step[0] = 1;
		*sideDistX = (ray->map[0] + 1.0 - ray->pos[0]) * deltaDist[0];
	}
	if (ray->dir[1] < 0)
	{
		ray->step[1] = -1;
		*sideDistY = (ray->pos[1] - ray->map[1]) * deltaDist[1];
	}
	else
	{
		ray->step[1] = 1;
		*sideDistY = (ray->map[1] + 1.0 - ray->pos[1]) * deltaDist[1];
	}
}

void		ft_send_rays(t_ray *ray, char **map, double sideDist[], double deltaDist[])
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (sideDist[0] < sideDist[1])
		{
			sideDist[0] += deltaDist[0];
			ray->map[0] += ray->step[0];
			ray->side = 0;
		}
		else
		{
			sideDist[1] += deltaDist[1];
			ray->map[1] += ray->step[1];
			ray->side = 1;
		}
		if (map[ray->map[0]][ray->map[1]] == '1')
			hit = 1;
	}
}

void		ft_dda_algo(char **map, t_ray *ray)
{
	double	sideDist[2];
	double	deltaDist[2];

	deltaDist[0] = (ray->dir[1] == 0) ? 0 : ((ray->dir[0] == 0) ? 1 : fabs(1 / ray->dir[0]));
	deltaDist[1] = (ray->dir[0] == 0) ? 0 : ((ray->dir[1] == 0) ? 1 : fabs(1 / ray->dir[1]));
	ft_get_dir(ray, &sideDist[0], &sideDist[1], deltaDist);
	ft_send_rays(ray, map, sideDist, deltaDist);
	if (ray->side == 0)
		ray->perpWallDist = (ray->map[0] - ray->pos[0] + (1 - ray->step[0]) / 2) / ray->dir[0];
	else
		ray->perpWallDist = (ray->map[1] - ray->pos[1] + (1 - ray->step[1]) / 2) / ray->dir[1];
}

void		ft_move(t_map *data)
{
	double	moveSpeed;
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;

	moveSpeed = 0.09;
	rotSpeed = 0.017 * 3;
	if (data->movement->forward == 1)
	{
		if (data->map_matrix[(int)(data->player_x + (data->dir[0] * moveSpeed))][(int)data->player_y] != '1')
			data->player_x += data->dir[0] * moveSpeed;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y + data->dir[1] * moveSpeed)] != '1')
			data->player_y += data->dir[1] * moveSpeed;
	}
	if (data->movement->backward == 1)
	{
		if (data->map_matrix[(int)(data->player_x - data->dir[0] * moveSpeed)][(int)data->player_y] != '1')
			data->player_x -= data->dir[0] * moveSpeed;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y - data->dir[1] * moveSpeed)] != '1')
			data->player_y -= data->dir[1] * moveSpeed;
	}
	if (data->movement->left == 1)
	{
		if (data->map_matrix[(int)(data->player_x - data->dir[1] * moveSpeed)][(int)data->player_y] != '1')
			data->player_x -= data->dir[1] * moveSpeed;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y + data->dir[0] * moveSpeed)] != '1')
			data->player_y += data->dir[0] * moveSpeed;
	}
	if (data->movement->right == 1)
	{
		if (data->map_matrix[(int)(data->player_x + data->dir[1] * moveSpeed)][(int)data->player_y] != '1')
			data->player_x += data->dir[1] * moveSpeed;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y - data->dir[0] * moveSpeed)] != '1')
			data->player_y -= data->dir[0] * moveSpeed;
	}
	if (data->movement->r_rotation == 1)
	{
		oldDirX = data->dir[0];
		oldPlaneX = data->plane[0];
		data->dir[0] = oldDirX * cos(rotSpeed) - data->dir[1] * sin(rotSpeed);
		data->dir[1] = oldDirX * sin(rotSpeed) + data->dir[1] * cos(rotSpeed);
		data->plane[0] = oldPlaneX * cos(rotSpeed) - data->plane[1] * sin(rotSpeed);
		data->plane[1] = oldPlaneX * sin(rotSpeed) + data->plane[1] * cos(rotSpeed);
	}
	if (data->movement->l_rotation == 1)
	{
		oldDirX = data->dir[0];
		oldPlaneX = data->plane[0];
		data->dir[0] = oldDirX * cos(-rotSpeed) - data->dir[1] * sin(-rotSpeed);
		data->dir[1] = oldDirX * sin(-rotSpeed) + data->dir[1] * cos(-rotSpeed);
		data->plane[0] = oldPlaneX * cos(-rotSpeed) - data->plane[1] * sin(-rotSpeed);
		data->plane[1] = oldPlaneX * sin(-rotSpeed) + data->plane[1] * cos(-rotSpeed);
	}
}

int			ft_raycasting(t_map *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray.pos[0] = data->player_x;
	ray.pos[1] = data->player_y;
	ft_move(data);
	while (x < data->resolution[0])
	{
		ft_get_ray(data, &ray, x);
		ray.map[0] = data->player_x;
		ray.map[1] = data->player_y;
		ft_dda_algo(data->map_matrix, &ray);
		ft_buffer(data, &ray, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->bg.img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img.img, 0, 0);
	return (0);
}