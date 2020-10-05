/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/02 19:27:20 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		*ft_resize(void *p, size_t oldlen, size_t newlen)
{
	void	*new;
	size_t	len;

	new = malloc(newlen);
	if(oldlen < newlen)
		len = oldlen;
	else
		len = newlen;
	if (p && new)
		ft_memcpy(new, p, len);
	if (new)
		free(p);
	return (new);
}

char		**ft_newline(char **file, char *line, size_t size)
{
	char *new_matrix;

	new_matrix = ft_resize(file, size, (sizeof(char *) + size));
	((char **)new_matrix)[size] = line;
	line = NULL;
	return ((char **)new_matrix);
}

char		**ft_read_map(int fd)
{
	char	*line;
	int		i;
	char	**file;

	i = 0;
	while((get_next_line(fd, &line)) == 1)
	{
		file = ft_newline(file, line, (i * sizeof(char *)));
		i++;
	}
	return(file);
}

int			cube3d(char *path)
{
	int		fd;
	char	**file;
	int		i;

	if(!(fd = open(path, O_RDONLY)))
	{
		write(1, "Error\n", 6);
		return(0);
	}
	file = ft_read_map(fd);
	i = 0;
	while (file[i])
	{
		ft_printf("%s\n", file[i]);
		i++;
	}
	return (1);
}

int			main(void)
{
	return(cube3d("mapa.txt"));
}
