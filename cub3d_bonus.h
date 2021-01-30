/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 00:32:36 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/29 19:40:33 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include "cub3d.h"

void		verticalrot_bonus(t_map *data);
void		crouch_bonus(t_map *data);
void		jump_bonus(t_map *data);
pid_t		start_music();

#endif