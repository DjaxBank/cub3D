/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:16:31 by dbank             #+#    #+#             */
/*   Updated: 2025/07/16 15:05:31 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static t_ray cast_ray(t_data *game)
{
	t_ray	ray;

	ray.angle = game->player.orientation - (FOV / 2) + ((FOV / game->mlx.mlx->width) * game->mlx.mlx->width);
	ray.y = game->player.pos_y;
	ray.x = game->player.pos_x;
	init_ray(game, &ray);
	if (ray.sidedistX < ray.sidedistY)
	{
		ray.x += ray.stepX;
		ray.sidedistX += ray.deltaX;
		ray.side = VERTICAL;
	}
	else
	{
		ray.y += ray.stepY;
		ray.sidedistY += ray.deltaY;
		ray.side = HORIZONTAL;
	}
	if (ray.side == VERTICAL)
		ray.distance = (ray.x - game->player.pos_x + (1 - ray.stepX) / 2) / ray.raydir_X;
	else
		ray.distance = (ray.y - game->player.pos_y + (1 - ray.stepY) / 2) / ray.raydir_Y;
	ray.hit_y = game->player.pos_y + ray.raydir_Y * ray.distance;
	ray.hit_x = game->player.pos_x + ray.raydir_X * ray.distance;
	return (ray);
}

void open_door(t_data *game)
{
	const t_ray	ray = cast_ray(game);

	if (game->map[ray.y][ray.x] == 'D')
	{
		game->map[ray.y][ray.x] = '0';
		raycaster(game, false);
		draw_minimap(game, false);
	}
}
