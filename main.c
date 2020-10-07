/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:49:20 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/07 12:33:22 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(const char *msg)
{
	ft_printf("Error\n");
	if (msg)
		ft_printf(msg);
}

int		main(int argc, char **argv)
{

	int	save;

	save = 0;
	if (argc > 3)
	{
		ft_error("Too many arguments. \
Cub3d takes 1 or 2 arguments: \"/path/to/map.cub\" and --save\n");
		return(1);
	}
	else if (argc < 2)
	{
		ft_error("Not enought arguments. \
Cub3d takes 1 or 2 arguments: \"/path/to/map.cub\" and --save\n");
		return(1);
	}
	else
	{
		if(!(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))))
		{
			ft_error("Bad file extension. Cub3d only takes \".cub\" files\n");
			return(1);
		}
		if(argc == 3)
			{
				if(!(ft_strncmp(argv[2], "--save", ft_strlen(argv[2]))))
				{
					ft_error("You can only use the \"--save\" flag");
					return(1);
				}
				save = 1;
			}
		cub3d(argv[1], save);
	}
}
