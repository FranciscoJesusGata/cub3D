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

void		ft_newline(char ***file, char *line, int i)
{
	char	**tmp;
	int	j;

	tmp = (char **)malloc(i * sizeof(char *));
	if (i == 1)
	{
		*tmp = line;
		*file = tmp;
	}
	else
	{
		j = 0;
		while (j < i - 1)
		{
			tmp[j] = *file[j]; 
			j++;
		}
		tmp[j] = line;
		free(*file);
		*file = tmp;
	}
}

char		**ft_read_map(int fd)
{
	char	*line;
	int		i;
	char	**file;

	i = 0;
	while((get_next_line(fd, &line)) == 1)
	{
		i++;
		ft_newline(&file, line, i);
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
