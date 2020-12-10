/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/10 12:59:54 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_key_control(int key, t_map *data)
{
	if (key == ESC)
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

void		get_ray_dir(int w, int x, double *rayDirX, double *rayDirY, double dir[], double plane[])
{
	double cameraX;

	cameraX = 2 * x / (double)w - 1;
	*rayDirX = dir[0] + plane[0] * cameraX;
	*rayDirY = dir[1] + plane[1] * cameraX;
}

double		do_dda(t_map *data, double rayDir[], int map[], int *side)
{
	double	deltaDist[2];
	double	step[2];
	double	sideDist[2];
	int		hit;
	
	hit = 0;
	deltaDist[0] = (rayDir[1] == 0) ? 0 : ((rayDir[0] == 0) ? 1 : fabs(1 / rayDir[0]));
	deltaDist[1] = (rayDir[0] == 0) ? 0 : ((rayDir[1] == 0) ? 1 : fabs(1 / rayDir[1]));
	if(rayDir[0] < 0)
	{
		step[0] = -1;
		sideDist[0] = (data->player_x - map[0]) * deltaDist[0];
	}
	else
	{
		step[0] = 1;
		sideDist[0] = (map[0] + 1.0 - data->player_x) * deltaDist[0];
	}
	if(rayDir[1] < 0)
	{
		step[1] = -1;
		sideDist[1] = (data->player_y - map[1]) * deltaDist[1];
	}
	else
	{
		step[1] = 1;
		sideDist[1] = (map[1] + 1.0 - data->player_y) * deltaDist[1];
	}
	while (hit == 0)
	{
		if (sideDist[0] < sideDist[1])
		{
			sideDist[0] += deltaDist[0];
			map[0] += step[0];
			*side = 0;
		}
		else
		{
			sideDist[1] += deltaDist[1];
			map[1] += step[1];
			*side = 1;
		}
		if (data->map_matrix[map[0]][map[1]] == '1')
			hit = 1;
	}
	if (*side == 0)
		return((map[0] - data->player_y + (1 - step[0]) / 2) / rayDir[0]);
	else
		return((map[1] - data->player_x + (1 - step[1]) / 2) / rayDir[1]);
}

double			ray_longitude(t_map *data, double dir[], double plane[], int x, int *side)
{
	double	rayDir[2];
	int		map[2];

	x = 0;
	map[0] = data->player_y;
	map[1] = data->player_x;
	get_ray_dir(data->resolution[0], x, &rayDir[0], &rayDir[1], dir, plane);
	return(do_dda(data, rayDir, map, side));
}

void		buffer_pixel(t_img *frame, int x, int y, int color)
{
    char	*dst;

    dst = frame->addr + (y * frame->line_length + x * (frame->bpp / 8));
    *(unsigned int*)dst = color;
}

void		buffer_line(t_img *frame, int x, int start, int end, int color)
{
	int		i;

	i = start;
	while(i <= end)
	{
		buffer_pixel(frame, x, i, color);
		i++;
	}
}

int			rgb_to_hex(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void		ft_draw(t_map *data, int x, t_img *frame, int side, int perpWallDist)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;

	lineHeight = (int)(data->resolution[1] / perpWallDist);
	drawStart = -lineHeight / 2 + data->resolution[1] / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + data->resolution[1] / 2;
	if (drawEnd >= data->resolution[1])
		drawEnd -= data->resolution[1] - 1;
	if (side == 1)
		color = rgb_to_hex(0, 255/2, 255/2, 255/2);
	else
		color = rgb_to_hex(0, 255, 255, 255);
	buffer_line(frame, x, drawStart, drawEnd, color);
}

void		createImg(t_map *data, t_img *frame)
{
	frame->img = mlx_new_image(data->mlx_ptr, data->resolution[0], data->resolution[1]);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp, &frame->line_length, &frame->endian);
}

int			ft_raycasting(t_map *data)
{
	double	dir[2];
	double	plane[2];
	double	prepWallDist;
	int		x;
	int		side;
	t_img	frame;

	dir[0] = 1;
	dir[1] = 0;
	plane[0] = 0;
	plane[1] = 1;
	x = 0;
	while(x < data->resolution[0])
	{
		createImg(data, &frame);
		prepWallDist = ray_longitude(data, dir, plane, x, &side);
		ft_draw(data, x, &frame, side, prepWallDist);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window, frame.img, 0, 0);
	return (0);
}

void		ft_start_screen(t_map *data, t_tex *tex)
{
	ft_print_data(data, tex);
	data->window = mlx_new_window(data->mlx_ptr, data->resolution[0],
								data->resolution[1], "Cub3D");
	mlx_key_hook(data->window, ft_key_control, data);
	mlx_hook(data->window, 17, 0L,(int (*)())exit, 0);
	ft_raycasting(data);
	//mlx_loop_hook(data->mlx_ptr, ft_raycasting, data);
	mlx_loop(data->mlx_ptr);
}