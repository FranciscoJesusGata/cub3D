#include "lib/mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_data {
void	*img;
char	*addr;
int		bits_per_pixel;
int		line_length;
int		endian;
int		x;
int		y;
}				t_data;

typedef struct	s_vars {
void	*mlx;
void	*win;
t_data	*img;
}				t_vars;


void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void		ft_print_square(t_vars *vars, int side, t_data *img, int color, int width, int height)
{
	int		i;
	int		j;

	img->img = mlx_new_image(vars->mlx, side, side);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
		&img->endian);
	i = 0;
	while (i < side)
	{
		j = 0;
		while (j < side)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, (width - i) / 2, (height - j) / 2);
}

int			square(int n)
{
	return (n * n);
}

void		ft_print_circle(t_vars *vars, int color, int a, int b)
{
	int x;
	int y;
	int	d;
	int	r;
	t_data *img;

	img = vars->img;
	r = 10;
	d = r * 2;
	img->img = mlx_new_image(vars->mlx, 1000, 800);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
		&img->endian);
	y = b - r;
	while (y >= b - r && y <= d)
	{
		x = a - r;
		while (x >= a - r && x <= d)
		{
			if (square(x - a) + square(y - r) <= (r * r))
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void		ft_move(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	ft_print_circle(vars, 0x000000FF, vars->img->x, vars->img->y);
	printf("circle is in %d,%d\n",vars->img->x,vars->img->y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, vars->img->x,vars->img->y);
}

int			ft_control_key(int keycode, t_vars *vars)
{
	printf("Key %d pressed\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	/* w = 13
	** a = 0
	** s = 1
	** d = 2
	*/
	else if (keycode == 13 && vars->img->y > 0)
	{
		vars->img->y -= 10;
		ft_move(vars);
		
	}
	else if (keycode == 1 && vars->img->y < 800)
	{
		vars->img->y += 10;
		ft_move(vars);
	}
	else if (keycode == 0 && vars->img->x > 0)
	{
		vars->img->x -= 10;
		ft_move(vars);
	}
	else if (keycode == 2 && vars->img->x < 800)
	{
		vars->img->x += 10;
		ft_move(vars);
	}
	return (0);
}

int			ft_mouse_pos(int x, int y, t_vars *vars)
{
	if (x >= 0 && x <= 1000 && y >= 0 && y <= 800)
		printf("Mouse is in x = %d, y = %d\n", x, y);
	return (0);
}

int			ft_window_closed(void)
{
	exit(0);
}

int			main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 800, "Hello world!");
	img.x = (1000 / 2) - 10;
	img.y = (800 / 2) - 10;
	vars.img = &img;
	//ft_print_square(&vars, 500, &img, 0x00FF0000, 1000, 800);
	ft_print_circle(&vars, 0x000000FF, img.x, img.y);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 6, (1L<<6), ft_mouse_pos, &vars);
	mlx_hook(vars.win, 17, 0L, ft_window_closed, 0);
	mlx_key_hook(vars.win, ft_control_key, &vars);
	mlx_loop(vars.mlx);
}
