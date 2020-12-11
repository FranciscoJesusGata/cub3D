/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:50:03 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/11 12:54:55 by fgata-va         ###   ########.fr       */
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

void		createImg(t_map *data, t_img *frame)
{
	frame->img = mlx_new_image(data->mlx_ptr, data->resolution[0], data->resolution[1]);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp, &frame->line_length, &frame->endian);
}

int			ft_raycasting(t_map *data)
{
	double	cameraX;
	double	rayDir[2];
	int		map[2];
	double	sideDist[2];
	double	deltaDist[2];
	int		step[2];
	int		hit;
	int		side;
	double	prepWallDist;
	int		lineHeight;
	int		start;
	int		end;
	int		color;
	int		x;
	t_img	frame;

	x = 0;
	createImg(data, &frame);
	while (x < data->resolution[0])
	{
		//Ray position and direction
		cameraX = 2 * x / (double)data->resolution[0] - 1;
		rayDir[0] = data->dir[0] + data->plane[0] * cameraX;
		rayDir[1] = data->dir[1] + data->plane[1] * cameraX;
		//Which cube we're checking
		map[0] = (int)data->player_x;
		map[1] = (int)data->player_y;
		//Length of one x or y side to next x or y side
		deltaDist[0] = (rayDir[1] == 0) ? 0 : ((rayDir[0] == 0) ? 1 : fabs(1 / rayDir[0]));
		deltaDist[1] = (rayDir[0] == 0) ? 0 : ((rayDir[1] == 0) ? 1 : fabs(1 / rayDir[1]));
		if (rayDir[0] < 0)
		{
			step[0] = -1;
			sideDist[0] = (data->player_x - map[0]) * deltaDist[0];
		}
		else
		{
			step[0] = 1;
			sideDist[0] = (map[0] + 1.0 - data->player_x) * deltaDist[0];
		}
		if (rayDir[1] < 0)
		{
			step[1] = -1;
			sideDist[1] = (data->player_y - map[1]) * deltaDist[1];
		}
		else
		{
			step[1] = 1;
			sideDist[1] = (map[1] + 1.0 - data->player_y) * deltaDist[1];
		}
		hit = 0;
		while (hit == 0)
		{
			if (sideDist[0] < sideDist[1])
			{
				sideDist[0] += deltaDist[0];
				map[0] += step[0];
				side = 0;
			}
			else
			{
				sideDist[1] += deltaDist[1];
				map[1] += step[1];
				side = 1;
			}
			if (data->map_matrix[map[0]][map[1]] == '1')
				hit = 1;
		}
		if (side == 0)
			prepWallDist = (map[0] - data->player_x + (1 - step[0]) / 2) / rayDir[0];
		else
			prepWallDist = (map[1] - data->player_y + (1 - step[1]) / 2) / rayDir[1];
		lineHeight = (int)(data->resolution[1] / prepWallDist);
		start = -lineHeight / 2 + data->resolution[1] / 2;
		if (start < 0)
			start = 0;
		end = lineHeight / 2 + data->resolution[1] / 2;
		if (end >= data->resolution[1])
			end = data->resolution[1] - 1;
		if (side == 1)
			color = rgb_to_hex(0, 255 / 2, 255 / 2, 255 / 2);
		else
			color = rgb_to_hex(0, 255, 255, 255);
		buffer_line(&frame, x, start, end, color);
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
	data->dir[0] = -1;
	data->dir[1] = 0;
	data->plane[0] = 0;
	data->plane[1] = 0.66;
	data->player_x += 0.5;
	data->player_y += 0.5;
	ft_raycasting(data);
	//mlx_loop_hook(data->mlx_ptr, ft_raycasting, data);
	mlx_loop(data->mlx_ptr);
}