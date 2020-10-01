/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:40:34 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/01 13:02:21 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		ft_

char		**ft_read_map(int fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while((get_next_line(fd, &line)) = 1)
	{}
}

int			cube3d(char *path)
{
	int		fd;
	t_map	map;
	char	**file;

	if(!(fd = open(path, O_RDONLY)))
	{
		write(1, "Error\n", 6);
		return(0);
	}
	ft_read_map(fd);
	return (1);
}
