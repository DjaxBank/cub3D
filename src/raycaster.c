/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:59:36 by dbank             #+#    #+#             */
/*   Updated: 2025/07/11 14:23:30 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#define	FOV 60 * M_PI / 180.0

static void init_ray(t_data *game, t_ray *ray)
{
	ray->raydir_X = cos(ray->angle);
	ray->raydir_Y = sin(ray->angle);
	ray->deltaX = fabs(1 / ray->raydir_X);
	ray->deltaY = fabs( 1 / ray->raydir_Y);
	if (ray->raydir_X < 0)
	{
		ray->stepX = -1;
		ray->sidedistX = (game->player.pos_x - (int)game->player.pos_x) * ray->deltaX;
	}
	else
	{
		ray->stepX = 1;
		ray->sidedistX = ((int)game->player.pos_x + 1 - game->player.pos_x) * ray->deltaX;
	}
	if (ray->raydir_Y < 0)
	{
		ray->stepY = -1;
		ray->sidedistY = (game->player.pos_y - (int)game->player.pos_y) * ray->deltaY;	
	}
	else
	{
		ray->stepY = 1;
		ray->sidedistY = ((int)game->player.pos_y + 1 - game->player.pos_y) * ray->deltaY;	
	}
}

static t_ray cast_ray(t_data *game, t_ray ray)
{
	int x;
	int y;

	y = game->player.pos_y;
	x = game->player.pos_x;
	init_ray(game, &ray);
	while (game->map[y][x] != '1')
	{
		if (ray.sidedistX < ray.sidedistY)
		{
			x += ray.stepX;
			ray.sidedistX += ray.deltaX;
			ray.side = VERTICAL;
		}
		else
		{
			y += ray.stepY;
			ray.sidedistY += ray.deltaY;
			ray.side = HORIZONTAL;
		}
	}
	if (ray.side == VERTICAL)
		ray.distance = (x - game->player.pos_x + (1 - ray.stepX) / 2) / ray.raydir_X;
	else
		ray.distance = (y - game->player.pos_y + (1 - ray.stepY) / 2) / ray.raydir_Y;
	ray.hit_y = game->player.pos_y + ray.raydir_Y * ray.distance;
	ray.hit_x = game->player.pos_x + ray.raydir_X * ray.distance;
	return (ray);
}

void	raycaster(t_data *game)
{
	static bool	run = false;
	size_t		count;
	t_ray		ray;
	int			height;
	size_t		max_rays;
	
	max_rays = game->mlx.mlx->width;
	count = 0;
	if (run == true)
		mlx_delete_image(game->mlx.mlx, game->mlx.wall);
	else
		run = true;
	game->mlx.wall = mlx_new_image(game->mlx.mlx, game->mlx.mlx->width, game->mlx.mlx->height);
	count = 0;
	while (count < max_rays)
	{
		ray.angle = game->player.orientation - (FOV / 2) + ((FOV / max_rays) * count);
		ray = cast_ray(game, ray);
		ray.distance *= cos(ray.angle - game->player.orientation);
		if (ray.distance < 0.0001)
   			ray.distance = 0.0001;
		height = (((game->mlx.mlx->width + game->mlx.mlx->height) / 2) / 3) / (ray.distance + 0.0001);
		if (height < 1)
   			height = 1;
		if (height > game->mlx.mlx->height)
			height = game->mlx.mlx->height;
		put_wall(game, ray, count, game->mlx.mlx->height / 2  - (height / 2), height);	
		count++;
	}
	mlx_image_to_window(game->mlx.mlx, game->mlx.wall, 0, 0);
}
