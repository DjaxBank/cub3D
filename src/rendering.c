/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/25 14:24:43 by dbank         #+#    #+#                 */
/*   Updated: 2025/07/14 19:39:13 by showard       ########   odam.nl         */
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
    const uint32_t converted_ceiling = ceilingc[0] << 24 | ceilingc[1] << 16 | ceilingc[2] << 8 | 255;
    const uint32_t converted_floor = floorc[0] << 24 | floorc[1] << 16 | floorc[2] << 8 | 255;

    if (!is_window_size_valid(mlx->mlx->width, mlx->mlx->height))
        return;
    if (force_recreate || !mlx->ceiling)
    {
        if (mlx->ceiling)
            mlx_delete_image(mlx->mlx, mlx->ceiling);
        mlx->ceiling = mlx_new_image(mlx->mlx, mlx->mlx->width, mlx->mlx->height / 2);
        if (!mlx->ceiling)
        {
            printf("Failed to create ceiling image\n");
            return;
        }
        mlx_image_to_window(mlx->mlx, mlx->ceiling, 0, 0);
        mlx_set_instance_depth(mlx->ceiling->instances, 0);
    }
    fill_image(mlx->ceiling, converted_ceiling, mlx->mlx->width, mlx->mlx->height / 2);
    if (force_recreate || !mlx->floor)
    {
        if (mlx->floor)
            mlx_delete_image(mlx->mlx, mlx->floor);
        mlx->floor = mlx_new_image(mlx->mlx, mlx->mlx->width, mlx->mlx->height / 2);
        if (!mlx->floor)
        {
            printf("Failed to create floor image\n");
            return;
        }
        mlx_image_to_window(mlx->mlx, mlx->floor, 0, mlx->mlx->height / 2);
        mlx_set_instance_depth(mlx->floor->instances, 0);
    }
    fill_image(mlx->floor, converted_floor, mlx->mlx->width, mlx->mlx->height / 2);
}
