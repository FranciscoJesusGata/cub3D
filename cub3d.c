/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/23 11:30:28 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			*ft_resize(void *p, size_t oldlen, size_t newlen)
{
	void		*new;

	if (!p)
		return (ft_calloc(newlen, 1));
	if(newlen <= oldlen)
		return (p);
	new = ft_calloc(newlen, 1);
	ft_memcpy(new, p, newlen);
	free(p);
	return(new);
}

char			**ft_newline(char **file, char *line, size_t size)
{
	char		**new_matrix;

	new_matrix = ft_resize(file, size * sizeof(char *), (size + 1) * sizeof(char *));
	new_matrix[size] = line;
	return (new_matrix);
}

void			*ft_read_map(int fd, int *lines)
{
	char		*line;
	int			i;
	char		**file;

	file = NULL;
	i = 0;
	while((get_next_line(fd, &line)) == 1)
	{
		file = ft_newline(file, line, i);
		i++;
	}
	file = ft_newline(file, line, i);
	i++;
	*lines = i;
	return(file);
}

int				ft_validate(char **file, t_map *map, t_textures *tex)
{
	int			i;
	t_cub_flags	flags;
	char		*line;
	int			valid;

	i = 0;
	valid = 0;
	ft_init_flags(&flags);
	while (i < map->lines)
	{
		line = ft_strtrim(file[i], "\t\v\f\r ");
		if(strlen(line) > 0)
		{
			if (line[0] == 'R' && ft_strnstr(line, "R", ft_strlen(line)))
				flags.has_resol += ft_check_resol(line, map);
			else if (ft_strchr("NSWE", line[0]))
				ft_check_texture(line, tex, &flags);
			else if ((line[0] == 'F' && ft_strnstr(line, "F", ft_strlen(line))) ||
					(line[0] == 'C' && ft_strnstr(line, "C", ft_strlen(line))))
				ft_check_floor_ceiling(line, map, &flags);
			else if (ft_ismap(line))
				ft_save_map(map, file, &i);
			else
			{
				free(line);
				return (1);
			}
		}
		free(line);
		i++;
	}
	if (!(ft_check_flags(flags)) || !(ft_valid_map(map)))
	{
		ft_error("Invalid arguments");
		valid = 1;
	}
	return (valid);
}

int				cub3d(char *path, int save)
{
	int			fd;
	char		**file;
	t_map		map;
	t_textures	textures;
	int			valid;

	file = NULL;
	if((fd = open(path, O_RDONLY)) == -1)
	{
		write(1, "Error\n", 6);
		strerror(errno);
		return(1);
	}
	ft_init_map(&map);
	map.save = save;
	ft_init_tex(&textures);
	file = ft_read_map(fd, &map.lines);
	close(fd);
	if((valid = ft_validate(file, &map, &textures)) == 0)
		ft_print_data(&map,&textures);
	ft_destroy_everything(&map, &textures, (void **)file);
	return (valid);
}

