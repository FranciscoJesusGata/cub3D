/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/04 12:07:13 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			*ft_read_map(int fd, int *lines)
{
	char		*line;
	int			i;
	char		**file;

	file = NULL;
	i = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		file = ft_newline(file, line, i);
		i++;
	}
	file = ft_newline(file, line, i);
	i++;
	*lines = i;
	return (file);
}

void			ft_elements(char *line, t_map *map, t_tex *tex, t_cflags *flags)
{
	if (ft_strnstr(line, "R", ft_strlen(line)))
		flags->has_resol += ft_save_resol(line, map);
	else if (ft_strchr("NSWE", line[0]))
		ft_check_texture(line, tex, flags);
	else if (ft_strnstr(line, "F", ft_strlen(line)) ||
			ft_strnstr(line, "C", ft_strlen(line)))
		ft_check_floor_ceiling(line, map, flags);
}

int				ft_save_elements(t_map *map, t_tex *tex, char **file,
				t_cflags *flags)
{
	int			i;
	char		*line;
	int			valid;

	valid = 1;
	i = 0;
	while (i < map->lines && valid == 1)
	{
		if (ft_strlen(file[i]) > 1)
			line = ft_strtrim(file[i], "\r\v\f\t ");
		else
			line = ft_strdup(file[i]);
		if (strlen(line) > 0)
		{
			if ((ft_strchr("RNSWEFC", line[0])))
				ft_elements(line, map, tex, flags);
			else if (ft_ismap(line))
				ft_save_map(map, file, &i);
			else
				valid = 0;
		}
		free(line);
		i++;
	}
	return (valid);
}

int				ft_validate(char **file, t_map *map, t_tex *tex)
{
	t_cflags	flags;
	int			valid;

	valid = 1;
	ft_init_flags(&flags);
	if (!(valid = ft_save_elements(map, tex, file, &flags)))
		ft_error("Invalid identifier");
	if (!(ft_check_flags(flags)) || !(ft_valid_map(map)))
		valid = 0;
	return (valid);
}

int				cub3d(char *path, int save)
{
	int			fd;
	char		**file;
	t_map		map;
	t_tex		textures;
	int			valid;

	file = NULL;
	valid = 1;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		write(1, "Error\n", 6);
		strerror(errno);
		return (1);
	}
	ft_init_map(&map);
	map.save = save;
	ft_init_tex(&textures);
	file = ft_read_map(fd, &map.lines);
	close(fd);
	if ((valid = ft_validate(file, &map, &textures)))
		ft_start_screen(&map, &textures, file);
	ft_free_all(&map, &textures, (void **)file);
	return (valid);
}
