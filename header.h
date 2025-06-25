/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:46:47 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 14:15:09 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_texture_t	*background;
	mlx_image_t		*background_image;
	mlx_texture_t	*block;
	mlx_image_t		*block_image;
	
} s_mlx;

typedef struct s_player
{
	unsigned int orientation;
	
}	s_player;

typedef struct s_game_data
{
	char		**map;
	s_player	player;

} s_game_data;
