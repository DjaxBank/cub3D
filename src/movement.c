/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:08:10 by showard           #+#    #+#             */
/*   Updated: 2025/07/17 13:46:37 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	try_x_movement(t_data *game, float new_x)
{
	float	temp_x;
	float	temp_y;

	if (game->map[(int)game->player.pos_y][(int)(new_x - 0.1)] != '1'
		&& game->map[(int)game->player.pos_y][(int)(new_x + 0.1)] != '1'
		&& game->map[(int)game->player.pos_y][(int)(new_x - 0.1)] != 'D'
		&& game->map[(int)game->player.pos_y][(int)(new_x + 0.1)] != 'D')
	{
		temp_x = new_x;
		temp_y = game->player.pos_y;
		if (game->map[(int)(temp_y - 0.1)][(int)(temp_x - 0.1)] != '1'
			&& game->map[(int)(temp_y - 0.1)][(int)(temp_x + 0.1)] != '1'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x - 0.1)] != '1'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x + 0.1)] != '1'
			&& game->map[(int)(temp_y - 0.1)][(int)(temp_x - 0.1)] != 'D'
			&& game->map[(int)(temp_y - 0.1)][(int)(temp_x + 0.1)] != 'D'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x - 0.1)] != 'D'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x + 0.1)] != 'D')
			game->player.pos_x = new_x;
	}
}

static void	try_y_movement(t_data *game, float new_y)
{
	float	temp_x;
	float	temp_y;

	if (game->map[(int)(new_y - 0.1)][(int)(game->player.pos_x)] != '1'
		&& game->map[(int)(new_y + 0.1)][(int)(game->player.pos_x)] != '1'
		&& game->map[(int)(new_y - 0.1)][(int)(game->player.pos_x)] != 'D'
		&& game->map[(int)(new_y + 0.1)][(int)(game->player.pos_x)] != 'D')
	{
		temp_x = game->player.pos_x;
		temp_y = new_y;
		if (game->map[(int)(temp_y - 0.1)][(int)(temp_x - 0.1)] != '1'
			&& game->map[(int)(temp_y - 0.1)][(int)(temp_x + 0.1)] != '1'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x - 0.1)] != '1'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x + 0.1)] != '1'
			&& game->map[(int)(temp_y - 0.1)][(int)(temp_x - 0.1)] != 'D'
			&& game->map[(int)(temp_y - 0.1)][(int)(temp_x + 0.1)] != 'D'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x - 0.1)] != 'D'
			&& game->map[(int)(temp_y + 0.1)][(int)(temp_x + 0.1)] != 'D')
		{
			game->player.pos_y = new_y;
		}
	}
}

static void	collision_check(t_data *game, float new_y, float new_x)
{
	if (game->map[(int)(new_y - 0.1)][(int)(new_x - 0.1)] != '1'
		&& game->map[(int)(new_y - 0.1)][(int)(new_x + 0.1)] != '1'
		&& game->map[(int)(new_y + 0.1)][(int)(new_x - 0.1)] != '1'
		&& game->map[(int)(new_y + 0.1)][(int)(new_x + 0.1)] != '1'
		&& game->map[(int)(new_y - 0.1)][(int)(new_x - 0.1)] != 'D'
		&& game->map[(int)(new_y - 0.1)][(int)(new_x + 0.1)] != 'D'
		&& game->map[(int)(new_y + 0.1)][(int)(new_x - 0.1)] != 'D'
		&& game->map[(int)(new_y + 0.1)][(int)(new_x + 0.1)] != 'D')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	try_x_movement(game, new_x);
	try_y_movement(game, new_y);
}

static int	handle_key_movement(t_data *game, double *new_y, double *new_x)
{
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_W))
		return (*new_y = game->player.pos_y + sin(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0),
			*new_x = game->player.pos_x + cos(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0));
	else if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_S))
		return (*new_y = game->player.pos_y - sin(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0),
			*new_x = game->player.pos_x - cos(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0));
	else if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_A))
		return (*new_y = game->player.pos_y - cos(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0),
			*new_x = game->player.pos_x + sin(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0));
	else
		return (*new_y = game->player.pos_y + cos(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0),
			*new_x = game->player.pos_x - sin(game->player.orientation)
			/ 20.0 * (game->mlx.mlx->delta_time * 60.0));
}

void	keypress(t_data *game)
{
	double	new_y;
	double	new_x;

	new_x = 0;
	new_y = 0;
	if (mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_W)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_S)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_A)
		|| mlx_is_key_down(((t_data *)game)->mlx.mlx, MLX_KEY_D))
		return (handle_key_movement(game, &new_y, &new_x),
			collision_check(game, new_y, new_x));
	else
	{
		if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_LEFT))
		{
			game->player.orientation -= 0.05
				*(game->mlx.mlx->delta_time * 60.0);
		}
		else
		{
			game->player.orientation += 0.05
				* (game->mlx.mlx->delta_time * 60.0);
		}
	}
}
