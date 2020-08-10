/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:53:41 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/10 18:45:12 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define FOV 60
#define ANGLE_INC FOV/W_WIDTH

int worldMap[mapHeight][mapWidth]=
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

/*
** FUNCTION TO TEST IF EVERYTHING IS WORKING WELL 
*/

void	draw_grid(t_data *data, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		y = -1;
		while (++y < data->height)
			my_pixel_put(data, x, y, color);
		x += CELL_SIZE;
	}
	y = 0;
	while (y < data->height)
	{
		x = -1;
		while (++x < data->width)
			my_pixel_put(data, x, y, color);
		y += CELL_SIZE;
	}	
}

void	fill_cell(t_data *data, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	
	x *= CELL_SIZE;
	y *= CELL_SIZE;
	start_x = x;
	start_y = y;
	while (y < start_y + CELL_SIZE)
	{
		while (x < start_x + CELL_SIZE)
		{
			my_pixel_put(data, x, y, color);
			x++;
		}
		y++;
		x = start_x;
	}
}

void	copy_image(t_data *src, t_data *dst)
{
	int	i;

	i = -1;
	while (++i < (dst->width * dst->height * dst->bits_per_pixel / 8)
			&& i < (src->width * src->height * src->bits_per_pixel / 8))
		(dst->addr)[i] = (char)(src->addr)[i];
}

int	get_random_int()
{
	srand(clock());
	return ((rand() ^ (rand() << 15) ^ ((long long int) rand() << 30)));
}

/*
** YOU SHOULD ALWAYS SWITCH BETWEEN TWO IMAGE BUFFERS TO PREVENT TEARING
** (DOUBLE BUFFERING) 
*/


void	minimap(t_game *game)
{
	int		x;
	int		y;
	static int		rgb[5] = {0xFFFFFF,0xFF0000,0xFF00,0xFF, 0xFFFF};

	y = -1;
	while (++y < mapHeight)
	{
		x = -1;
		while (++x < mapWidth)
			fill_cell(game->img_ptr, x, y, rgb[worldMap[x][y]]);
	}
}

void	rotate_vect(double *x, double *y, double angle)
{
	double old_x;
	double old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
	printf("ox %lf oy %lf x %lf y %lf\n", old_x, old_y, *x, *y);
}

/*
** void	raycast(t_game *game)
** {
** 	double		x;
** 	double		y;
** 	double		dir_x;
** 	double 	dir_y;
** 	double		step_x;
** 	double		step_y;
** 	//int 	dist;
** 	//static int		rgb[5] = {0xFFFFFF,0xFF0000,0xFF00,0xFF, 0xFFFF};
** 	int		col = -1;
** 
** 	dir_x = game->dir_x;
** 	dir_y = game->dir_x;
** 	x = game->x;
** 	y = game->y;
** 	while (++col < W_WIDTH)
** 	{
** 		step_x = (dir_x >= 0) ? 0.01 : -0.1;
** 		step_y = (dir_y >= 0) ? 0.01 : -0.1;
** 		fill_cell(game->img_ptr, x, y, 0xFF00FF);
** 		if (worldMap[(int)x][(int)y])
** 		{
** 			return ;
** 		}
** 		x += step_x;
** 		y += step_y;
** 		rotate_vect(&dir_x, &dir_y, ANGLE_INC);
** 	}
** 
** }
*/

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
		my_pixel_put(game->img_ptr, (int)x, (int)y, 0xFFFFFF);
		x += game->dir_x;
		y += game->dir_y;
		//printf("%lf %lf\n", x ,y);
	}
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
		game->img_ptr = game->img + i++ % 2;
		t0 = clock();
		game->frame_ready = 0;
	}
	return (NULL);
}

int		loop_handler(t_game *game)
{
	//pthread_t		threads[3];

	if (!game->frame_ready)
	{
		//minimap(game);
		raycast(game);
		game->frame_ready = 1;
		rotate_vect(&game->dir_x, &game->dir_y, 1);
	}
	refresh(game);
	return (0);
}

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
	game->frame_ready = 0;
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
	return (0);
}

int		main(void)
{
	t_game	game;
	
	game = (t_game){0};
	game.x = W_WIDTH / 2;
	game.y = W_HEIGHT / 2;
	init_display(&game);
	draw_grid(game.img, 0xFF);
	draw_grid(game.img + 1, 0xFF0000);
	game.dir_x = -1;
	game.dir_y = 0;
	mlx_loop_hook(game.mlx, loop_handler, (void *)&game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, leave, &game);
	mlx_loop(game.mlx);
	return (0);
}