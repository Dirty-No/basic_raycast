/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:05:17 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/13 01:01:18 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

void	clean_all(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->scene->mlx_img);
	mlx_destroy_image(game->mlx, game->scene[1].mlx_img);
	mlx_destroy_image(game->mlx, game->minimap->mlx_img);
	mlx_destroy_image(game->mlx, game->minimap[1].mlx_img);
}

int		leave(t_game *game)
{
	clean_all(game);
    mlx_do_key_autorepeaton(game->mlx);
	exit(0);
}
