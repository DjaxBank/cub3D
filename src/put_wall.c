/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:29:04 by dbank             #+#    #+#             */
/*   Updated: 2025/07/21 14:57:11 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_wall(t_data *game, t_ray ray, t_wall *wall, mlx_image_t *image)
{
	double	hit_pos;

	wall->wall = image;
	wall->max_y = game->mlx.mlx->height;
	if (ray.side == VERTICAL)
		hit_pos = fmod(ray.hit_y, 1.0);
	else
		hit_pos = fmod(ray.hit_x, 1.0);
	if (hit_pos < 0)
		hit_pos += 1.0;
	wall->texture_x = (size_t)(hit_pos * wall->tex->width);
	wall->step = (double)wall->tex->height / (double)wall->size;
	wall->tex_pos = 0.0;
	if (wall->y < 0)
	{
		wall->tex_pos += -wall->y * wall->step;
		wall->size += wall->y;
		wall->y = 0;
	}
	if (wall->texture_x >= wall->tex->width)
		wall->texture_x = wall->tex->width - 1;
}

static void	wall_loop(t_wall *wall)
{
	uint8_t		colour[3];
	size_t		texture_y;
	int			calc;
	const int	transparancy = 255 - ((wall->content == 'd') * 150);

	while (wall->size > 0 && wall->y < wall->max_y)
	{
		texture_y = (size_t)wall->tex_pos;
		wall->tex_pos += wall->step;
		if (texture_y >= wall->tex->height)
			texture_y = wall->tex->height - 1;
		calc = (texture_y * wall->tex->width + wall->texture_x)
			* wall->tex->bytes_per_pixel;
		colour[0] = wall->tex->pixels[calc];
		colour[1] = wall->tex->pixels[++calc];
		colour[2] = wall->tex->pixels[++calc];
		mlx_put_pixel(wall->wall, wall->x, wall->y++,
			(uint32_t)
		{
			colour[0] << 24
			| colour[1] << 16
			| colour[2] << 8 | transparancy
		});
		wall->size--;
	}
}

void	put_wall(t_data *game, t_ray ray, t_wall wall, mlx_image_t *image)
{
	init_wall(game, ray, &wall, image);
	wall_loop(&wall);
}
