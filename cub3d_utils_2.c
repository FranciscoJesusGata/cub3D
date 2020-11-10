/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:34:02 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/10 12:17:31 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		*ft_matrix_cpy(void *input, int size)
{
	void	*cpy;

	if(!input || size == 0)
		return (ft_calloc(1, 1));
	if(!(cpy = malloc(size)))
		return (NULL);
	ft_memcpy(cpy, input, size);
	return (cpy);
}

int		ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (0);
	}
	return (1);
}
