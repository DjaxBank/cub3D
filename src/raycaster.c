/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:59:36 by dbank             #+#    #+#             */
/*   Updated: 2025/07/08 17:17:48 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#define MAX_RAYS 800
#define	FOV 60 * M_PI / 180.0
#define SCALE 500
#define SCREENSIZE 800

static t_ray cast_ray(t_data *game, t_ray ray)
{
	double x;
	double y;
	double xcalc;
	double ycalc;

	x = game->player.pos_x;
	y = game->player.pos_y;
	while (game->map[(int)y][(int)x] != '1')
	{
		y += sin(ray.angle) * 0.001;
		x += cos(ray.angle) * 0.001;
	}
	ray.hit_x = x;
	ray.hit_y = y;
	xcalc = x - game->player.pos_x;
	ycalc = y - game->player.pos_y;
	if (xcalc > ycalc)
		ray.side = VERTICAL;
	else
		ray.side = HORIZONTAL;
	ray.distance = sqrt(xcalc * xcalc + ycalc * ycalc);
	return (ray);
}

void	raycaster(t_data *game)
{
	static bool	run = false;
	size_t		count;
	t_ray		ray;
	int			height;
	
	count = 0;
	if (run == true)
		mlx_delete_image(game->mlx.mlx, game->mlx.wall);
	else
		run = true;
	game->mlx.wall = mlx_new_image(game->mlx.mlx, 800, 800);
	count = 0;
	while (count < MAX_RAYS)
	{
		ray.angle = game->player.orientation - (FOV / 2) + ((FOV / MAX_RAYS) * count);
		ray = cast_ray(game, ray);
		ray.distance *= cos(ray.angle - game->player.orientation);
		if (ray.distance < 0.0001)
   			ray.distance = 0.0001;
		height = SCALE / (ray.distance + 0.0001);
		if (height < 1)
   			height = 1;
		if (height > 800)
			height = 800;
		put_wall(game, ray, count, 400 - (height / 2), height);	
		count++;
	}
	mlx_image_to_window(game->mlx.mlx, game->mlx.wall, 0, 0);
}
