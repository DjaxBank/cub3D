/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:29:04 by dbank             #+#    #+#             */
/*   Updated: 2025/07/08 16:57:19 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void sample_wall(mlx_image_t *wall, mlx_texture_t *to_render, int x, int y, size_t size, size_t texture_x)
{
	const size_t	height = size;
	const double	step = (double)to_render->height / (double)height;
	const uint32_t	*pixels = (uint32_t *)to_render->pixels;
	uint32_t		colour;
	size_t			texture_y;
	double			tex_pos;
	
	tex_pos = 0;
	if (texture_x >= to_render->width)
		texture_x = to_render->width - 1;
	while (size > 0)
	{
		texture_y = ((size_t)tex_pos);
		tex_pos += step;
		if (texture_y >= to_render->height)
			texture_y = to_render->height - 1;
		colour = pixels[texture_y * to_render->width + texture_x];
		mlx_put_pixel(wall, x, y, colour);
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
	sample_wall(game->mlx.wall, to_render, x, y, size, hit_pos * to_render->width);
}
