/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:34:02 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/29 19:41:57 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_mtxdup(char **input, int lines)
{
	char	**cpy;
	int		i;

	if (!input || lines == 0 || !(cpy = malloc(lines * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < lines)
	{
		cpy[i] = ft_strdup(input[i]);
		i++;
	}
	return (cpy);
}

int		ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			free(s);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free_textures(t_tex *tex)
{
	if (tex->n_texture)
	{
		free(tex->n_texture);
		tex->n_texture = NULL;
	}
	if (tex->s_texture)
	{
		free(tex->s_texture);
		tex->s_texture = NULL;
	}
	if (tex->w_texture)
	{
		free(tex->w_texture);
		tex->w_texture = NULL;
	}
	if (tex->e_texture)
	{
		free(tex->e_texture);
		tex->e_texture = NULL;
	}
	if (tex->sprite)
	{
		free(tex->sprite);
		tex->sprite = NULL;
	}
}

void	ft_free_data(t_map *data)
{
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		data->window = NULL;
	}
	if (data->mlx_ptr)
	{
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	if (data->map_matrix)
	{
		free(data->map_matrix);
		data->map_matrix = NULL;
	}
	if (data->num_sprites > 0)
	{
		free(data->sprites);
		data->sprites = NULL;
	}
}

int		end_program(t_args *game_data)
{
	ft_free_all(game_data->data, game_data->tex, game_data->file);
	kill(game_data->data->music_process, 9);
	ft_printf("See you, space cowboy\n");
	exit(0);
	return(0);
}
