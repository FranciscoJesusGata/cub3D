/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:27:01 by fgata-va          #+#    #+#             */
/*   Updated: 2020/12/10 11:29:31 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define ESC 53
# define RIGHT_KEY 124
# define LEFT_KEY 123
#elif __linux__
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define ESC 65307
# define RIGHT_KEY 65363
# define LEFT_KEY 65361
#endif