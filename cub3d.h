/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:13:53 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/08 09:57:57 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "lib/GNL/get_next_line.h"
# include "lib/libftprintf/ft_printf.h"
# include "keys.h"
# if MAC_VERSION
#  include "lib/mlx/mlx.h"
# else
#  include "lib/mlx_linux/mlx.h"
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <signal.h>
# ifndef BONUS
#  define BONUS 0
# endif

typedef	struct	s_moves
{
	int		forward;
	int		backward;
	int		right;
	int		left;
	int		r_rotation;
	int		l_rotation;
	int		look_up;
	int		look_down;
	int		crouch;
	int		jump;
	int		ascend;
	int		fall;
}				t_moves;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_sprite
{
	int			x;
	int			y;
	int			width;
	int			height;
	double		perpdist;
	int			draw_x[2];
	int			draw_y[2];
	int			print_x;
	int			tex[2];
}				t_sprite;

typedef struct	s_map{
	int			resolution[2];
	int			max_r[2];
	char		**map_matrix;
	int			floor[3];
	int			ceiling[3];
	void		*mlx_ptr;
	void		*window;
	int			max_y;
	double		player_x;
	double		player_y;
	double		dir[2];
	double		plane[2];
	int			save;
	int			lines;
	int			valid_map;
	int			draw_start;
	int			draw_end;
	int			num_sprites;
	int			*ray_buffer;
	t_moves		*movement;
	t_img		img;
	t_sprite	*sprites;
	double		vertical_angle;
	double		vertical_pos;
	double		vertical_total;
	pid_t		music_process;
}				t_map;

typedef struct	s_tex_img
{
	t_img		img;
	int			height;
	int			width;
	int			coords[2];
}				t_tex_img;

typedef struct	s_tex
{
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char		*sprite;
	t_tex_img	textures[5];
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

typedef struct	s_ray
{
	double	pos[2];
	int		map[2];
	double	dir[2];
	int		step[2];
	double	side_dist[2];
	int		side;
	double	perpwalldist;
}				t_ray;

typedef struct	s_args
{
	t_map		*data;
	t_tex		*tex;
	void		*file;
}				t_args;

int				cub3d(char *path, int save);
void			ft_init_map(t_map *map);
void			ft_init_tex(t_tex *tex);
void			ft_init_flags(t_cflags *flags);
void			ft_init_raycast(t_map *data, t_moves *mvnt,\
						t_tex *tex, t_args *args);
int				ft_save_resol(char *line, t_map *map);
void			ft_error(const char *msg);
void			ft_check_texture(char *line, t_tex *tex, t_cflags *flags);
int				ft_check_extension(char *check, char *expected);
void			ft_check_floor_ceiling(char *line, t_map *map, t_cflags *flags);
int				*ft_save_rgb(char **args, int id);
int				ft_check_flags(t_cflags flags);
void			ft_free_matrix(void **matrix, int lines);
int				ft_isnumber(char *s, int id);
char			**ft_mtxdup(char **input, int lines);
char			**ft_newline(char **file, char *line, size_t size);
void			ft_save_map(t_map *data, char **file, int *i);
void			ft_set_orientation(char player, t_map *data);
int				ft_ismap(char *line);
int				ft_valid_map(t_map *data);
void			ft_free_textures(t_tex *tex, t_map *data);
void			ft_free_data(t_map *data);
void			free_mlx(t_map *data);
void			ft_free_all(t_map *data, t_tex *textures, void **file);
int				end_program(t_args *game_data);
int				ft_count_chars(const char *s, char c);
void			ft_start_screen(t_map *data, t_tex *tex, char **file);
int				main_loop(t_args *args);
void			ft_raycasting(t_map *data, t_tex *tex);
void			ft_get_raydir(int x, int w, t_ray *ray, t_map *data);
void			ft_shoot_rays(t_ray *ray, double deltadist[], \
								t_map *data, int x);
void			ft_init_sidedist(t_ray *ray, double deltadist[]);
void			ft_init_sidedist(t_ray *ray, double deltadist[]);
void			ft_get_delta(t_ray *ray, double *deltadist_x, \
							double *deltadist_y);
void			buffer_pixel(t_img *frame, int x, int y, int color);
void			buffer_line(t_map *data, t_tex_img *texture, int x,\
							int lineheight);
int				rgb_to_hex(int t, int r, int g, int b);
void			create_img(t_map *data, t_img *img);
void			load_texture(t_map *data, t_tex_img *texture, char *path);
void			ft_buffer(t_map *data, t_tex *tex, t_ray *ray, int x);
int				get_pixel(t_img *frame, int x, int y);
void			ft_move(t_map *data);
void			ft_rotate(t_map *data);
void			sprite_size(t_map *data, t_sprite sprite, \
							double transform[], t_tex_img texture);
void			buffer_sprites(t_map *data, t_tex_img spritetex);
void			ft_save_sprites(t_map *data);
void			ft_update_sprites(t_map *data);
void			createbmp(t_args *data);

#endif
