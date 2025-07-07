/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:59:36 by dbank             #+#    #+#             */
/*   Updated: 2025/07/07 14:38:01 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#define MAX_RAYS 800
#define	FOV 60 * M_PI / 180.0
#define SCALE 500
#define SCREENSIZE 800

static void put_line(mlx_image_t *window, uint32_t colour, int x, int y, int size)
{
	while (size > 0)
	{
		mlx_put_pixel(window, x, y, colour);
		y++;
		size--;
	}	
}

static double cast_ray(t_data *game, double angle)
{
	double x;
	double y;
	double xcalc;
	double ycalc;

	x = game->player.pos_x;
	y = game->player.pos_y;
	while (game->map[(int)y][(int)x] != '1')
	{
		y += sin(angle) * 0.001;
		x += cos(angle) * 0.001;
	}
	xcalc = x - game->player.pos_x;
	ycalc = y - game->player.pos_y;
	return (sqrt(xcalc * xcalc + ycalc * ycalc));
}

void	raycaster(t_data *game)
{
	static bool	run = false;
	size_t	count;
	double	ray;
	double 	distance;
	int	height;
	
	count = 0;
	if (run == true)
		mlx_delete_image(game->mlx.mlx, game->mlx.wall);
	else
		run = true;
	game->mlx.wall = mlx_new_image(game->mlx.mlx, 800, 800);
	count = 0;
	while (count < MAX_RAYS)
	{
		ray = game->player.orientation - (FOV / 2) + ((FOV / MAX_RAYS) * count);
		distance = cast_ray(game, ray);
		distance *= cos(ray - game->player.orientation);
		if (distance < 0.0001)
   			distance = 0.0001;
		height = SCALE / (distance + 0.0001);
		if (height < 1)
   			height = 1;
		if (height > 800)
			height = 800;
		put_line(game->mlx.wall, (uint32_t){60 << 24 | 40 << 16 | 20 << 8 | 255}, count, 400 - (height / 2), height);
		count++;
	}
	mlx_image_to_window(game->mlx.mlx, game->mlx.wall, 0, 0);
}
