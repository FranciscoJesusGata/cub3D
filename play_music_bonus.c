/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:34:47 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/29 20:18:17 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

pid_t		start_music()
{
	pid_t	pid;

	char	**args;

	pid = fork();
	args = ft_split("aplay -q audio/music.wav", ' ');
	args[4] = NULL;
	if (pid < 0)
	{
		ft_error("Music process couldn't be forked :(");
		return -1;
	}
	else if (pid == 0)
		if (MAC_VERSION)
		{
			args = ft_split("afplay -q audio/music.wav", ' ');
			execv("/usr/bin/afplay", args);
		}
		else
		{
			args = ft_split("aplay -q audio/music.wav", ' ');
			execv("/usr/bin/aplay",args);
		}
	return pid;
}