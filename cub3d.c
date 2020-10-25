/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/25 12:18:31 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		*ft_resize(void *p, size_t oldlen, size_t newlen)
{
	void	*new;

	if (!p)
		return (malloc(newlen));
	if(newlen <= oldlen)
		return (p);
	new = malloc(newlen);
	ft_memcpy(new, p, newlen);
	free(p);
	return(new);
}

char		**ft_newline(char **file, char *line, size_t size)
{
	char **new_matrix;

	new_matrix = ft_resize(file, size * sizeof(char *), (size + 1) * sizeof(char *));
	new_matrix[size] = line;
	return (new_matrix);
}

void	*ft_read_map(int fd)
{
	char	*line;
	int		i;
	char	**file;

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

int			ft_validate(char **file, t_map *map)
{
	int		i;
	int		valid;

	i = 0;
	valid = 1;
	while (file[i])
	{
		if (file[i][0] == 'R' && ft_strnstr(file[i], "R", ft_strlen(file[i])))
			valid = ft_check_resol(file[i], map);
		else if (ft_strchr("NSWE",file[i][0]))
			valid = ft_check_texture(file[i], map);
		else if (file[i][0] == 'F' && ft_strnstr(file[i], "F", ft_strlen(file[i])))
			ft_check_floor(file[i], map);
		if (!valid)
		{
			ft_error("Invalid map");
			break ;
		}
		i++;
	}
	return (valid);
}

int			cub3d(char *path, int save)
{
	int		fd;
	char	**file;
	t_map	*map;


	file = NULL;
	if(!(fd = open(path, O_RDONLY)) || !(map = malloc(sizeof(t_map))))
	{
		write(1, "Error\n", 6);
		strerror(errno);
		return(1);
	}
	file = ft_read_map(fd);
	close(fd);
	ft_validate(file, map);
	return (0);
}

