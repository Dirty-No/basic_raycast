/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:53:41 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/14 03:38:26 by smaccary         ###   ########.fr       */
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
  {1,0,0,0,0,0,2,2,0,2,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
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
** void	draw_col(t_data *data, int col, double dist, int wall_color)
** {
** 	int	start_y;
** 	int	end_y;
** 	int	wall_size;
** 	int	i;
** 
** 	if (dist == 0)
** 		dist = 0.000000001;
** 	wall_size = W_HEIGHT / dist;
** 	start_y = W_HEIGHT / 2 - wall_size / 2;
** 	end_y =  W_HEIGHT / 2 + wall_size / 2;
** 	i = -1;
** 	while (++i < W_HEIGHT)
** 	{
** 		if (0 <= i && i < start_y)
** 			my_pixel_put(data, col, i, ROOF_COLOR);
** 		else if (start_y <= i && i <= end_y)
** 			my_pixel_put(data, col, i, wall_color);
** 		else if (end_y < i && i < W_HEIGHT)
** 			my_pixel_put(data, col, i, FLOOR_COLOR);
** 	}
** }
*/

/*
int		get_text_color(int wall_size, int y, t_ray *ray, t_data *text)
{
	int	text_x;
	int	wall_x;
	int	side;
	int	hit_x;
	int	hit_y;

	hit_x = fmod(ray->x, 1.01);
	hit_y = fmod(ray->y, 1.01);
	if ((0 <= hit_y && hit_y <= 0.05) || (0.95 <= hit_y && hit_y <= 1))
	{
		wall_x	
	}
	
	wall_x = ray->x
}
*/


int		add_shade(int color, double shade)
{
	if (shade < 0 || shade >= 1)
		return 0;
	((unsigned char *)&color)[0] *= 1 - shade;
	((unsigned char *)&color)[1] *= 1 - shade;
	((unsigned char *)&color)[2] *= 1 - shade;
	return (color);
}

int		get_text_color(t_data *text, int wall_size, int y, t_ray *ray)
{
	unsigned int color;
	int	wall_x;
	
	(void)wall_size;
	wall_x = (int)(fmod((ray->side ? ray->y : ray->x) + 0.5, 1) * (double)text->width);
	y = y * text->height / wall_size;
	if (wall_x > text->width)
		printf("WIDTH  %d\n", wall_x);
	if (y > text->height)
		printf("HEIGHT  %d\n", y);
	color = *(unsigned int *)(text->addr + y * text->line_length + wall_x * (text->bits_per_pixel / 8));
	return (color);
}

void	draw_col(t_data *data, t_ray *ray, int col, t_data *text)
{
	int	start_y;
	int	end_y;
	int	wall_size;
	int	i;

	if (ray->dist == 0)
		ray->dist = 0.000000001;
	wall_size = W_HEIGHT / ray->dist;
	start_y = W_HEIGHT / 2 - wall_size / 2;
	end_y =  W_HEIGHT / 2 + wall_size / 2;
	i = -1;
	//printf("%lf\n", (double)wall_size / (double)W_HEIGHT);
	while (++i < W_HEIGHT)
	{
		if (0 <= i && i < start_y)
			my_pixel_put(data, col, i, add_shade(ROOF_COLOR, (double)(i * 2) /(double)W_HEIGHT));
		else if (start_y <= i && i <= end_y)
			my_pixel_put(data, col, i, get_text_color(text, end_y - start_y, i - start_y, ray));
		else if (end_y < i && i < W_HEIGHT)
			my_pixel_put(data, col, i, add_shade(FLOOR_COLOR, (double)((W_HEIGHT - i) * 2) /(double)W_HEIGHT));
	}
}

int	get_wall(double x, double y)
{
	return (worldMap[(int)round(y)][(int)round(x)]);
}

void	raycast(t_game *game)
{
	t_ray		ray;
	double		pxl_x;
	double		pxl_y;
	//static int	rgb[6] = {0x0,0xFF0000,0xFF00,0xFF, 0xFFFF, 0xFF00FF};
	int			col = -1;

	ray.dir_x = game->dir_x;
	ray.dir_y = game->dir_y;
	ray.origin_x = game->x;
	ray.origin_y = game->y;
	rotate_vect(&ray.dir_x, &ray.dir_y, -FOV / 2);
	while (++col < W_WIDTH)
	{
		ray.x = ray.origin_x;
		ray.y = ray.origin_y;
		while (!get_wall(ray.x, ray.y))
		{
			ray.step_x = ray.dir_x * RAY_STEP;
			ray.step_y = ray.dir_y * RAY_STEP;
			get_grid_coord(ray.x, ray.y, &pxl_x, &pxl_y);
			my_pixel_put(game->minimap_ptr, pxl_x, pxl_y, 0xFFFFFF);
			if (get_wall(ray.x + ray.step_x, ray.y + ray.step_y)
			|| get_wall(ray.x + ray.step_x, ray.y)
			|| get_wall(ray.x, ray.y + ray.step_y))
			{
				ray.step_x = ray.dir_x * RAYCAST_CLOSE_STEP;
				ray.step_y = ray.dir_y * RAYCAST_CLOSE_STEP;
			}
			ray.x += ray.step_x; 
			ray.y += ray.step_y; 
		}
		ray.side = !get_wall(ray.x - ray.step_x, ray.y);
		ray.dist = cos((double)ANGLE_INC * (double)(col - W_HEIGHT / 2)) * my_dist(game->x, game->y, ray.x, ray.y);
		draw_col(game->scene_ptr, &ray, col, game->minimap_ptr);
		rotate_vect(&ray.dir_x, &ray.dir_y, ANGLE_INC);
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
	game.x = 5;
	game.y = 5;
	init_display(&game);
	draw_grid(game.scene, 0xFF);
	draw_grid(game.scene + 1, 0xFF0000);
	game.dir_x = -1;
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
