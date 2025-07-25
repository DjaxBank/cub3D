/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:26:48 by dbank             #+#    #+#             */
/*   Updated: 2025/07/25 17:07:41 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	up(double *new_y, double *new_x, t_data *game)
{
	*new_y += sin(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	*new_x += cos(game->player.orientation) / 20.0
		* (game->mlx.mlx->delta_time * 60.0);
}

static void	down(double *new_y, double *new_x, t_data *game)
{
	*new_y -= sin(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	*new_x -= cos(game->player.orientation) / 20.0
		* (game->mlx.mlx->delta_time * 60.0);
}

static void	left(double *new_y, double *new_x, t_data *game)
{
	*new_y -= cos(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	*new_x += sin(game->player.orientation) / 20.0
		* (game->mlx.mlx->delta_time * 60.0);
}

static void	right(double *new_y, double *new_x, t_data *game)
{
	*new_y += cos(game->player.orientation)
		/ 20.0 * (game->mlx.mlx->delta_time * 60.0);
	*new_x -= sin(game->player.orientation) / 20.0
		* (game->mlx.mlx->delta_time * 60.0);
}

void	handle_key_movement(t_data *game, double *new_y, double *new_x)
{
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx.mlx, MLX_KEY_UP))
		up(new_y, new_x, game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx.mlx, MLX_KEY_DOWN))
		down(new_y, new_x, game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_A))
		left(new_y, new_x, game);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_D))
		right(new_y, new_x, game);
}
