/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/04 12:02:40 by fgata-va         ###   ########.fr       */
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
	int			j;

	i = 0;
	while (file[i])
	{
		if (file[i][0] == 'R' && ft_strnstr(file[i], "R", ft_strlen(file[i])))
			map->flags[0] += ft_check_resol(file[i], map);
		else if (ft_strchr("NSWE",file[i][0]))
			ft_check_texture(file[i], map, tex);
		else if ((file[i][0] == 'F' && ft_strnstr(file[i], "F", ft_strlen(file[i]))) ||
				(file[i][0] == 'C' && ft_strnstr(file[i], "C", ft_strlen(file[i]))))
			ft_check_floor_ceiling(file[i], map);
		if (!(ft_check_flags(map)) || !(ft_map_validation(file, map)))
		{
			ft_error("Invalid arguments");
			return (0);
		}
		i++;
	}
	return (1);
}

int				cub3d(char *path, int save)
{
	int			fd;
	char		**file;
	t_map		*map;
	t_textures	*textures;

	file = NULL;
	if(!(fd = open(path, O_RDONLY)) || !(map = malloc(sizeof(t_map)))
		|| !(textures = malloc(sizeof(t_textures))))
	{
		write(1, "Error\n", 6);
		strerror(errno);
		return(1);
	}
	ft_init_map(map);
	ft_init_tex(textures);
	file = ft_read_map(fd);
	close(fd);
	if(!(ft_validate(file, map, textures)))
	{
		ft_destroy_everything();
		return (0);
	}
	return (1);
}

