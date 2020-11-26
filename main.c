/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:49:20 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/26 12:13:51 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{

	int	save;

	save = 0;
	if (argc > 3)
	{
		ft_error("Too many arguments. \
Cub3d takes 1 or 2 arguments: \"/path/to/map.cub\" and --save\n");
		return(0);
	}
	else if (argc < 2)
	{
		ft_error("Not enought arguments. \
Cub3d takes 1 or 2 arguments: \"/path/to/map.cub\" and --save\n");
		return (0);
	}
	else
	{
		if(!(ft_check_extension(argv[1], ".cub")))
		{
			ft_error("Bad file extension. Cub3d only takes \".cub\" files\n");
			return (0);
		}
		if(argc == 3)
			{
				if(!(ft_strncmp(argv[2], "--save", ft_strlen(argv[2]))))
				{
					ft_error("You can only use the \"--save\" flag");
					return(0);
				}
				save = 1;
			}
		cub3d(argv[1], save);
		//system("leaks cub3D");
	}
}
