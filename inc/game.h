/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:46:47 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 14:25:09 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "MLX42/include/MLX42/MLX42.h"
# include <stdio.h>

typedef struct s_player
{
	unsigned int	orientation;
	int				pos[2];
	
}	s_player;

typedef struct s_game_data
{
	char		**map;
	s_player	player;
	
} s_game_data;

typedef struct s_mlx
{
	mlx_t			*mlx;
	s_game_data		game;
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	mlx_texture_t	*block;
	mlx_image_t		*block_image;
	
} s_mlx;

void	key_hook(struct mlx_key_data key, void *param);
void	loop_hook(void *param);
void	render_background(const int ceilingc[3], const int floorc[3], s_mlx *mlx);

#endif