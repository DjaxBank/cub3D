/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_door.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:39:15 by showard           #+#    #+#             */
/*   Updated: 2025/08/01 15:49:17 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static void	create_new_door(t_data *game)
{
	if (!game->mlx.open_doors)
	{
		game->mlx.open_doors = mlx_new_image(game->mlx.mlx,
				game->mlx.mlx->width, game->mlx.mlx->height);
		mlx_image_to_window(game->mlx.mlx, game->mlx.open_doors, 0, 0);
		mlx_set_instance_depth(game->mlx.open_doors->instances, 3);
	}
}

void	render_door(t_data *game, t_ray ray)
{
	t_wall	wall;
	int		height;

	if (ray.side == VERTICAL)
		ray.distance = (ray.x - game->player.pos_x + (1 - ray.stepx) / 2)
			/ ray.raydir_x;
	else
		ray.distance = (ray.y - game->player.pos_y + (1 - ray.stepy) / 2)
			/ ray.raydir_y;
	ray.hit_y = game->player.pos_y + ray.raydir_y * ray.distance;
	ray.hit_x = game->player.pos_x + ray.raydir_x * ray.distance;
	create_new_door(game);
	ray.distance *= cos(ray.angle - game->player.orientation);
	if (ray.distance < 0.0001)
		ray.distance = 0.0001;
	height = (((game->mlx.mlx->width + game->mlx.mlx->height) / 2) / 3)
		/ (ray.distance + 0.0001);
	if (height < 1)
		height = 1;
	wall.x = *ray.count;
	wall.y = game->mlx.mlx->height / 2 - (height / 2);
	wall.size = height;
	wall.tex = game->mlx.door;
	wall.content = game->map[ray.y][ray.x];
	put_wall(game, ray, wall, game->mlx.open_doors);
}

void	init_wall_vars(size_t *count, t_ray *ray)
{
	*count = 0;
	ft_bzero(ray, sizeof(t_ray));
	ray->count = count;
}
