/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:08:27 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/15 11:40:11 by fgata-va         ###   ########.fr       */
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

void		ft_save_sprite(t_map *data, int coords[])
{
	int		i;

	i = 0;
	while (i < data->savedSprites)
	{
		if (data->sprites[i].x == coords[0] &&
		data->sprites[i].y == coords[1])
			return ;
		i++;
	}
	data->sprites[data->savedSprites].x = coords[0];
	data->sprites[data->savedSprites].y = coords[1];
	data->sprites[data->savedSprites].perpDist =
	pow((data->player_x - coords[0]), 2.0) + pow((data->player_y - coords[1]), 2.0);
	data->savedSprites += 1;
}

void		ft_shoot_rays(t_ray *ray, double deltaDist[], t_map *data)
{
	int		hit;
	char	**map;

	hit = 0;
	map = data->map_matrix;
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
		else if (map[ray->map[0]][ray->map[1]] == '2')
			ft_save_sprite(data, ray->map);
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->map[0] - ray->pos[0] + (1 - ray->step[0]) / 2) / ray->dir[0];
	else
		ray->perpWallDist = (ray->map[1] - ray->pos[1] + (1 - ray->step[1]) / 2) / ray->dir[1];
}
void		ft_get_raydir(int x, int w, t_ray *ray, t_map *data)
{
	double 	cameraX;

	cameraX = 2 * x / (double)w - 1;
	ray->dir[0] = data->dir[0] + data->plane[0] * cameraX;
	ray->dir[1] = data->dir[1] + data->plane[1] * cameraX;
}

void			ft_swap(t_sprite *ptr1, t_sprite *ptr2)
{
	t_sprite	aux;

	aux = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = aux;
}

void			ft_sort_sprites(t_map *data)
{
	int			i;
	int			j;
	
	i = 0;
	j = 0;
	while (i < data->savedSprites)
	{
		while (j < data->savedSprites - i - 1)
		{
			if (data->sprites[j].perpDist < data->sprites[j + 1].perpDist)
				ft_swap(data->sprites + j, data->sprites + j + 1);
			j++;
		}
		i++;	
	}
}

void		ft_raycasting(t_map *data, t_tex *tex)
{
	int		x;
	int		w;
	double	deltaDist[2];
	t_ray	ray;
	
	w = data->resolution[0];
	x = 0;
	ray.pos[0] = data->player_x;
	ray.pos[1] = data->player_y;
	while (x < w)
	{
		ray.map[0] = (int)data->player_x;
		ray.map[1] = (int)data->player_y;
		ft_get_raydir(x, w, &ray, data);
		ft_get_delta(&ray, &deltaDist[0], &deltaDist[1]);
		ft_init_sideDist(&ray, deltaDist);
		ft_shoot_rays(&ray, deltaDist, data);
		data->rayBuffer[x] = ray.perpWallDist;
		if (data->savedSprites > 1)
			ft_sort_sprites(data);
		ft_buffer(data, tex, &ray, x);
		x++;
	}
	if (data->savedSprites > 1)
		buffer_sprites(data, tex->textures[4]);
}

int		main_loop(t_args *args)
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
		createImg(data, &data->img);
		if (data->numSprites > 0)
			data->sprites = (t_sprite *)malloc(sizeof(t_sprite) * data->numSprites);
		ft_raycasting(data, tex);
		if (data->savedSprites > 0)
		{
			free(data->sprites);
			data->sprites = NULL;
			data->savedSprites = 0;	
		}
		data->update = 0;
		mlx_put_image_to_window(data->mlx_ptr, data->window, data->img.img, 0, 0);
	}
	return (0);
}