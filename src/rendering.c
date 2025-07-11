/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/07/11 14:35:53 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

void fill_image(mlx_image_t *image, uint32_t colour, size_t width, size_t height)
{
	size_t					x;
	size_t					y;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(image, x, y, colour);
			x++;
		}
		y++; 
	}
}

void render_background(const int ceilingc[3], const int floorc[3], t_mlx *mlx)
{
	const	uint32_t		converted_ceiling = ceilingc[0] << 24 | ceilingc[1] << 16 | ceilingc[2] << 8 | 255;
	const	uint32_t		converted_floor = floorc[0] << 24 | floorc[1] << 16 | floorc[2] << 8 | 255;

	if (mlx->ceiling)
		mlx_resize_image(mlx->ceiling, mlx->mlx->width, mlx->mlx->height);
	else
		mlx->ceiling = mlx_new_image(mlx->mlx, mlx->mlx->width, mlx->mlx->height / 2);
	fill_image(mlx->ceiling, converted_ceiling, mlx->mlx->width, mlx->mlx->height / 2);
	if (mlx->floor)
		mlx_resize_image(mlx->floor, mlx->mlx->width, mlx->mlx->height);
	else
		mlx->floor = mlx_new_image(mlx->mlx, mlx->mlx->width, mlx->mlx->height / 2);
	fill_image(mlx->floor, converted_floor,  mlx->mlx->width, mlx->mlx->height / 2);
	mlx_image_to_window(mlx->mlx, mlx->ceiling, 0, 0);
	mlx_image_to_window(mlx->mlx, mlx->floor, 0, mlx->mlx->height / 2);
}
