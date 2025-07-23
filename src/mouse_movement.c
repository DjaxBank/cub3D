/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:42:59 by dbank             #+#    #+#             */
/*   Updated: 2025/07/23 15:22:50 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void mousemovement(double x, double y, void *game)
{
	int	differential;

	if (((t_data *)game)->toggle == false)
		return ;
	(void)y;
	differential = x - ((t_data *)game)->mlx.mlx->width / 2;
	if (differential < 0)
		differential *= -1;
	printf("%d\n", differential);
	if (x < ((t_data *)game)->mlx.mlx->width / 2)
		((t_data *)game)->player.orientation -= (0.05) * ((t_data *)game)->mlx.mlx->delta_time
				* 60.0;
	if (x > ((t_data *)game)->mlx.mlx->width / 2)
		((t_data *)game)->player.orientation += (0.05) * ((t_data *)game)->mlx.mlx->delta_time
				* 60.0;
	raycaster(game, false);	
	mlx_set_mouse_pos(((t_data *)game)->mlx.mlx, ((t_data *)game)->mlx.mlx->width / 2, ((t_data *)game)->mlx.mlx->height / 2);
}