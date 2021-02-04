/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:34:02 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/04 19:20:22 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_mtxdup(char **input, int lines)
{
	char	**cpy;
	int		i;

	if (!input || lines == 0 || !(cpy = malloc(lines * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < lines)
	{
		cpy[i] = ft_strdup(input[i]);
		i++;
	}
	return (cpy);
}

int		ft_isnumber(char *s, int id)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			if (id == 'C')
				ft_error("The ceiling values are invalid");
			else
				ft_error("The floor values are invalid");
			free(s);
			return (0);
		}
		i++;
	}
	return (1);
}

int		end_program(t_args *game_data)
{
	ft_free_all(game_data->data, game_data->tex, game_data->file);
	if (BONUS && game_data->data->music_process >= 0)
		kill(game_data->data->music_process, 9);
	ft_printf("See you, space cowboy\n");
	exit(0);
	return (0);
}
