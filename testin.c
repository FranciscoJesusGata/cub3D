/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:04:15 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/30 12:58:11 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			main(void)
{
	char	*file[] = {
	"R		6000   6000",
	"F 255, 20,		0",
	};
	int		i;
	int		valid;
	t_map	map;

	i = 0;
	valid = 1;
	map.mlx_ptr = mlx_init();
	mlx_get_screen_size(map.mlx_ptr, &(map.max_r[0]),&(map.max_r[1]));
	while (i < 2)
	{
		if (file[i][0] == 'R' && ft_strnstr(file[i], "R", ft_strlen(file[i])))
			valid = ft_check_resol(file[i], &map);
		/*else if (ft_strchr("NSWE",file[i][0]))
			valid = ft_check_texture(file[i], map);*/
		else if (file[i][0] == 'F' && ft_strnstr(file[i], "F", ft_strlen(file[i])))
			valid = ft_check_floor(file[i], &map);
		if (!valid)
		{
			ft_error("Invalid map");
			return (0);
		}
		i++;
	}
ft_printf("Max Resolution %d, %d\n", map.max_r[0], map.max_r[1]);
	ft_printf("R %d, %d\nF %d, %d, %d", map.resolution[0], map.resolution[1], map.floor[0], map.floor[1], map.floor[2]);
	return (0);
}