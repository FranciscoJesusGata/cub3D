/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:26:26 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/04 12:03:16 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_check_resol(char *line ,t_map *map)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while(line[i])
	{
		if(ft_isdigit(line[i]) && j < 2)
		{
			map->resolution[j] = ft_atoi(line + i);
			while (ft_isdigit(line[i]))
				i++;
			i--;
			j++;
		}
		else if ((ft_isdigit(line[i]) && j >= 2) || 
				!(ft_strchr("\t\v\f\r ", line[i])))
			return (0);
		i++;
	}
	if (j < 2)
		return (0);
	j = 0;
	while (j < 2)
	{
		if (map->resolution[j] > map->max_r[j])
			map->resolution[j] = map->max_r[j];
		j++;
	}
		return (1);
}

void		ft_tex_flag(char *line, t_map *map, t_textures *tex, char *path)
{
	if (line[0] == 'N' && ft_strnstr(line, "NO", ft_strlen(line)))
	{
		tex->n_texture = path;
		map->flags[1] += 1;
	}
	else if (line[0] == 'S' && ft_strnstr(line, "SO", ft_strlen(line)))
	{
		tex->s_texture = path;
		map->flags[2] += 1;
	}
	else if (line[0] == 'W' && ft_strnstr(line, "WE", ft_strlen(line)))
	{
		tex->w_texture = path;
		map->flags[3] += 1;
	}
	else if (line[0] == 'E' && ft_strnstr(line, "EA", ft_strlen(line)))
	{
		tex->e_texture = path;
		map->flags[4] += 1;
	}
	else if (line[0] == 'S' && ft_strnstr(line, "S", ft_strlen(line)))
	{
		tex->sprite = path;
		map->flags[5] += 1;
	}
}

void			ft_check_texture(char *line, t_map *map, t_textures *tex)
{
	int		fd;
	char	*path;

	path = ft_strtrim(line, "\t\v\f\r NSWEAO");
	if(!path || ((fd = open(path, O_RDONLY)) == -1) || 
		!ft_check_extension(path, ".xpm") ||
		!ft_check_extension(path, ".png"))
	{
		ft_error("Texture file doesn't exists or format not valid");
		free(path);
		return ;
	}
	close(fd);
	ft_tex_flag(line, map, tex, path);
}

int				*ft_save_rgb(char **args, t_map *map)
{
	int			i;
	int			j;
	char		*nbr;
	int			*nums;

	i = 0;
	if(!(nums = malloc(sizeof(int) * 3)))
		return (NULL);
	while(args[i])
	{
		if(!(nbr = ft_strtrim(args[i], "\t\v\f\r ")))
			return (NULL);
		nums[i] = ft_atoi(nbr);
		if (nums[i] > 255 || nums[i] < 0 || !(ft_isnumber(nbr)))
		{
			free(nums);
			free(nbr);
			return (NULL);
		}
		free(nbr);
		i++;
	}
	return (nums);
}

void			ft_check_floor_ceiling(char *line, t_map *map)
{
	char		**args;
	int			*nums;
	int			i;

	if(!(args = ft_split((line + 1), ',')) ||
		!(nums = ft_save_rgb(args, map)))
		return ;
	i = 0;
	while(i > 3)
	{
		if (line [0] == 'F')
			map->floor[i] = nums[i];
		else
			map->ceiling[i] = nums[i];
		i++;
	}
	if (line [0] == 'F')
			map->flags[6] += 1;
	else
			map->flags[7] += 1;
	free(nums);
	ft_free_matrix((void **)args);
}

int		ft_check_flags(t_map *map)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (map->flags[i] != 1)
			return (0);
	}
	return (1);
}

