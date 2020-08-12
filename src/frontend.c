/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:29:26 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/12 00:29:26 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** THIS IS HOW YOU DRAW INSIDE AN MLX IMAGE 
*/

void    my_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x <= 0 || x >= data->width || y <= 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * data->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	copy_image(t_data *src, t_data *dst)
{
	int	i;

	i = -1;
	while (++i < (dst->width * dst->height * dst->bits_per_pixel / 8)
			&& i < (src->width * src->height * src->bits_per_pixel / 8))
		(dst->addr)[i] = (char)(src->addr)[i];
}

void	*refresh(t_game *game)
{
	static clock_t	t0 = 0;
	static int i = 0;

	if (game->frame_ready && (!FRAME_CAP
	|| (double)(clock() - t0) > (double)CLOCKS_PER_SEC / (double)FRAME_CAP))
	{
		mlx_put_image_to_window(game->mlx, game->win,
								game->img_ptr->mlx_img, 0, 0);
        mlx_put_image_to_window(game->mlx, game->win, game->minimap.mlx_img, 0, 0);
		game->img_ptr = game->img + i++ % 2;
		t0 = clock();
		game->frame_ready = 0;
	}
	return (NULL);
}
