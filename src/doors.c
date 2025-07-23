/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doors.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/16 14:16:31 by dbank         #+#    #+#                 */
/*   Updated: 2025/07/23 13:34:51 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static t_ray	init_door_ray(t_data *game)
{
	t_ray	ray;

	ray.angle = game->player.orientation - (FOV / 2) + ((FOV
				/ game->mlx.mlx->width) * game->mlx.mlx->width);
	ray.x = game->player.pos_x;
	ray.y = game->player.pos_y;
	init_ray(game, &ray);
	return (ray);
}

static void	step_door_ray(t_data *game, t_ray *ray)
{
	if (ray->sidedistx < ray->sidedisty)
	{
		ray->x += ray->stepx;
		ray->sidedistx += ray->deltax;
		ray->side = VERTICAL;
	}
	else
	{
		ray->y += ray->stepy;
		ray->sidedisty += ray->deltay;
		ray->side = HORIZONTAL;
	}
	if (ray->side == VERTICAL)
		ray->distance = (ray->x - game->player.pos_x + (1 - ray->stepx) / 2)
			/ ray->raydir_x;
	else
		ray->distance = (ray->y - game->player.pos_y + (1 - ray->stepy) / 2)
			/ ray->raydir_y;
	ray->hit_x = game->player.pos_x + ray->raydir_x * ray->distance;
	ray->hit_y = game->player.pos_y + ray->raydir_y * ray->distance;
}

static t_ray	cast_ray(t_data *game)
{
	t_ray	ray;

	ray = init_door_ray(game);
	step_door_ray(game, &ray);
	return (ray);
}

void	open_door(struct mlx_key_data key, void *game)
{
	t_ray	ray;

	(void)key;
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_LEFT_CONTROL))
	{
		((t_data *)game)->toggle = !((t_data *)game)->toggle;
		return ;
	}
	if (!mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_ENTER))
		return ;
	ray = cast_ray(game);
	if (((t_data *)game)->map[ray.y][ray.x] == 'D'
		|| ((t_data *)game)->map[ray.y][ray.x] == 'd')
	{
		if (((t_data *)game)->map[ray.y][ray.x] == 'D')
			((t_data *)game)->map[ray.y][ray.x] = 'd';
		else
			((t_data *)game)->map[ray.y][ray.x] = 'D';
		raycaster(game, false);
		draw_minimap(game, false);
	}
}
