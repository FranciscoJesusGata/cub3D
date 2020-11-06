/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:04:15 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/06 13:02:47 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			main(void)
{
	char		*file[] = {
	"R		6000   6000",
	"F 255, 20,		0",
	"C	200, 50,     100",
	"NO	./textures/bluestone.png",
	"SO     ./textures/1.GIF",
	"WE	 ./textures/colorstone.png",
	"EA  ./textures/17.GIF",
	"S		./textures/barrel.png"
	};
	int			i;
	t_map		map;
	t_textures	tex;
	t_cub_flags	flags;
	char		*line;

	i = 0;
	ft_init_map(&map);
	ft_init_tex(&tex);

	i = 0;
	while (i < 8)
	{
		line = ft_strtrim(file[i], "\t\v\f\r ");
		if (line[0] == 'R' && ft_strnstr(line, "R", ft_strlen(line)))
			flags.has_resol += ft_check_resol(line, &map);
		else if (ft_strchr("NSWE",line[0]))
			ft_check_texture(line, &tex, &flags);
		else if ((line[0] == 'F' && ft_strnstr(line, "F", ft_strlen(line))) ||
				(line[0] == 'C' && ft_strnstr(line, "C", ft_strlen(line))))
			ft_check_floor_ceiling(line, &map, &flags);
		free(line);
		i++;
	}

	if (!(ft_check_flags(flags)) /*|| !(ft_map_validation(file, map))*/)
	{
		ft_error("Invalid arguments");
		return (0);
	}
	ft_printf("Max Resolution %d, %d\n", map.max_r[0], map.max_r[1]);
	ft_printf("R %d, %d\n", map.resolution[0], map.resolution[1]);
	ft_printf("F %d, %d, %d\n", map.floor[0], map.floor[1], map.floor[2]);
	ft_printf("C %d, %d, %d\n", map.ceiling[0], map.ceiling[1], map.ceiling[2]);
	return (0);
}
