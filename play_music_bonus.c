/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:34:47 by fgata-va          #+#    #+#             */
/*   Updated: 2021/02/02 10:09:06 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_bonus.h"

pid_t		start_music(void)
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid < 0)
	{
		ft_error("Music process couldn't be forked :(");
		return (-1);
	}
	else if (!(open("audio/music.wav", O_RDONLY)))
	{
		ft_printf("Warning: The file \"audio/music.wav\" wasn't found, music won't play.\n");
		return (-1);
	}
	else if (pid == 0)
	{
		if (MAC_VERSION)
		{
			args = ft_split("afplay audio/music.wav", ' ');
			execv("/usr/bin/afplay", args);
		}
		else
		{
			args = ft_split("aplay -q audio/music.wav", ' ');
			execv("/usr/bin/aplay", args);
		}
	}
	return (pid);
}
