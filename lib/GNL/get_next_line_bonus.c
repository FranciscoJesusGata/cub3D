/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:04:00 by fgata-va          #+#    #+#             */
/*   Updated: 2020/01/14 19:27:00 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char				*ft_clean_line(char *save, char **line, int r)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			break ;
		i++;
	}
	if (i < ft_strlen(save))
	{
		*line = ft_substr(save, 0, i);
		tmp = ft_substr(save, i + 1, ft_strlen(save));
		free(save);
		save = ft_strdup(tmp);
		free(tmp);
	}
	else if (r == 0)
	{
		*line = save;
		save = NULL;
	}
	return (save);
}

char				*ft_save(char *buffer, char *save)
{
	char			*tmp;

	if (save)
	{
		tmp = ft_strjoin(save, buffer);
		free(save);
		save = ft_strdup(tmp);
		free(tmp);
	}
	else
		save = ft_strdup(buffer);
	return (save);
}

int					get_next_line(int fd, char **line)
{
	static char		*save[4096];
	char			buffer[BUFFER_SIZE + 1];
	int				r;

	while ((r = read(fd, buffer, BUFFER_SIZE)))
	{
		if (r == -1)
			return (-1);
		buffer[r] = '\0';
		save[fd] = ft_save(buffer, save[fd]);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (r <= 0 && !save[fd])
	{
		*line = ft_strdup("");
		return (r);
	}
	save[fd] = ft_clean_line(save[fd], line, r);
	if (r <= 0 && !save[fd])
		return (r);
	return (1);
}
