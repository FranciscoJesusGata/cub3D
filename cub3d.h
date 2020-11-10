/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:13:53 by fgata-va          #+#    #+#             */
/*   Updated: 2020/11/10 12:27:55 by fgata-va         ###   ########.fr       */
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
	int		player_x;
	int		player_y;
}				t_map;

typedef struct s_textures
{
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*sprite;
}				t_textures;

typedef struct s_cub_flags
{
	int		has_resol;
	int		has_n_tex;
	int		has_w_tex;
	int		has_e_tex;
	int		has_s_tex;
	int		has_sprite;
	int		has_floor;
	int		has_clng;
}				t_cub_flags;

int				cub3d(char *path);
void			ft_init_map(t_map *map);
void			ft_init_tex(t_textures *tex);
void			ft_init_flags(t_cub_flags *flags);
int				ft_check_resol(char *line ,t_map *map);
void			ft_error(const char *msg);
void			ft_check_texture(char *line, t_textures *tex, t_cub_flags *flags);
int				ft_check_extension(char *check, char *expected);
void			ft_check_floor_ceiling(char *line, t_map *map, t_cub_flags *flags);
int				ft_check_flags(t_cub_flags flags);
void			ft_free_matrix(void **matrix);
int				ft_isnumber(char *s);
void			*ft_matrix_cpy(void *input, int size);

#endif
