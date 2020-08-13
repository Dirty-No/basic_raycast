/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:06:44 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/13 22:41:26 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "keys.h"

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
	t_data      scene[2];
	t_data  	*scene_ptr;
	t_data		minimap[2];
    t_data      *minimap_ptr;
	t_key		keys[K_BUFF_SIZE];
	int			frame_ready;
}				t_game;

typedef struct s_ray
{
    double		x;
	double		y;
	double			origin_x;
	double			origin_y;
	double		dir_x;
	double 		dir_y;
	double		step_x;
	double		step_y;
	double 		dist;
    int         side;
}               t_ray;


#endif