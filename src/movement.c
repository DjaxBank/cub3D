/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:08:10 by showard           #+#    #+#             */
/*   Updated: 2025/07/25 16:32:32 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	keypress(t_data *game)
{
	double	new_y;
	double	new_x;

	new_x = game->player.pos_x;
	new_y = game->player.pos_y;
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_W)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_S)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_A)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_D)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_UP)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_DOWN))
	{
		(handle_key_movement(game, &new_y, &new_x), collision_check(game,
				new_y, new_x));
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_LEFT))
		game->player.orientation -= 0.05 * (game->mlx.mlx->delta_time
				* 60.0);
	else if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_RIGHT))
		game->player.orientation += 0.05 * (game->mlx.mlx->delta_time
				* 60.0);
}
