/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/15 15:05:51 by showard       #+#    #+#                 */
/*   Updated: 2025/07/31 16:31:35 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	swap_walls(t_data *game)
{
	mlx_texture_t	*temp;

	if (game->rtorch == true)
	{
		temp = game->mlx.tex[W];
		game->mlx.tex[W] = game->mlx.tex2[W];
		game->mlx.tex2[W] = temp;
	}
	if (game->btorch == true)
	{
		temp = game->mlx.tex[E];
		game->mlx.tex[E] = game->mlx.tex2[E];
		game->mlx.tex2[E] = temp;
	}
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		open_door(param);
}

void	key_hook(struct mlx_key_data key, void *game)
{
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(((t_data *)game)->mlx.mlx);
	else if (key.key == MLX_KEY_LEFT_CONTROL && key.action == MLX_PRESS)
	{
		((t_data *)game)->mouse_enabled = !((t_data *)game)->mouse_enabled;
		if (((t_data *)game)->mouse_enabled)
			mlx_set_cursor_mode(((t_data *)game)->mlx.mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(((t_data *)game)->mlx.mlx, MLX_MOUSE_NORMAL);
	}
	else if (key.key == MLX_KEY_ENTER && key.action == MLX_PRESS)
		open_door(game);
}

void	loop_hook(void *param)
{
	t_data			*data;
	static double	deltatime;
	static double	save[3];
	int32_t			mouse[2];

	data = (t_data *)param;
	deltatime += data->mlx.mlx->delta_time;
	mlx_get_mouse_pos(data->mlx.mlx, &mouse[0], &mouse[1]);
	handle_window_resize(data);
	if (check_stuff(mouse, data) && (save[0] != data->player.pos_y
			|| save[1] != data->player.pos_x
			|| save[2] != data->player.orientation))
	{
		save[0] = data->player.pos_y;
		save[1] = data->player.pos_x;
		save[2] = data->player.orientation;
		if (deltatime < 2.0)
			raycaster(data, false);
		draw_minimap(data, true);
	}
	if (deltatime >= 2.0)
	{
		(swap_walls(data), raycaster(data, false));
		deltatime = 0.0;
	}
}
