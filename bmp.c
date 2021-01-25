/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 20:17:40 by fgata-va          #+#    #+#             */
/*   Updated: 2021/01/25 01:24:08 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    createHeader(t_map *data, unsigned char *fileheader, unsigned char *infoheader, int filesize)
{
    fileheader[0] = (unsigned char)'B';
    fileheader[1] = (unsigned char)'M';
    fileheader[2] = (unsigned char)(filesize);
    fileheader[3] = (unsigned char)(filesize >> 8);
    fileheader[4] = (unsigned char)(filesize >> 16);
    fileheader[5] = (unsigned char)(filesize >> 24);
    fileheader[10] = (unsigned char)(14 + 40);
    infoheader[0] = (unsigned char)40;
    infoheader[4] = (unsigned char)(data->resolution[0]);
    infoheader[5] = (unsigned char)(data->resolution[0] >> 8);
    infoheader[6] = (unsigned char)(data->resolution[0] >> 16);
    infoheader[7] = (unsigned char)(data->resolution[0] >> 24);
    infoheader[8] = (unsigned char)(data->resolution[1]);
    infoheader[9] = (unsigned char)(data->resolution[1] >> 8);
    infoheader[10] = (unsigned char)(data->resolution[1] >> 16);
    infoheader[11] = (unsigned char)(data->resolution[1] >> 24);
    infoheader[12] = (unsigned char)1;
    infoheader[14] = (unsigned char)24;
}

void     writeBits(t_map *data, int padding, int fd)
{
    int                     i;
    int                     j;
    int                     color;
    static unsigned char    zero[3];

    ft_bzero(zero, 3);
    i = data->resolution[1] - 1;
    while (i >= 0)
    {
        j = 0;
        while (j < data->resolution[0])
        {
            color = get_pixel(&data->img, j, i);
            write(fd, &color, 3);
            j++;
        }
        if (padding > 0)
            write(fd, &zero, padding);
        i--;
    }
}

void     createbmp(t_map *data)
{
    int             fd;
    unsigned char   fileheader[14];
    unsigned char   infoheader[40];
    int             filesize;
    int             padding;

    if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0777)) < 0)
    {
        ft_error("Couldn't create de bmp file");
        return ;
    }
    ft_bzero(fileheader, 14);
    ft_bzero(infoheader, 40);
    padding = (4 - (3 * data->resolution[0]) % 4) % 4;
    filesize = 40 + 14 + (3 * data->resolution[0] + padding) * data->resolution[1];
    createHeader(data, fileheader, infoheader, filesize);
    write(fd, &fileheader, 14);
    write(fd, &infoheader, 40);
    writeBits(data, padding, fd);
}