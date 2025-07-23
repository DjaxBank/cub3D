/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:05:51 by showard           #+#    #+#             */
/*   Updated: 2025/07/23 15:20:32 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	check_keys(void *game)
{
	return (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_W)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_S)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_A)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_D)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_UP)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_DOWN));
}
static void swap_walls(t_data *game)
{
	mlx_texture_t *temp;

	temp = game->mlx.tex[W];
	game->mlx.tex[W] = game->mlx.tex2[W];
	game->mlx.tex2[W] = temp;
	temp = game->mlx.tex[E];
	game->mlx.tex[E] = game->mlx.tex2[E];
	game->mlx.tex2[E] = temp;
}

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		open_door(param);
	}

void key_hook(struct mlx_key_data key, void *game)
{
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(((t_data *)game)->mlx.mlx);
	else if (key.key == MLX_KEY_LEFT_CONTROL && key.action == MLX_PRESS)
	{
		((t_data *)game)->toggle = !((t_data *)game)->toggle;
		return;
	}
	else if (key.key == MLX_KEY_ENTER && key.action == MLX_PRESS)
			open_door(game);
}

void	loop_hook(void *game)
{
	static double		deltatime;
	static double		save[3];
	
	deltatime += ((t_data *)game)->mlx.mlx->delta_time;
	handle_window_resize(game);
	if (check_keys(game))
	{
		keypress(game);
		if (save[0] != ((t_data *)game)->player.pos_y
		|| save[1] != ((t_data *)game)->player.pos_x
		|| save[2] != ((t_data *)game)->player.orientation)
	{
		save[0] = ((t_data *)game)->player.pos_y;
		save[1] = ((t_data *)game)->player.pos_x;
		save[2] = ((t_data *)game)->player.orientation;
		if (deltatime < 2)
			raycaster(game, false);
		draw_minimap(game, false);
	}
	}
	if (deltatime >= 2)
	{
		swap_walls(game);
		raycaster(game, false);
		deltatime = 0;
	}
}
