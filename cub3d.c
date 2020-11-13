/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/13 12:12:49 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			*ft_resize(void *p, size_t oldlen, size_t newlen)
{
	void		*new;

	if (!p)
		return (malloc(newlen));
	if(newlen <= oldlen)
		return (p);
	new = malloc(newlen);
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

void			*ft_read_map(int fd)
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
	file[i] = NULL;
	return(file);
}

int				ft_validate(char **file, t_map *map, t_textures *tex)
{
	int			i;
	t_cub_flags	flags;
	char		*line;
	int			valid;

	i = 0;
	valid = 1;
	ft_init_flags(&flags);
	while (file[i])
	{
		line = ft_strtrim(file[i], "\t\v\f\r ");
		if (line[0] == 'R' && ft_strnstr(line, "R", ft_strlen(line)))
			flags.has_resol += ft_check_resol(line, map);
		else if (ft_strchr("NSWE",ft_strlen(line)))
			ft_check_texture(line, tex, &flags);
		else if ((line[0] == 'F' && ft_strnstr(line, "F", ft_strlen(line))) ||
				(line[0] == 'C' && ft_strnstr(line, "C", ft_strlen(line))))
			ft_check_floor_ceiling(line, map, &flags);
		else if (ft_ismap(line))
			ft_save_map(map, file, &i);
		else
			break ;
		i++;
	}
	if (!(ft_check_flags(flags)) || !(ft_valid_map(map)))
	{
		ft_error("Invalid arguments");
		valid = 0;
	}
	ft_free_matrix((void **)file);
	return (valid);
}

int				cub3d(char *path, int save)
{
	int			fd;
	char		**file;
	t_map		map;
	t_textures	textures;

	file = NULL;
	if(!(fd = open(path, O_RDONLY)))
	{
		write(1, "Error\n", 6);
		strerror(errno);
		return(1);
	}
	ft_init_map(&map);
	map.save = save;
	ft_init_tex(&textures);
	file = ft_read_map(fd);
	close(fd);
	if(!(ft_validate(file, &map, &textures)))
	{
		//ft_destroy_everything();
		return (0);
	}
	ft_printf("R  %d, %d\n", map.resolution[0], map.resolution[1]);
	ft_printf("F  %d, %d, %d\n", map.floor[0], map.floor[1], map.floor[2]);
	ft_printf("C  %d, %d, %d\n", map.ceiling[0], map.ceiling[1], map.ceiling[2]);
	ft_printf("NO %s\n", textures.n_texture);
	ft_printf("SO %s\n", textures.s_texture);
	ft_printf("WE %s\n", textures.w_texture);
	ft_printf("EA %s\n", textures.e_texture);
	ft_printf("S  %s\n\n", textures.sprite);
	ft_print_map(map.map_matrix, map.max_y);
	return (1);
}

