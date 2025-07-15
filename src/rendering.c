/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/07/15 14:50:01 by showard          ###   ########.fr       */
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

void render_background(const int ceilingc[3], const int floorc[3], t_data *data, bool force_recreate)
{
    const uint32_t converted_ceiling = ceilingc[0] << 24 | ceilingc[1] << 16 | ceilingc[2] << 8 | 255;
    const uint32_t converted_floor = floorc[0] << 24 | floorc[1] << 16 | floorc[2] << 8 | 255;

    if (!is_window_size_valid(data->mlx.mlx->width, data->mlx.mlx->height))
        return;
    if (force_recreate || !data->mlx.ceiling)
    {
        if (data->mlx.ceiling)
            mlx_delete_image(data->mlx.mlx, data->mlx.ceiling);
        data->mlx.ceiling = mlx_new_image(data->mlx.mlx, data->mlx.mlx->width, data->mlx.mlx->height / 2);
        if (!data->mlx.ceiling)
            werror("Failed to create ceiling image", data);
        if (mlx_image_to_window(data->mlx.mlx, data->mlx.ceiling, 0, 0) == -1)
            werror("Failed to add ceiling image to window", data);
        mlx_set_instance_depth(data->mlx.ceiling->instances, 0);
    }
    fill_image(data->mlx.ceiling, converted_ceiling, data->mlx.mlx->width, data->mlx.mlx->height / 2);
    if (force_recreate || !data->mlx.floor)
    {
        if (data->mlx.floor)
            mlx_delete_image(data->mlx.mlx, data->mlx.floor);
        data->mlx.floor = mlx_new_image(data->mlx.mlx, data->mlx.mlx->width, data->mlx.mlx->height / 2);
        if (!data->mlx.floor)
            werror("Failed to create floor image", data);
        if (mlx_image_to_window(data->mlx.mlx, data->mlx.floor, 0, data->mlx.mlx->height / 2) == -1)
            werror("Failed to add floor image to window", data);
        mlx_set_instance_depth(data->mlx.floor->instances, 0);
    }
    fill_image(data->mlx.floor, converted_floor, data->mlx.mlx->width, data->mlx.mlx->height / 2);
}
