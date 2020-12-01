/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:49:20 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/01 10:55:51 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_args(int argc)
{
	if (argc > 3)
	{
		ft_error("Too many arguments. \
Cub3d takes 1 or 2 arguments: \"/path/to/map.cub\" and --save\n");
		return (0);
	}
	else if (argc < 2)
	{
		ft_error("Not enought arguments. \
Cub3d takes 1 or 2 arguments: \"/path/to/map.cub\" and --save\n");
		return (0);
	}
	return (1);
}

int		ft_check_save(char **argv, int *save)
{
	if ((ft_strncmp(argv[2], "--save", ft_strlen(argv[2]))) != 0)
	{
		ft_error("You can only use the \"--save\" flag");
		return (1);
	}
	*save = 1;
	return (0);
}

int		main(int argc, char **argv)
{
	int	save;
	int	valid;

	save = 0;
	valid = 0;
	if (ft_check_args(argc))
	{
		if (!(ft_check_extension(argv[1], ".cub")))
		{
			ft_error("Bad file extension. Cub3d only takes \".cub\" files\n");
			return (1);
		}
		if (argc == 3)
			valid = ft_check_save(argv, &save);
		valid = cub3d(argv[1], save);
		if (LEAKS_CHECK == 1)
			system("leaks cub3D");
	}
	else
		valid = 1;
	return (valid);
}
