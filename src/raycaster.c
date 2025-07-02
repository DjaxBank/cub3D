/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:59:36 by dbank             #+#    #+#             */
/*   Updated: 2025/07/02 23:53:44 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#define MAX_RAYS 800
#define	FOV 60 * M_PI / 180.0
#define SCALE 500
#define SCREENSIZE 800

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
		y += sin(angle);
		x += cos(angle);
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
	int		height;
	
	count = 0;
	if (run == true)
	{
		while (count < MAX_RAYS)
		{
			mlx_delete_image(game->mlx.mlx, game->mlx.wall[count]);
			count++;
		}
	}
	else
		run = true;
	count = 0;
	while (count < MAX_RAYS)
	{
		ray = game->player.orientation - (FOV / 2) + ((FOV / MAX_RAYS) * count);
		distance = cast_ray(game, ray);
		distance *= cos(ray - game->player.orientation);
		height = SCALE / (distance + 0.0001);
		game->mlx.wall[count] = mlx_new_image(game->mlx.mlx, 1, height);
		fill_image(game->mlx.wall[count], (uint32_t){130 << 24 | 186 << 16 | 3 << 8 | 255}, 1, height);
		mlx_image_to_window(game->mlx.mlx, game->mlx.wall[count], count, 300 - (height / 2));
		count++;
	}
}
