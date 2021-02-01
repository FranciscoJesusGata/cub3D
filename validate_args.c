/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:26:26 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/01 11:24:52 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_save_tex(int *flag, char **tex, char *path)
{
	if (*flag == 0)
		*tex = path;
	*flag += 1;
}

int			ft_tex_flag(char *line, t_cflags *flags, t_tex *tex, char *path)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		ft_save_tex(&(flags->has_n_tex), &(tex->n_texture), path);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ft_save_tex(&(flags->has_s_tex), &(tex->s_texture), path);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ft_save_tex(&(flags->has_w_tex), &(tex->w_texture), path);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ft_save_tex(&(flags->has_e_tex), &(tex->e_texture), path);
	else if (ft_strncmp(line, "S ", 2) == 0)
		ft_save_tex(&(flags->has_sprite), &(tex->sprite), path);
	else
		return (0);
	return (1);
}

void		ft_check_texture(char *line, t_tex *tex, t_cflags *flags)
{
	int		fd;
	char	*path;

	path = ft_strtrim(line, "\t\v\f\r NSWEAO");
	if (!path || ((fd = open(path, O_RDONLY)) == -1) ||
		(!ft_check_extension(path, ".xpm") &&
		!(ft_check_extension(path, ".png") && MAC_VERSION)))
	{
		if (MAC_VERSION)
			ft_printf("Error\nTexture \"%s\" doesn't \
exists or isn't XPM or PNG format\n", path);
		else
			ft_printf("Error\nTexture \"%s\" doesn't \
exists or isn't XPM format\n", path);
		free(path);
		path = NULL;
		return ;
	}
	close(fd);
	if (ft_tex_flag(line, flags, tex, path) == 0)
		ft_error("Texture identificator invalid");
}

void		ft_check_floor_ceiling(char *line, t_map *map, t_cflags *flags)
{
	char	**args;
	int		*nums;
	int		i;

	if (!(args = ft_split((line + 1), ',')) ||
		ft_count_chars(line, ',') != 2)
	{
		ft_error("Not enought numbers in floor/ceiling");
		return ;
	}
	if (!(nums = ft_save_rgb(args, line[0])))
		return ;
	i = 0;
	while (i < 3)
	{
		if (line[0] == 'F')
			map->floor[i] = nums[i];
		else
			map->ceiling[i] = nums[i];
		i++;
	}
	if (line[0] == 'F')
		flags->has_floor += 1;
	else
		flags->has_clng += 1;
	free(nums);
}

int			ft_check_flags(t_cflags flags)
{
	if (flags.has_resol != 1 || flags.has_n_tex != 1 || flags.has_w_tex != 1 ||
		flags.has_e_tex != 1 || flags.has_s_tex != 1 || flags.has_sprite != 1 ||
		flags.has_floor != 1 || flags.has_clng != 1)
		{
			ft_error("Invalid number of arguments");
			return (0);
		}
	return (1);
}
