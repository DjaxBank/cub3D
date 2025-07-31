/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:42:59 by dbank             #+#    #+#             */
/*   Updated: 2025/07/31 14:04:29 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	mousemovement(double x, double y, void *game)
{
	static bool	ignore;

	if (((t_data *)game)->mouse_enabled == false || ignore)
	{
		if (ignore)
			ignore = false;
		return ;
	}
	(void)y;
	if (x < ((t_data *)game)->mlx.mlx->width / 2)
		((t_data *)game)->player.orientation -= 0.05
			* ((t_data *)game)->mlx.mlx->delta_time * 60.0;
	if (x > ((t_data *)game)->mlx.mlx->width / 2)
		((t_data *)game)->player.orientation += 0.05
			* ((t_data *)game)->mlx.mlx->delta_time * 60.0;
	raycaster(game, false);
	draw_minimap(game, false);
	mlx_set_mouse_pos(((t_data *)game)->mlx.mlx,
		((t_data *)game)->mlx.mlx->width / 2, ((t_data *)game)->mlx.mlx->height
		/ 2);
	ignore = true;
}
