/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/15 15:05:51 by showard       #+#    #+#                 */
/*   Updated: 2025/07/18 13:18:17 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	loop_hook(void *game)
{
	static double	save[3];

	handle_window_resize(game);
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(((t_data *)game)->mlx.mlx);
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_ENTER))
		open_door(game);
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_W)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_S)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_A)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_D)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_UP)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_DOWN))
		keypress(game);
	if (save[0] != ((t_data *)game)->player.pos_y
		|| save[1] != ((t_data *)game)->player.pos_x
		|| save[2] != ((t_data *)game)->player.orientation)
	{
		save[0] = ((t_data *)game)->player.pos_y;
		save[1] = ((t_data *)game)->player.pos_x;
		save[2] = ((t_data *)game)->player.orientation;
		(raycaster(game, false), draw_minimap(game, false));
	}
}
