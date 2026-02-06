/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:22:29 by pecastro          #+#    #+#             */
/*   Updated: 2026/02/06 19:58:20 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define GREEN_PIXEL 0xFF00
#define RED_PIXEL 0xFF0000

//rect function is just for testing:
int render_rect(t_data *data, t_rect rect)
{
    int i;
    int j;

    if (!data->win_ptr)
        return (1);
    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
        i ++;
    }
    return (0);
}

int render(t_data *data)
{
    render_rect(data, (t_rect){WIN_W - 100, WIN_H - 100, 100, 100, GREEN_PIXEL});
    render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});
    return (0);
}

//int   ft_put_image(t_data *data)

//some other functions for coloring?

void  img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}
