/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 14:50:17 by showard       #+#    #+#                 */
/*   Updated: 2025/07/15 18:55:21 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

void	put_player_pixel(t_data *data, int pos_x, int pos_y, int radius)
{
	int	offsetx;
	int	offsety;
	int	x;
	int	y;

	offsetx = -radius;
	while (offsetx <= radius)
	{
		offsety = -radius;
		while (offsety <= radius)
		{
			x = pos_x + offsetx;
			y = pos_y + offsety;
			if (x >= 0 && y >= 0 && x < data->map_width * data->minimap_scale
				&& y < data->map_height * data->minimap_scale)
			{
				mlx_put_pixel(data->mlx.minimap_image, x, y, 0xFF00D97E);
			}
			offsety++;
		}
		offsetx++;
	}
}

void	draw_player(t_data *data)
{
	int	pos_x;
	int	pos_y;
	int	radius;

	pos_x = (int)(data->player.pos_x * data->minimap_scale);
	pos_y = (int)(data->player.pos_y * data->minimap_scale);
	radius = data->minimap_scale / 3;
	put_player_pixel(data, pos_x, pos_y, radius);
}

void	draw_minimap_pixel(t_data *data, int map_i, int map_j, uint32_t color)
{
	int	pos_x;
	int	pos_y;
	int	px;
	int	py;

	pos_y = 0;
	while (pos_y < data->minimap_scale)
	{
		pos_x = 0;
		while (pos_x < data->minimap_scale)
		{
			px = map_j * data->minimap_scale + pos_x;
			py = map_i * data->minimap_scale + pos_y;
			mlx_put_pixel(data->mlx.minimap_image, px, py, color);
			pos_x++;
		}
		pos_y++;
	}
}

void	recreate_minimap(t_data *data)
{
	if (data->mlx.minimap_image)
		mlx_delete_image(data->mlx.mlx, data->mlx.minimap_image);
	data->mlx.minimap_image = mlx_new_image(data->mlx.mlx, data->map_width
			* data->minimap_scale, data->map_height * data->minimap_scale);
	if (!data->mlx.minimap_image)
		werror("Failed to create minimap image", data);
	if (mlx_image_to_window(data->mlx.mlx, data->mlx.minimap_image, 10, 10) ==
		-1)
		werror("Failed to add minimap image to window", data);
	mlx_set_instance_depth(data->mlx.minimap_image->instances, 2);
}

void	draw_minimap(t_data *data, bool force_recreate)
{
	int			i;
	int			j;
	uint32_t	color;

	if (!is_window_size_valid(data->mlx.mlx->width, data->mlx.mlx->height))
		return;
	if (force_recreate || !data->mlx.minimap_image)
		recreate_minimap(data);
	fill_image(data->mlx.minimap_image, 0xFF000000, data->map_width
		* data->minimap_scale, data->map_height * data->minimap_scale);
	i = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			color = 0xFFEEEEEE;
			if (data->map[i][j] == '1' || data->map[i][j] == ' ')
				color = 0x000000FF;
            if (data->map[i][j] == 'D')
				color = (uint32_t){176 << 24 | 109 << 16 | 28 << 8 | 255};
			draw_minimap_pixel(data, i, j, color);
			j++;
		}
		i++;
	}
	draw_minimap_fov(data);
	draw_player(data);
}
