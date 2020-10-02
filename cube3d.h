/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:13:53 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/02 10:44:33 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "lib/mlx/mlx.h"
# include "lib/GNL/get_next_line.h"
# include "lib/libftprintf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_map{
	int		resolution[2];
	char	**map_matrix;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	int		floor[3];
	void	*mlx_ptr;
	void	*window;
}				t_map;

#endif
