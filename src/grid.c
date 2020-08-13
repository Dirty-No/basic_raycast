/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:24:34 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/13 00:27:07 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

void	minimap(t_game *game)
{
	int		x;
	int		y;
	static int	rgb[6] = {0x0,0xFF0000,0xFF00,0xFF, 0xFFFF, 0xFF00FF};

	y = -1;
	
	while (++y < mapHeight)
	{
		x = -1;
		while (++x < mapWidth)
			fill_cell(game->minimap_ptr, x, y, rgb[worldMap[y][x]]);
	}
	//fill_cell(game->minimap_ptr, game->x, game->y, 0xFF0000);
}

void    get_grid_coord(double x, double y, double *x_grid, double *y_grid)
{
	*x_grid = x * CELL_SIZE + CELL_SIZE / 2;
	*y_grid = y * CELL_SIZE + CELL_SIZE / 2;
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

void    draw_fov(t_game *game)
{
	double	x;
	double	y;
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	int   	i;
	double	dir1[2];
	double	dir2[2];

	get_grid_coord(game->x, game->y, &x, &y);
	dir1[0] = game->dir_x;
	dir1[1] = game->dir_y;
	dir2[0] = game->dir_x;
	dir2[1] = game->dir_y;
	rotate_vect(dir1, dir1 + 1, -FOV / 2);
	rotate_vect(dir2, dir2 + 1, FOV / 2 );
	x1 = x;
	y1 = y;
	x2 = x;
	y2 = y;
	i = -1;
	while (++i < 100)
	{
		my_pixel_put(game->minimap_ptr, (int)x1, (int)y1, 0xFFFFFF);
		my_pixel_put(game->minimap_ptr, (int)x2, (int)y2, 0xFFFFFF);
		x1 += dir1[0];
		y1 += dir1[1];
		x2 += dir2[0];
		y2 += dir2[1];
	}
	
}