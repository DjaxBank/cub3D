/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:29:04 by dbank             #+#    #+#             */
/*   Updated: 2025/07/11 16:01:18 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void sample_wall(t_data *game, mlx_image_t *wall, mlx_texture_t *to_render, int x, int y, int size, size_t texture_x)
{
	const size_t	height = size;
	const double	step = (double)to_render->height / (double)height;
	uint8_t			colour[3];
	size_t			texture_y;
	double			tex_pos;
	
	tex_pos = 0;
	if (y < 0)
	{
		tex_pos += -y * step;
		size += y;
		y = 0;
	}
	if (texture_x >= to_render->width)
		texture_x = to_render->width - 1;
	while (size > 0 && y < game->mlx.mlx->height)
	{
		texture_y = ((size_t)tex_pos);
		tex_pos += step;
		if (texture_y >= to_render->height)
			texture_y = to_render->height - 1;
		colour[0] = to_render->pixels[(texture_y * to_render->width + texture_x) * to_render->bytes_per_pixel];
		colour[1] = to_render->pixels[((texture_y * to_render->width + texture_x) * to_render->bytes_per_pixel) + 1];
		colour[2] = to_render->pixels[((texture_y * to_render->width + texture_x) * to_render->bytes_per_pixel) + 2];
		mlx_put_pixel(wall, x, y, (uint32_t){colour[0] << 24 | colour[1] << 16 | colour[2] << 8 | 255});
		y++;
		size--;
	}
}

void	put_wall(t_data *game, t_ray ray, int x , int y , size_t size)
{
	mlx_texture_t	*to_render;
	double			hit_pos;

	to_render = game->mlx.tex[N];
	if (ray.side == VERTICAL)
		hit_pos = fmod(ray.hit_y, 1);
	else
		hit_pos = fmod(ray.hit_x, 1);
	if (hit_pos < 0)
		hit_pos += 1;
	sample_wall(game, game->mlx.wall, to_render, x, y, size, hit_pos * to_render->width);
}
