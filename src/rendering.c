/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/06/30 14:26:37 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"


void	loop_hook(void *param)
{
	(void)param;
}

void	key_hook(struct mlx_key_data key, void *param)
{

}

void render_background(const int ceilingc[3], const int floorc[3], s_mlx *mlx)
{
	const	uint32_t		converted_ceiling = ceilingc[0] << 24 | ceilingc[1] << 16 | ceilingc[2] << 8 | 255;
	const	uint32_t		converted_floor = floorc[0] << 24 | floorc[1] << 16 | floorc[2] << 8 | 255;
	size_t					x;
	size_t					y;
	
	mlx->ceiling = mlx_new_image(mlx->mlx, 800, 300);
	mlx->floor = mlx_new_image(mlx->mlx, 800, 500);
	y = 0;
	while (y < 500)
	{
		x = 0;
		while (x < 800)
		{
			mlx_put_pixel(mlx->floor, x, y, converted_floor);
			if (y <= 300)
				mlx_put_pixel(mlx->ceiling, x, y, converted_ceiling);
			x++;
		}
		y++; 
	}
	mlx_image_to_window(mlx->mlx, mlx->ceiling, 0, 0);
	mlx_image_to_window(mlx->mlx, mlx->floor, 0, 300);
}
