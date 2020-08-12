/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:53:41 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/10 19:12:19 by smaccary         ###   ########.fr       */
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

/*
void	raycast(t_game *game)
{
	double		x;
	double		y;
	double		dir_x;
	double 	dir_y;
	double		step_x;
	double		step_y;
	//int 	dist;
	//static int		rgb[5] = {0xFFFFFF,0xFF0000,0xFF00,0xFF, 0xFFFF};
	int		col = -1;

	dir_x = game->dir_x;
	dir_y = game->dir_x;
	while (++col < W_WIDTH)
	{
		x = game->x;
		y = game->y;
		//step_x = (dir_x >= 0) ? 0.1 : -0.1;
		//step_y = (dir_y >= 0) ? 0.1 : -0.1;
		step_x = dir_x * 0.1;
		step_y = dir_y * 0.1;
		while (!worldMap[(int)x][(int)y])
		{
			fill_cell(game->img_ptr, x, y, 0xFF00FF);
			x += step_x;
			y += step_y;
		}
		rotate_vect(&dir_x, &dir_y, 0.1);
		printf("%lf %lf\n", dir_x, dir_y);
	}
	fill_cell(game->img_ptr, game->x, game->y, 0xFF0000);
}
*/

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
		//step_x = (dir_x >= 0) ? 0.1 : -0.1;
		//step_y = (dir_y >= 0) ? 0.1 : -0.1;
		step_x = dir_x * RAY_STEP;
		step_y = dir_y * RAY_STEP;
		while (!worldMap[(int)round(y)][(int)round(x)])
		{
			//fill_cell(game->img_ptr, x, y, 0xFF00FF);
			get_grid_coord(x, y, &pxl_x, &pxl_y);
			//my_pixel_put(&(game->minimap), pxl_x, pxl_y, 0xFFFFFF);
			x += step_x;
			y += step_y;
		}
		dist = my_dist(game->x, game->y, x, y);
		draw_col(game->img_ptr, col, dist, rgb[worldMap[(int)round(y)][(int)round(x)]]);
		rotate_vect(&dir_x, &dir_y, ANGLE_INC);
		//printf("%lf %lf\n", dir_x, dir_y);
	}
}

/*
void	raycast(t_game *game)
{
	double x;
	double	y;
	int i;

	x = game->x;
	y = game->y;
	//printf("%f\n",game->x + game->dir_x * 100);

	i = -1;
	while (++i < 100)
	{
		my_pixel_put(game->img_ptr, (int)x, (int)y, (int)sqrt(((x - game->x) * (x - game->x) + (y - game->y) * (y - game->y))) * 500 % 0xFFFFFF);
		x += game->dir_x;
		y += game->dir_y;
		//printf("%lf %lf\n", x ,y);
	}
}
*/

int		loop_handler(t_game *game)
{
	//pthread_t		threads[3];

	if (!game->frame_ready)
	{
		minimap(game);
		raycast(game);
		draw_fov(game);
		game->frame_ready = 1;
		//rotate_vect(&game->dir_x, &game->dir_y, 0.1);
	}
	refresh(game);
	return (0);
}

void	clean_all(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->img->mlx_img);
	mlx_destroy_image(game->mlx, game->img[1].mlx_img);
}

int		leave(t_game *game)
{
	clean_all(game);
	exit(0);
}

int		key_handler(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		leave(game);
	if (keycode == FORWARD_KEY)
	{
		game->x += SPEED * game->dir_x;
		game->y += SPEED * game->dir_y;
	}
	if (keycode == BACKWARD_KEY)
	{
		game->x -= SPEED * game->dir_x;
		game->y -= SPEED * game->dir_y;
	}
	if (keycode == RIGHT_KEY)
	{
		game->y += SPEED * game->dir_x;
		game->x -= SPEED * game->dir_y;	}
	if (keycode == LEFT_KEY)
	{
		game->y -= SPEED * game->dir_x;
		game->x += SPEED * game->dir_y;
	}
	if (keycode == ARROW_RIGHT_KEY)
		rotate_vect(&(game->dir_x), &(game->dir_y), TURN_ANGLE);
	if (keycode == ARROW_LEFT_KEY)
		rotate_vect(&(game->dir_x), &(game->dir_y), -TURN_ANGLE);
	return (0);
}

int		main(void)
{
	t_game	game;
	
	game = (t_game){0};
	game.x = mapWidth / 2;
	game.y = mapHeight / 2;
	init_display(&game);
	draw_grid(game.img, 0xFF);
	draw_grid(game.img + 1, 0xFF0000);
	game.dir_x = 1;
	game.dir_y = 0;
	mlx_do_key_autorepeaton(game.mlx);
	mlx_loop_hook(game.mlx, loop_handler, (void *)&game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, leave, &game);
	mlx_loop(game.mlx);
	return (0);
}