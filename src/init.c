/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:26:18 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/12 00:26:18 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    init_data(t_data *data, void *mlx, int w, int h)
{
	data->mlx_img = mlx_new_image(mlx, w, h);
	data->addr = mlx_get_data_addr(data->mlx_img, &(data->bits_per_pixel),
								 &(data->line_length), &(data->endian));
	data->width = w;
	data->height = h;
}

void	init_display(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, W_TITLE);
	game->img_ptr = game->img;
	init_data(game->img, game->mlx, W_WIDTH, W_HEIGHT);
	init_data(game->img + 1, game->mlx, W_WIDTH, W_HEIGHT);
    init_data(&(game->minimap), game->mlx, mapWidth * CELL_SIZE, mapHeight * CELL_SIZE);
	game->frame_ready = 0;
}
