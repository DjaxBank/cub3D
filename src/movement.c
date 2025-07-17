/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: showard <showard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:08:10 by showard           #+#    #+#             */
/*   Updated: 2025/07/17 12:39:05 by showard          ###   ########.fr       */
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

void	collision_check(t_data *game, float new_y, float new_x)
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
