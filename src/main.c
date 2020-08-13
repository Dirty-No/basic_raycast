/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:53:41 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/13 02:34:04 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_col(t_data *data, int col, double dist, int wall_color)
{
	int	start_y;
	int	end_y;
	int	wall_size;
	int	i;

	if (dist == 0)
		dist = 0.000000001;
	wall_size = W_HEIGHT / dist;
	start_y = W_HEIGHT / 2 - wall_size / 2;
	end_y =  W_HEIGHT / 2 + wall_size / 2;
	i = -1;
	while (++i < W_HEIGHT)
	{
		if (0 <= i && i < start_y)
			my_pixel_put(data, col, i, ROOF_COLOR);
		else if (start_y <= i && i <= end_y)
			my_pixel_put(data, col, i, wall_color);
		else if (end_y < i && i < W_HEIGHT)
			my_pixel_put(data, col, i, FLOOR_COLOR);
	}
}

int	get_wall(double x, double y)
{
	return (worldMap[(int)round(y)][(int)round(x)]);
}

void	raycast(t_game *game)
{
	double		x;
	double		y;
	double		dir_x;
	double 		dir_y;
	double		step_x;
	double		step_y;
	double 		dist;
	double		pxl_x;
	double		pxl_y;
	static int	rgb[6] = {0x0,0xFF0000,0xFF00,0xFF, 0xFFFF, 0xFF00FF};
	int			col = -1;

	dir_x = game->dir_x;
	dir_y = game->dir_y;
	rotate_vect(&dir_x, &dir_y, -FOV / 2);
	while (++col < W_WIDTH)
	{
		x = game->x;
		y = game->y;
		step_x = dir_x * RAY_STEP;
		step_y = dir_y * RAY_STEP;
		while (!get_wall(x, y))
		{
			get_grid_coord(x, y, &pxl_x, &pxl_y);
			my_pixel_put(game->minimap_ptr, pxl_x, pxl_y, 0xFFFFFF);
			if (get_wall(x + step_x, y + step_y)
			|| get_wall(x + step_x / 2, y + step_y / 2))
			{
				x += step_x * RAYCAST_CLOSE_STEP;
				y += step_y * RAYCAST_CLOSE_STEP;	
			}
			else
			{
				x += step_x;
				y += step_y;
			}
		}
		dist = my_dist(game->x, game->y, x, y);
		draw_col(game->scene_ptr, col, dist, rgb[get_wall(x ,y)]);
		rotate_vect(&dir_x, &dir_y, ANGLE_INC);
	}
}

int		keys_handler(t_game *game, t_key keys[K_BUFF_SIZE])
{
	if (key_chr(keys, ESC_KEY, K_BUFF_SIZE))
		leave(game);
	if (key_chr(keys, FORWARD_KEY, K_BUFF_SIZE))
	{
		game->x += SPEED * game->dir_x;
		game->y += SPEED * game->dir_y;
	}
	if (key_chr(keys, BACKWARD_KEY, K_BUFF_SIZE))
	{
		game->x -= SPEED * game->dir_x;
		game->y -= SPEED * game->dir_y;
	}
	if (key_chr(keys, RIGHT_KEY, K_BUFF_SIZE))
	{
		game->y += SPEED * game->dir_x;
		game->x -= SPEED * game->dir_y;	}
	if (key_chr(keys, LEFT_KEY, K_BUFF_SIZE))
	{
		game->y -= SPEED * game->dir_x;
		game->x += SPEED * game->dir_y;
	}
	if (key_chr(keys, ARROW_RIGHT_KEY, K_BUFF_SIZE))
		rotate_vect(&(game->dir_x), &(game->dir_y), TURN_ANGLE);
	if (key_chr(keys, ARROW_LEFT_KEY, K_BUFF_SIZE))
		rotate_vect(&(game->dir_x), &(game->dir_y), -TURN_ANGLE);
	return (0);
}

int		loop_handler(t_game *game)
{
	keys_handler(game, game->keys);
	if (!game->frame_ready)
	{
		minimap(game);
		raycast(game);
		draw_fov(game);
		game->frame_ready = 1;
	}
	refresh(game);
	return (0);
}

int		main(void)
{
	t_game	game;
	
	game = (t_game){0};
	game.x = mapWidth / 2;
	game.y = mapHeight / 2;
	init_display(&game);
	draw_grid(game.scene, 0xFF);
	draw_grid(game.scene + 1, 0xFF0000);
	game.dir_x = 1;
	game.dir_y = 0;
	mlx_do_key_autorepeaton(game.mlx);
	init_keys(game.keys);
	mlx_loop_hook(game.mlx, loop_handler, (void *)&game);
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, key_press_hook, game.keys);
	mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, game.keys);
	mlx_hook(game.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, leave, &game);
	mlx_loop(game.mlx);
	return (0);
}
