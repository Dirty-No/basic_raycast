/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:55:40 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/10 17:59:04 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/*
** MLX HEADER
*/

# include "mlx.h"

/*
** X EVENTS ARE REWRITTEN ACCORDINGLY TO 42'S NORM IN THIS FILE
*/

# include "x_events.h"

/*
** IMPORTANT KEYBOARD KEYCODES FOR LINUX, OSX AND WINDOWS (MINGW)
** ARE REWRITTEN IN THIS FILE
*/

# include "keycodes.h"

# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define W_WIDTH	800
# define W_HEIGHT	800
# define W_TITLE	"window title"

# define PI 3.14159265

# define RADIANS(x) x * PI / 180

# define FOV RADIANS(90)

# define ANGLE_INC FOV/W_WIDTH

# define SPEED 0.1
# define TURN_ANGLE 0.05

# define RAY_STEP 0.01

# define ROOF_COLOR 0xAAAAAA
# define FLOOR_COLOR 0xBBFFAA

/*
** MAX FRAMES PER SECOND 
*/

# define FRAME_CAP	0

# define CELL_SIZE 12

/*
** STRUCT STORING ALL INFORMATION REQUIRED TO USE A MLX IMAGE 
*/

typedef struct	s_data
{
	void		*mlx_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_data;

/*
** MLX HOOKS ONLY TAKE ONE ARGUMENT SO YOU SHOULD STORE EVERYTHING YOU NEED
** IN A STRUCT 
*/

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	int			dist;
	t_data  	img[2];
	t_data  	*img_ptr;
	t_data		minimap;
	int			frame_ready;
}				t_game;

void    draw_fov(t_game *game);
void	draw_grid(t_data *data, int color);
void	fill_cell(t_data *data, int x, int y, int color);
void	minimap(t_game *game);
void    get_grid_coord(double x, double y, double *x_grid, double *y_grid);


void    init_data(t_data *data, void *mlx, int w, int h);
void	init_display(t_game *game);

void    my_pixel_put(t_data *data, int x, int y, int color);
void	copy_image(t_data *src, t_data *dst);
void	*refresh(t_game *game);

int		get_random_int(void);
void	rotate_vect(double *x, double *y, double angle);
double	my_square(double x);
double	my_dist(double x1, double y1, double x2, double y2);


#define mapWidth 24
#define mapHeight 24

int worldMap[mapHeight][mapWidth];

#endif