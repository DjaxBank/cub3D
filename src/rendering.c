/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/07/17 13:32:07 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

void	fill_image(mlx_image_t *image, uint32_t colour, size_t width,
		size_t height)
{
	size_t	x;
	size_t	y;

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

static void	recreate_bg_image(t_data *data, mlx_image_t **img, int y_offset)
{
	if (*img)
		mlx_delete_image(data->mlx.mlx, *img);
	*img = mlx_new_image(data->mlx.mlx, data->mlx.mlx->width,
			data->mlx.mlx->height / 2);
	if (!*img)
		werror("Failed to create background image", data);
	if (mlx_image_to_window(data->mlx.mlx, *img, 0, y_offset) == -1)
		werror("Failed to add background image to window", data);
	mlx_set_instance_depth((*img)->instances, 0);
}

void	render_background(const int ceilingc[3], const int floorc[3],
		t_data *data, bool force_recreate)
{
	uint32_t	converted_ceiling;
	uint32_t	converted_floor;

	converted_ceiling = ceilingc[0] << 24;
	converted_ceiling |= ceilingc[1] << 16;
	converted_ceiling |= ceilingc[2] << 8;
	converted_ceiling |= 255;
	converted_floor = floorc[0] << 24;
	converted_floor |= floorc[1] << 16;
	converted_floor |= floorc[2] << 8;
	converted_floor |= 255;
	if (!is_window_size_valid(data->mlx.mlx->width, data->mlx.mlx->height))
		return ;
	if (force_recreate || !data->mlx.ceiling)
		recreate_bg_image(data, &data->mlx.ceiling, 0);
	fill_image(data->mlx.ceiling, converted_ceiling, data->mlx.mlx->width,
		data->mlx.mlx->height / 2);
	if (force_recreate || !data->mlx.floor)
		recreate_bg_image(data, &data->mlx.floor, data->mlx.mlx->height / 2);
	fill_image(data->mlx.floor, converted_floor, data->mlx.mlx->width,
		data->mlx.mlx->height / 2);
}
