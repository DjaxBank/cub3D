/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:17:46 by showard           #+#    #+#             */
/*   Updated: 2025/07/21 17:06:44 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	calc_ray(t_ray *ray)
{
	ray->raydir_x = cos(ray->angle);
	ray->raydir_y = sin(ray->angle);
	ray->deltax = fabs(1 / ray->raydir_x);
	ray->deltay = fabs(1 / ray->raydir_y);
}

void	calc_sidedistx(t_data *game, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (game->player.pos_x - (int)game->player.pos_x)
			* ray->deltax;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = ((int)game->player.pos_x + 1 - game->player.pos_x)
			* ray->deltax;
	}
}

void	calc_sidedisty(t_data *game, t_ray *ray)
{
	if (ray->raydir_y < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (game->player.pos_y - (int)game->player.pos_y)
			* ray->deltay;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = ((int)game->player.pos_y + 1 - game->player.pos_y)
			* ray->deltay;
	}
}

void	init_ray(t_data *game, t_ray *ray)
{
	calc_ray(ray);
	calc_sidedistx(game, ray);
	calc_sidedisty(game, ray);
}

mlx_texture_t	*choose_image(t_data *game, t_ray ray)
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
		{
			if ((int)mlx_get_time() % 2 == 0)
				return (game->mlx.tex[W]);
			else
				return (game->mlx.tex2[W]);
		}
	}
	else
		return (game->mlx.door);
}
