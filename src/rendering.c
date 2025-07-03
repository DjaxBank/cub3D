/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/07/03 15:49:12 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

static void move_player(struct mlx_key_data key, t_data *game)
{
	float new_y;
	float new_x;

	new_y = 0;
	new_x = 0;
	if (key.key == MLX_KEY_W)
	{
		new_y = game->player.pos_y + sin(game->player.orientation) / 10;
		new_x = game->player.pos_x + cos(game->player.orientation) / 10;
	}
	else if (key.key == MLX_KEY_S)
	{
		new_y = game->player.pos_y - sin(game->player.orientation) / 10;
		new_x = game->player.pos_x - cos(game->player.orientation) / 10;
	}
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	key_hook(struct mlx_key_data key, void *param)
{
	t_data *game;

	game = param;
	if (key.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx.mlx);
		return;
	}
	if (key.key == MLX_KEY_A)
		game->player.orientation -= 0.03;
	else if (key.key == MLX_KEY_D)
		game->player.orientation += 0.03;
	else if (key.key == MLX_KEY_W || key.key == MLX_KEY_S)
		move_player(key, param);
	raycaster(param);
}

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
	
	mlx->ceiling = mlx_new_image(mlx->mlx, 800, 400);
	fill_image(mlx->ceiling, converted_ceiling, 800, 400);
	mlx->floor = mlx_new_image(mlx->mlx, 800, 400);
	fill_image(mlx->floor, converted_floor, 800, 400);
	mlx_image_to_window(mlx->mlx, mlx->ceiling, 0, 0);
	mlx_image_to_window(mlx->mlx, mlx->floor, 0, 400);
}
