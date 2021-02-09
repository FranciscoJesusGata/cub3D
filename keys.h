/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:27:01 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/28 11:51:35 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
# ifdef __APPLE__
#  define MAC_VERSION 1
#  define W_KEY 13
#  define S_KEY 1
#  define A_KEY 0
#  define D_KEY 2
#  define ESC 53
#  define SHIFT 57
#  define DOWN_KEY 125
#  define UP_KEY 126
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define LEFT_CTRL 59
#  define SPACE 49
#  define ABS abs
# elif __linux__
#  define MAC_VERSION 0
#  define W_KEY 119
#  define S_KEY 115
#  define A_KEY 97
#  define D_KEY 100
#  define ESC 65307
#  define SHIFT 57
#  define DOWN_KEY 65364
#  define UP_KEY 65362
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
#  define LEFT_CTRL 65507
#  define SPACE	32
#  define ABS fabs
# endif
#endif
