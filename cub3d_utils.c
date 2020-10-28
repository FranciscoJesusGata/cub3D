/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 10:55:24 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/28 11:46:00 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_free_matrix(void **matrix)
{
	int		i;

	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int			ft_check_extension(char *check, char *expected)
{
	int		i;
	char	*extension;

	i = 0;
	if (!check)
		return (0);
	while (check[i] && check[i] != '.')
		i++;
	if (check[i] == '\0')
		return (0);
	extension = check + i;
	if (!(ft_strnstr(extension, expected, ft_strlen(expected))))
		return (0);
	return (1);
}

void	ft_error(const char *msg)
{
	ft_printf("Error\n");
	if (msg)
		ft_printf(msg);
}
