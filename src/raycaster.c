/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:59:36 by dbank             #+#    #+#             */
/*   Updated: 2025/07/17 13:23:18 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static mlx_texture_t	*choose_image(t_data *game, t_ray ray)
{
	if (ray.hit_door)
		return (game->mlx.door);
	if (ray.side == HORIZONTAL)
	{
		if (game->player.pos_y > ray.hit_y)
			return (game->mlx.tex[N]);
		else
			return (game->mlx.tex[S]);
	}
	else if (ray.side == VERTICAL)
	{
		if (game->player.pos_x > ray.hit_x)
			return (game->mlx.tex[E]);
		else
			return (game->mlx.tex[W]);
	}
	else
		return (game->mlx.door);
}

static void	trace_ray(t_data *game, t_ray *ray)
{
	while (game->map[ray->y][ray->x] != '1' && game->map[ray->y][ray->x] != 'D')
	{
		if (ray->sidedistX < ray->sidedistY)
		{
			ray->x += ray->stepX;
			ray->sidedistX += ray->deltaX;
			ray->side = VERTICAL;
		}
		else
		{
			ray->y += ray->stepY;
			ray->sidedistY += ray->deltaY;
			ray->side = HORIZONTAL;
		}
	}
	ray->hit_door = (game->map[ray->y][ray->x] == 'D');
	if (ray->side == VERTICAL)
		ray->distance = (ray->x - game->player.pos_x + (1 - ray->stepX) / 2)
			/ ray->raydir_X;
	else
		ray->distance = (ray->y - game->player.pos_y + (1 - ray->stepY) / 2)
			/ ray->raydir_Y;
	ray->hit_y = game->player.pos_y + ray->raydir_Y * ray->distance;
	ray->hit_x = game->player.pos_x + ray->raydir_X * ray->distance;
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

	count = 0;
	while (count < (size_t)game->mlx.mlx->width)
	{
		ray.angle = game->player.orientation - (FOV / 2) + ((FOV
					/ game->mlx.mlx->width) * count);
		ray = cast_ray(game, ray);
		ray.distance *= cos(ray.angle - game->player.orientation);
		if (ray.distance < 0.0001)
			ray.distance = 0.0001;
		height = (((game->mlx.mlx->width + game->mlx.mlx->height) / 2) / 3)
			/ (ray.distance + 0.0001);
		if (height < 1)
			height = 1;
		wall.x = count;
		wall.y = game->mlx.mlx->height / 2 - (height / 2);
		wall.size = height;
		wall.tex = choose_image(game, ray);
		put_wall(game, ray, wall);
		count++;
	}
}

void	raycaster(t_data *game, bool force_recreate)
{
	if (!is_window_size_valid(game->mlx.mlx->width, game->mlx.mlx->height))
		return ;
	if (force_recreate || !game->mlx.wall)
	{
		if (game->mlx.wall)
			mlx_delete_image(game->mlx.mlx, game->mlx.wall);
		game->mlx.wall = mlx_new_image(game->mlx.mlx, game->mlx.mlx->width,
				game->mlx.mlx->height);
		if (!game->mlx.wall)
			werror("Failed to create wall image", game);
		if (mlx_image_to_window(game->mlx.mlx, game->mlx.wall, 0, 0) == -1)
			werror("Failed to add wall image to window", game);
		mlx_set_instance_depth(game->mlx.wall->instances, 1);
	}
	if (!game->mlx.wall)
		return ;
	fill_image(game->mlx.wall, 0x00000000, game->mlx.mlx->width,
		game->mlx.mlx->height);
	render_wall_slices(game);
}
