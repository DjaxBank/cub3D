/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:59:36 by dbank             #+#    #+#             */
/*   Updated: 2025/06/30 16:18:32 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void move_ray(int ray[2], int orientation)
{
	
}

void	raycaster(void *param)
{
	t_data	*game;
	int		ray[2];
	size_t	count;

	game = param;
	ray[0] = game->player.pos_x;
	ray[1] = game->player.pos_y;
	count = 0;
	while (game->map[ray[1]][ray[0]] != '1')
	{
		count++;
		ray[1]++;
	}
}
