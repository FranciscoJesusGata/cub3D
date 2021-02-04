/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 23:09:36 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/04 17:49:02 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tex_imgs(t_map *data, t_tex_img textures[])
{
	int	i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(data->mlx_ptr, textures->img.img);
		i++;
		textures++;
	}
}

void	ft_free_textures(t_tex *tex, t_map *data)
{
	if (tex->n_texture)
		free(tex->n_texture);
	if (tex->s_texture)
		free(tex->s_texture);
	if (tex->w_texture)
		free(tex->w_texture);
	if (tex->e_texture)
		free(tex->e_texture);
	if (tex->sprite)
		free(tex->sprite);
	if (tex->textures[0].img.img)
		free_tex_imgs(data, tex->textures);
}

void	ft_free_data(t_map *data)
{
	if (!MAC_VERSION)
		free_mlx(data);
	free(data->map_matrix);
	data->map_matrix = NULL;
	if (data->num_sprites > 0)
	{
		free(data->sprites);
		data->sprites = NULL;
	}
	free(data->ray_buffer);
	data->ray_buffer = NULL;
}

void	ft_free_matrix(void **matrix, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
