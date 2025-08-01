/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:59:36 by dbank             #+#    #+#             */
/*   Updated: 2025/08/01 16:06:29 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	step_ray(t_ray *ray)
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
}

static void	trace_ray(t_data *game, t_ray *ray)
{
	size_t	count;
	bool	open_door_hit;

	count = 0;
	open_door_hit = false;
	while (game->map[ray->y][ray->x] != '1' && game->map[ray->y][ray->x] != 'D')
	{
		if (game->map[ray->y][ray->x] == 'd' && count > 0 && !open_door_hit)
		{
			render_door(game, *ray);
			open_door_hit = true;
		}
		step_ray(ray);
		count++;
	}
	ray->hit_door = (game->map[ray->y][ray->x] == 'D');
	if (ray->side == VERTICAL)
		ray->distance = (ray->x - game->player.pos_x + (1 - ray->stepx) / 2)
			/ ray->raydir_x;
	else
		ray->distance = (ray->y - game->player.pos_y + (1 - ray->stepy) / 2)
			/ ray->raydir_y;
	ray->hit_y = game->player.pos_y + ray->raydir_y * ray->distance;
	ray->hit_x = game->player.pos_x + ray->raydir_x * ray->distance;
}

static t_ray	cast_ray(t_data *game, t_ray ray)
{
	ray.y = game->player.pos_y;
	ray.x = game->player.pos_x;
	init_ray(game, &ray);
	trace_ray(game, &ray);
	return (ray);
}

static void	render_wall_slices(t_data *game)
{
	size_t	count;
	t_ray	ray;
	int		height;
	t_wall	wall;

	init_wall_vars(&count, &ray);
	while (count < (size_t)game->mlx.mlx->width)
	{
		ray.angle = game->player.orientation - (game->fov / 2) + ((game->fov
					/ game->mlx.mlx->width) * count);
		ray = cast_ray(game, ray);
		ray.distance *= cos(ray.angle - game->player.orientation);
		if (ray.distance < 0.0001)
			ray.distance = 0.0001;
		height = (((game->mlx.mlx->width + game->mlx.mlx->height) / 2) / 3)
			/ (ray.distance + 0.0001);
		if (height < 1)
			height = 1;
		wall.x = count++;
		wall.y = game->mlx.mlx->height / 2 - (height / 2);
		wall.size = height;
		wall.tex = choose_image(game, ray);
		wall.content = game->map[ray.y][ray.x];
		put_wall(game, ray, wall, game->mlx.wall);
	}
}

void	raycaster(t_data *game, bool force_recreate)
{
	if (!is_window_size_valid(game->mlx.mlx->width, game->mlx.mlx->height))
		return ;
	if (force_recreate)
	{
		mlx_resize_image(game->mlx.wall, game->mlx.mlx->width,
			game->mlx.mlx->height);
		mlx_resize_image(game->mlx.open_doors, game->mlx.mlx->width,
			game->mlx.mlx->height);
		if (!game->mlx.wall || ! game->mlx.open_doors)
			werror("Failed to resize image", game);
		mlx_set_instance_depth(game->mlx.wall->instances, 1);
	}
	if (!game->mlx.wall)
		return ;
	fill_image(game->mlx.open_doors, 0x00000000, game->mlx.mlx->width,
		game->mlx.mlx->height);
	fill_image(game->mlx.wall, 0x00000000, game->mlx.mlx->width,
		game->mlx.mlx->height);
	render_wall_slices(game);
}
