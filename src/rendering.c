/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 14:30:29 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

void key_hook(struct mlx_key_data key, void *param)
{
	static int count;
	static int size = 100;
	mlx_image_t *image;
	s_mlx *box;
	box = param;
	(void)key;
	if (mlx_is_key_down(box->mlx, MLX_KEY_ESCAPE))
		return (mlx_close_window(box->mlx));
	else if (!mlx_is_key_down(box->mlx, MLX_KEY_RIGHT))
		return ;
	image = mlx_texture_to_image(box->mlx, box->block);
	mlx_resize_image(image, size, size);
	mlx_image_to_window(box->mlx, image, count * 80, 0 + (300 + (count * 2)));
	count++;
	size -= 10;
}