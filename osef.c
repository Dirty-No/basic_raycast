void	raycast(t_game *game)
{
    t_ray   
	double		pxl_x;
	double		pxl_y;
	static int	rgb[6] = {0x0,0xFF0000,0xFF00,0xFF, 0xFFFF, 0xFF00FF};
	int			col = -1;

	ray = game->dir_x;
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