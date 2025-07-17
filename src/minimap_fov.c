/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:35:31 by showard           #+#    #+#             */
/*   Updated: 2025/07/17 12:33:53 by showard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	draw_minimap_ray(t_data *data, double angle, double max_distance,
		uint32_t color)
{
	double	x;
	double	y;
	double	distance;
	int		px;
	int		py;

	x = data->player.pos_x;
	y = data->player.pos_y;
	distance = 0.0;
	while (distance < max_distance)
	{
		if (data->map[(int)y][(int)x] == '1'
			|| data->map[(int)y][(int)x] == 'D')
			break ;
		px = (int)(x * data->minimap_scale);
		py = (int)(y * data->minimap_scale);
		if (px >= 0 && py >= 0 && px < data->map_width * data->minimap_scale
			&& py < data->map_height * data->minimap_scale)
		{
			mlx_put_pixel(data->mlx.minimap_image, px, py, color);
		}
		x += cos(angle) * 0.05;
		y += sin(angle) * 0.05;
		distance += 0.05;
	}
}

void	draw_minimap_fov(t_data *data)
{
	int		i;
	double	fov;
	double	start_angle;
	double	ray_angle;
	double	max_distance;

	i = 0;
	fov = 60.0 * M_PI / 180.0;
	start_angle = data->player.orientation - fov / 2.0;
	max_distance = 100.0;
	while (i < 120)
	{
		ray_angle = start_angle + (fov * i) / (120 - 1);
		draw_minimap_ray(data, ray_angle, max_distance, 0xFF00D97E);
		i++;
	}
}
