/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/07/02 23:44:03 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	
	ft_bzero(&data, sizeof(t_data));
	if (argc != 2 || input_check(argv[1], &data) != 1)
	{
		printf("Error\n");
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	map_init(&data);
	data.mlx.block = mlx_load_png("textures/block.png");
	data.mlx.mlx = mlx_init(800, 800, "Cub3d", false);
	data.mlx.wall = malloc(800 * sizeof(mlx_image_t *));
	data.player.orientation = -M_PI/2;
	mlx_key_hook(data.mlx.mlx, key_hook, &data);
	render_background((int[3]){40, 40, 120}, (int[3]){50, 110, 40}, &data.mlx);
	raycaster(&data);
	mlx_loop(data.mlx.mlx);
	mlx_terminate(data.mlx.mlx);
	free(data.mlx.wall);
	return 0;
}
