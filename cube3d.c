/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/06 10:24:06 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	new_matrix[size] = ft_strdup(line);
	free(line);
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
	free(line);
	file[i] = NULL;
	return(file);
}

int			cube3d(char *path)
{
	int		fd;
	char	**file;
	int		i;

	file = NULL;
	if(!(fd = open(path, O_RDONLY)))
	{
		write(1, "Error\n", 6);
		return(1);
	}
	file = ft_read_map(fd);
	i = 0;
	while (file[i])
	{
		ft_printf("%s\n", file[i]);
		free(file[i]);
		i++;
	}
	free(file[i]);
	free(file);
	return (0);
}

int			main(void)
{
	return(cube3d("mapa.txt"));
}
