/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 13:39:27 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void key_hook(struct mlx_key_data key, void *param)
{
	static int count;
	static int size = 100;
	mlx_image_t *image;
	mlx_s *box;
	box = param;
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

int main()
{
	mlx_s box;
	box.background = mlx_load_png("textures/Background.png");
	box.block = mlx_load_png("textures/block.png");
	box.mlx = mlx_init(800, 800, "Cub3d", false);
	box.background_image = mlx_texture_to_image(box.mlx, box.background);
	mlx_resize_image(box.background_image, 800, 800);
	mlx_image_to_window(box.mlx, box.background_image, 0, 0);
	mlx_key_hook(box.mlx, key_hook, &box);
	mlx_loop(box.mlx);
	mlx_terminate(box.mlx);
}