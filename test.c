#include "cube3d.h"

int			main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		length;
	int		max_w;
	int		max_l;

	if (argc != 3)
	{
		ft_printf("Invalid number of arguments!\n");
		return(0);
	}
	mlx_ptr = mlx_init();
	mlx_get_screen_size(mlx_ptr, &max_w ,&max_l);
	width = ft_atoi(argv[1]);
	length = ft_atoi(argv[2]);
	if(width > max_w)
		width = max_w;
	if (length > max_l)
		length = max_l;
	win_ptr = mlx_new_window(mlx_ptr, width, length, "test");
	mlx_loop(mlx_ptr);
}
