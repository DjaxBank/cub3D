/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:05:51 by showard           #+#    #+#             */
/*   Updated: 2025/07/16 14:43:16 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void    handle_key_w(t_data *game)
{
	double      new_y;
	double      new_x;

	new_y = game->player.pos_y + sin(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	new_x = game->player.pos_x + cos(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	collision_check(game, new_y, new_x);
}

static void    handle_key_s(t_data *game)
{
	double      new_y;
	double      new_x;

	new_y = game->player.pos_y - sin(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	new_x = game->player.pos_x - cos(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	collision_check(game, new_y, new_x);
}

static void    handle_key_a(t_data *game)
{
	game->player.orientation -= 0.05
		* (game->mlx.mlx->delta_time * 60.0);
}

static void    handle_key_d(t_data *game)
{
	game->player.orientation += 0.05
		* (game->mlx.mlx->delta_time * 60.0);
}

void	loop_hook(void *param)
{
	t_data			*game;
	const double	save[3] = {((t_data*)param)->player.pos_y,
		((t_data *)param)->player.pos_x, ((t_data *)param)->player.orientation};

	game = (t_data *)param;
	handle_window_resize(game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx.mlx);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_ENTER))
		open_door(game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_W))
		handle_key_w(game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_S))
		handle_key_s(game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_A))
		handle_key_a(game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_D))
		handle_key_d(game);
	if (save[0] != game->player.pos_y || save[1] != game->player.pos_x
		|| save[2] != game->player.orientation)
	{
		raycaster(game, false);
		draw_minimap(game, false);
	}
}
