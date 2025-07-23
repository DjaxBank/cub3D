/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/15 15:05:51 by showard       #+#    #+#                 */
/*   Updated: 2025/07/23 13:58:05 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

static void mousemovement(t_data *game)
{
	int			mousepos[2];
	int	differential;

	mlx_get_mouse_pos((t_data *){game}->mlx.mlx, &mousepos[0], &mousepos[1]);
	differential = mousepos[1] - ((t_data *)game)->mlx.mlx->width / 2;
	if (differential < 0)
		differential *= -1;
	printf("%d\n", differential);
	if (mousepos[0] < ((t_data *)game)->mlx.mlx->width / 2)
		((t_data *)game)->player.orientation -= (0.05 * differential) * ((t_data *)game)->mlx.mlx->delta_time
				* 60.0;
	if (mousepos[0] > ((t_data *)game)->mlx.mlx->width / 2)
		((t_data *)game)->player.orientation += (0.05 * differential) * ((t_data *)game)->mlx.mlx->delta_time
				* 60.0;
	mlx_set_mouse_pos(((t_data *)game)->mlx.mlx, ((t_data *)game)->mlx.mlx->width / 2, ((t_data *)game)->mlx.mlx->height / 2);
	
}

void	loop_hook(void *game)
{
	static double		save[3];
	static double		deltatime;
	bool				raycasterrun;
	
	deltatime += ((t_data *)game)->mlx.mlx->delta_time;
	raycasterrun = false;
	if (((t_data *)game)->toggle == false)
		mousemovement(game);
	handle_window_resize(game);
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(((t_data *)game)->mlx.mlx);
	if (check_keys(game))
		keypress(game);
	if (save[0] != ((t_data *)game)->player.pos_y
		|| save[1] != ((t_data *)game)->player.pos_x
		|| save[2] != ((t_data *)game)->player.orientation)
	{
		save[0] = ((t_data *)game)->player.pos_y;
		save[1] = ((t_data *)game)->player.pos_x;
		save[2] = ((t_data *)game)->player.orientation;
		(raycasterrun = true, raycaster(game, false), draw_minimap(game, false));
	}
	if (deltatime > 2)
	{
		swap_walls(game);
		if (!raycasterrun)
			raycaster(game, false);
		deltatime = 0;
	}
}
