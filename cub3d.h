/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:13:53 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/10 11:29:44 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "lib/mlx/mlx.h"
# include "lib/GNL/get_next_line.h"
# include "lib/libftprintf/ft_printf.h"
# include "keys.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# ifdef LEAKS
#  define LEAKS_CHECK 1
# else
#  define LEAKS_CHECK 0
# endif

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
	int		save;
	int		lines;
	int		valid_map;
}				t_map;

typedef struct	s_tex
{
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*sprite;
}				t_tex;

typedef struct	s_cub_flags
{
	int		has_resol;
	int		has_n_tex;
	int		has_w_tex;
	int		has_e_tex;
	int		has_s_tex;
	int		has_sprite;
	int		has_floor;
	int		has_clng;
}				t_cflags;

typedef struct	s_img {
void	*img;
char	*addr;
int		bpp;
int		line_length;
int		endian;
int		x;
int		y;
}				t_img;

int				cub3d(char *path, int save);
void			ft_init_map(t_map *map);
void			ft_init_tex(t_tex *tex);
void			ft_init_flags(t_cflags *flags);
int				ft_save_resol(char *line, t_map *map);
void			ft_error(const char *msg);
void			ft_check_texture(char *line, t_tex *tex, t_cflags *flags);
int				ft_check_extension(char *check, char *expected);
void			ft_check_floor_ceiling(char *line, t_map *map, t_cflags *flags);
int				*ft_save_rgb(char **args);
int				ft_check_flags(t_cflags flags);
void			ft_free_matrix(void **matrix, int lines);
int				ft_isnumber(char *s);
char			**ft_mtxdup(char **input, int lines);
char			**ft_newline(char **file, char *line, size_t size);
void			ft_save_map(t_map *data, char **file, int *i);
int				ft_ismap(char *line);
int				ft_valid_map(t_map *data);
void			ft_print_map(char **map, int lines);
void			ft_destroy_everything(t_map *map, t_tex *tex, void **file);
void			ft_print_data(t_map *data, t_tex *tex);
int				ft_count_chars(const char *s, char c);
void			ft_start_screen(t_map *data, t_tex *tex);

#endif
