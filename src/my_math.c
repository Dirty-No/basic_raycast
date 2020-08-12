/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 01:10:56 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/12 01:10:56 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <time.h>

int	get_random_int()
{
	srand(clock());
	return ((rand() ^ (rand() << 15) ^ ((long long int) rand() << 30)));
}

/*
** YOU SHOULD ALWAYS SWITCH BETWEEN TWO IMAGE BUFFERS TO PREVENT TEARING
** (DOUBLE BUFFERING) 
*/


void	rotate_vect(double *x, double *y, double angle)
{
	double old_x;
	double old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
	//printf("ox %lf oy %lf x %lf y %lf\n", old_x, old_y, *x, *y);
}

double	my_square(double x)
{
	return (x * x);
}

double	my_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(my_square(x2 - x1) + my_square(y2 - y1)));
}