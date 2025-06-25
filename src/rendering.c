/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:24:43 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 16:02:01 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"
#define y 0
#define x 1
#define BPP sizeof(int32_t)

void	loop_hook(void *param)
{
	#include <stdio.h>
	static unsigned int c;
	s_mlx *box;

	box = param; 
	printf("%d\n", c++);
}

void	key_hook(struct mlx_key_data key, void *param)
{
	static int	count;
	static int	size = 100;
	mlx_image_t	*image;
	s_mlx		*box;

	(void)key;
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

void render_background(const int ceilingc, const int floorc, s_mlx *mlx)
{

	mlx->ceiling = mlx_new_image(mlx->mlx, 800, 400);
	mlx->floor = mlx_new_image(mlx->mlx, 800, 400);
	ft_memset(mlx->ceiling, ceilingc, 800 * 400 * BPP);
	ft_memset(mlx->floor, floorc, 800 * 400 * BPP);
	mlx_image_to_window(mlx->mlx, mlx->ceiling, 0, 0);
	mlx_image_to_window(mlx->mlx, mlx->floor, 0, 400);
}

void	render_window(s_game_data *data)
{
	int pos[2];
	size_t i;

	i = 0;
	pos[x] = data->player.pos[x];
	pos[y] = data->player.pos[y];
	while (data->map[y][x] == '0' || data->map[y][x] == 'P');
	
}
