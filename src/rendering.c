/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/08/01 16:09:59 by dbank            ###   ########.fr       */
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

static void	fill_background(t_data *data, uint32_t colours[2])
{
	int	x;
	int	y;

	y = 0;
	while (y < data->mlx.mlx->height)
	{
		x = 0;
		while (x < data->mlx.mlx->width)
		{
			if (y < data->mlx.mlx->height / 2)
				mlx_put_pixel(data->mlx.background, x, y, colours[0]);
			else
				mlx_put_pixel(data->mlx.background, x, y, colours[1]);
			x++;
		}
		y++;
	}
}

static void	recreate_bg_image(t_data *data,
			uint32_t converted_ceiling, uint32_t converted_floor)
{
	mlx_resize_image(data->mlx.background, data->mlx.mlx->width,
		data->mlx.mlx->height);
	if (!data->mlx.background)
		werror("Failed to resize background image", data);
	fill_background(data, (uint32_t[2]){converted_ceiling, converted_floor});
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
	if (force_recreate || !data->mlx.background)
		recreate_bg_image(data, converted_ceiling, converted_floor);
}

void	create_images(t_data *data)
{
	data->mlx.background = mlx_new_image(data->mlx.mlx,
			data->mlx.mlx->width, data->mlx.mlx->height);
	data->mlx.wall = mlx_new_image(data->mlx.mlx,
			data->mlx.mlx->width, data->mlx.mlx->height);
	data->mlx.open_doors = mlx_new_image(data->mlx.mlx,
			data->mlx.mlx->width, data->mlx.mlx->height);
	if (!data->mlx.background || !data->mlx.wall || !data->mlx.open_doors)
		werror("Failed to create image", data);
	if (mlx_image_to_window(data->mlx.mlx, data->mlx.background, 0, 0) == -1)
		werror("Failed to add background image to window", data);
	if (mlx_image_to_window(data->mlx.mlx, data->mlx.wall, 0, 0) == -1)
		werror("Failed to add background wall to window", data);
	if (mlx_image_to_window(data->mlx.mlx, data->mlx.open_doors, 0, 0) == -1)
		werror("Failed to add door image to window", data);
}
