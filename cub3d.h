/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:13:53 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/04 12:03:12 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "lib/mlx/mlx.h"
# include "lib/GNL/get_next_line.h"
# include "lib/libftprintf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct	s_map{
	int		resolution[2];
	int		max_r[2];
	char	**map_matrix;
	int		floor[3];
	int		ceiling[3];
	void	*mlx_ptr;
	void	*window;
	int		max_y;
	int		flags[8];
	char	*ft_get_path(char *line);
}				t_map;

typedef struct s_textures
{
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*sprite;
}				t_textures;

int				cub3d(char *path, int save);
void			ft_init_map(t_map *map);
void			ft_init_tex(t_textures *tex);
int				ft_check_resol(char *line ,t_map *map);
void			ft_error(const char *msg);
void			ft_check_texture(char *line, t_map *map, t_textures *tex);
int				ft_check_extension(char *check, char *expected);
void			ft_check_floor_ceiling(char *line, t_map *map);
int				ft_check_flags(t_map *map);
void			ft_free_matrix(void **matrix);
int				ft_isnumber(char *s);

#endif
