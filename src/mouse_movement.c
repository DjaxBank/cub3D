/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_movement.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: showard <showard@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/31 16:29:04 by showard       #+#    #+#                 */
/*   Updated: 2025/08/06 13:58:07 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

static bool	initialized_questionmark(double *last_x, double *last_y, double x,
		double y)
{
	static bool	initialized = false;

	if (!initialized)
	{
		*last_x = x;
		*last_y = y;
		initialized = true;
		return (false);
	}
	return (true);
}

static void	mousemovement(double x, double y, void *param)
{
	t_data			*game;
	static double	last_x = 0;
	static double	last_y = 0;
	const double	sensitivity = 0.001;

	game = param;
	if (!game->mouse_enabled || !initialized_questionmark(&last_x, &last_y, x,
			y))
		return ;
	game->player.orientation += (x - last_x) * sensitivity
		* (game->mlx.mlx->delta_time * 60.0);
	last_x = x;
	last_y = y;
	if (game->player.orientation < 0)
		game->player.orientation += 2 * M_PI;
	else if (game->player.orientation > 2 * M_PI)
		game->player.orientation -= 2 * M_PI;
	if (x > game->mlx.mlx->width - 5 || x < 5)
	{
		mlx_set_mouse_pos(((t_data *)game)->mlx.mlx,
			((t_data *)game)->mlx.mlx->width / 2,
			((t_data *)game)->mlx.mlx->height / 2);
		last_x = ((t_data *)game)->mlx.mlx->width / 2;
		last_y = ((t_data *)game)->mlx.mlx->height / 2;
	}
}

static bool	check_if_mouse_moved(int32_t x, int32_t y, t_data *data)
{
	if (data->last_mouse_x != x || data->last_mouse_y != y)
	{
		data->last_mouse_x = x;
		data->last_mouse_y = y;
		return (mousemovement((double)data->last_mouse_x,
				(double)data->last_mouse_y, data), true);
	}
	return (false);
}

static int	check_keys(void *game)
{
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_W)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_S)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_A)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_D)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_UP)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_DOWN))
		return (keypress(game), true);
	return (false);
}

int	check_stuff(int32_t mouse[2], t_data *data)
{
	const bool	keys = check_keys(data);
	const bool	mouse_chck = check_if_mouse_moved(mouse[0], mouse[1], data);

	return (keys || mouse_chck);
}
