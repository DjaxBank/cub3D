/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:46:47 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 13:17:31 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
typedef struct mlx_s
{
	mlx_t *mlx;
	mlx_texture_t *background;
	mlx_image_t *background_image;
	mlx_texture_t *block;
	mlx_image_t *block_image;
	
} mlx_s;