/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/07/15 14:05:12 by showard          ###   ########.fr       */
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

void render_background(const int ceilingc[3], const int floorc[3], t_mlx *mlx, bool force_recreate)
{
    const uint32_t converted_ceiling = ceilingc[0]<<24 | ceilingc[1]<<16 | ceilingc[2]<<8 | 255;
    const uint32_t converted_floor   = floorc[0]<<24   | floorc[1]<<16   | floorc[2]<<8   | 255;

    if (!is_window_size_valid(mlx->mlx->width, mlx->mlx->height))
        return;

    printf("1\n");
    // --- CEILING ---
    if (force_recreate || !mlx->ceiling)
    {
        // 1) Make new image first
        mlx_image_t *new_ceil = mlx_new_image(mlx->mlx,
            mlx->mlx->width, mlx->mlx->height / 2);
        if (!new_ceil)
        {
            fprintf(stderr, "Failed to create ceiling image\n");
            return;
        }
        // 2) Fill & show it
        fill_image(new_ceil, converted_ceiling,
            mlx->mlx->width, mlx->mlx->height / 2);
        mlx_image_to_window(mlx->mlx, new_ceil, 0, 0);
        mlx_set_instance_depth(new_ceil->instances, 0);
        // 3) Now delete the old one
        if (mlx->ceiling)
            mlx_delete_image(mlx->mlx, mlx->ceiling);
        // 4) Swap in
        mlx->ceiling = new_ceil;
    }
    else
    {
        // No recreate: just recolor
        fill_image(mlx->ceiling, converted_ceiling,
            mlx->mlx->width, mlx->mlx->height / 2);
    }
    printf("2\n");
    // --- FLOOR ---
    if (force_recreate || !mlx->floor)
    {
        mlx_image_t *new_floor = mlx_new_image(mlx->mlx,
            mlx->mlx->width, mlx->mlx->height / 2);
        if (!new_floor)
        {
            fprintf(stderr, "Failed to create floor image\n");
            return;
        }
        fill_image(new_floor, converted_floor,
            mlx->mlx->width, mlx->mlx->height / 2);
        mlx_image_to_window(mlx->mlx, new_floor, 0, mlx->mlx->height / 2);
        mlx_set_instance_depth(new_floor->instances, 0);
        if (mlx->floor)
            mlx_delete_image(mlx->mlx, mlx->floor);
        mlx->floor = new_floor;
    }
    else
    {
        fill_image(mlx->floor, converted_floor,
            mlx->mlx->width, mlx->mlx->height / 2);
    }
     printf("3\n");
}
