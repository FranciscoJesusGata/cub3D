/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:08:27 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/16 13:07:48 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_move(t_map *data)
{
	double	moveSpeed;
	double	moveX;
	double	moveY;

	moveSpeed = 0.1;
	moveX = data->dir[0] * moveSpeed;
	moveY = data->dir[1] * moveSpeed;
	if (data->movement->forward == 1)
	{
		if (data->map_matrix[(int)(data->player_x + moveX)][(int)data->player_y] != '1')
			data->player_x += moveX;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y + moveY)] != '1')
			data->player_y += moveY;
		data->update = 1;
	}
	if (data->movement->backward == 1)
	{
		if (data->map_matrix[(int)(data->player_x - moveX)][(int)data->player_y] != '1')
			data->player_x -= moveX;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y - moveY)] != '1')
			data->player_y -= moveY;
		data->update = 1;
	}
	if (data->movement->left == 1)
	{
		if (data->map_matrix[(int)(data->player_x - moveY)][(int)data->player_y] != '1')
			data->player_x -= moveY;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y + moveX)] != '1')
			data->player_y += moveX;
		data->update = 1;
	}
	if (data->movement->right == 1)
	{
		if (data->map_matrix[(int)(data->player_x + moveY)][(int)data->player_y] != '1')
			data->player_x += moveY;
		if (data->map_matrix[(int)data->player_x][(int)(data->player_y - moveX)] != '1')
			data->player_y -= moveX;
		data->update = 1;
	}
}

void		ft_rotate(t_map *data)
{
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;

	rotSpeed = 0.017 * 3;
	if (data->movement->l_rotation == 1)
	{
		oldDirX = data->dir[0];
		oldPlaneX = data->plane[0];
		data->dir[0] = oldDirX * cos(rotSpeed) - data->dir[1] * sin(rotSpeed);
		data->dir[1] = oldDirX * sin(rotSpeed) + data->dir[1] * cos(rotSpeed);
		data->plane[0] = oldPlaneX * cos(rotSpeed) - data->plane[1] * sin(rotSpeed);
		data->plane[1] = oldPlaneX * sin(rotSpeed) + data->plane[1] * cos(rotSpeed);
		data->update = 1;
	}
	else if (data->movement->r_rotation == 1)
	{
		oldDirX = data->dir[0];
		oldPlaneX = data->plane[0];
		data->dir[0] = oldDirX * cos(-rotSpeed) - data->dir[1] * sin(-rotSpeed);
		data->dir[1] = oldDirX * sin(-rotSpeed) + data->dir[1] * cos(-rotSpeed);
		data->plane[0] = oldPlaneX * cos(-rotSpeed) - data->plane[1] * sin(-rotSpeed);
		data->plane[1] = oldPlaneX * sin(-rotSpeed) + data->plane[1] * cos(-rotSpeed);
		data->update = 1;
	}
}

void		ft_get_delta(t_ray *ray, double *deltaDistX, double *deltaDistY)
{
	if (ray->dir[0] == 0)
	{
		*deltaDistX = 1;
		*deltaDistY = 0;
	}
	else if (ray->dir[1] == 0)
	{
		*deltaDistX = 0;
		*deltaDistY = 1;
	}
	else
	{
		*deltaDistX = fabs(1 / ray->dir[0]);
		*deltaDistY = fabs(1 / ray->dir[1]);
	}
}

void		ft_init_sideDist(t_ray *ray, double deltaDist[])
{
	int	i;
	
	i = 0;
	while (i < 2)
	{
		if (ray->dir[i] < 0)
		{
			ray->step[i] = -1;
			ray->sideDist[i] = (ray->pos[i] - ray->map[i]) * deltaDist[i];
		}
		else
		{
			ray->step[i] = 1;
			ray->sideDist[i] = (ray->map[i] + 1.0 - ray->pos[i]) * deltaDist[i];
		}
		i++;
	}
}

void		ft_shoot_rays(t_ray *ray, double deltaDist[], char **map)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDist[0] < ray->sideDist[1])
		{
			ray->sideDist[0] += deltaDist[0];
			ray->map[0] += ray->step[0];
			ray->side = 0;
		}
		else
		{
			ray->sideDist[1] += deltaDist[1];
			ray->map[1] += ray->step[1];
			ray->side = 1;
		}
		if (map[ray->map[0]][ray->map[1]] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->map[0] - ray->pos[0] + (1 - ray->step[0]) / 2) / ray->dir[0];
	else
		ray->perpWallDist = (ray->map[1] - ray->pos[1] + (1 - ray->step[1]) / 2) / ray->dir[1];
}

void		ft_raycasting(t_map *data)
{
	int		x;
	int		w;
	double 	cameraX;
	double	deltaDist[2];
	t_ray	ray;
	
	w = data->resolution[0];
	ray.pos[0] = data->player_x;
	ray.pos[1] = data->player_y;
	x = 0;
	while (x < w)
	{
		ray.map[0] = (int)data->player_x;
		ray.map[1] = (int)data->player_y;
		cameraX = 2 * x / (double)w - 1;
		ray.dir[0] = data->dir[0] + data->plane[0] * cameraX;
		ray.dir[1] = data->dir[1] + data->plane[1] * cameraX;
		ft_get_delta(&ray, &deltaDist[0], &deltaDist[1]);
		ft_init_sideDist(&ray, deltaDist);
		ft_shoot_rays(&ray, deltaDist, data->map_matrix);
		ft_buffer(data, &ray, x);
		x++;
	}
}

int		main_loop(t_map *data)
{
	ft_move(data);
	ft_rotate(data);
	if (data->update)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		createImg(data, &data->img);
		ft_raycasting(data);
		data->update = 0;
		mlx_put_image_to_window(data->mlx_ptr, data->window, data->img.img, 0, 0);
	}
	return (0);
}