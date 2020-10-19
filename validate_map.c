/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:11:43 by fgata-va          #+#    #+#             */
/*   Updated: 2020/10/19 13:41:33 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_check_resol(char *line ,t_map *map)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while(line[i])
	{
		if(ft_isdigit(line[i]) && j < 2)
		{
			map->resolution[j] = ft_atoi(line + i);
			j++;
		}
		else if ((ft_isdigit(line[i])&& j >= 2) || 
				!(ft_strchr("\t\v\f\r ", line[i])))
			return (0);
		i++;
	}
	if (j < 2)
		return (0);
	return (1);
}

int			ft_check_texture(char *line, t_map *map)
{
	int		i;
	int		len;
	int		fd;
	char	*path;

	i = 2;
	len = 0;
	while(ft_strchr("\t\v\f\r ", line[i]))
		i++;
	while (!(ft_strchr("\t\v\f\r ", line[i])))
		len++;
	path = ft_substr(line, i, len);
	if(((fd = open(path, O_RDONLY)) == -1) && (!(ft_check_extension(path, ".xpm"))))
	{
		ft_printf("Texture file doesn't exists or format not valid");
		free(path);
		return(0);
	}
	close(fd);
	if (line[0] == 'N' && ft_strnstr(line, "NO", ft_strlen(line)))
		map->n_texture = path;
	else if (line[0] == 'S' && ft_strnstr(line, "SO", ft_strlen(line)))
		map->s_texture = path;
	else if (line[0] == 'W' && ft_strnstr(line, "WE", ft_strlen(line)))
		map->w_texture = path;
	else if (line[0] == 'E' && ft_strnstr(line, "EA", ft_strlen(line)))
		map->e_texture = path;
	else if (line[0] == 'S' && ft_strnstr(line, "S", ft_strlen(line)))
		map->sprite = path;
	return(1);
}

int			ft_check_floor(char *line, t_map *map)
{
	return (1);
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

