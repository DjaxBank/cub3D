/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/06/25 14:30:44 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

int	main(int argc, char *argv[])
{
	t_state state;
	s_mlx		box;
	// s_game_data game;
	
	ft_bzero(&state, sizeof(t_state));
	if (argc != 2 || input_check(argv[1], &state) != 1)
	{
		printf("Error\n");
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	// map_init(&state);

	box.background = mlx_load_png("textures/Background.png");
	box.block = mlx_load_png("textures/block.png");
	box.mlx = mlx_init(800, 800, "Cub3d", false);
	box.background_image = mlx_texture_to_image(box.mlx, box.background);
	mlx_resize_image(box.background_image, 800, 800);
	mlx_image_to_window(box.mlx, box.background_image, 0, 0);
	mlx_key_hook(box.mlx, key_hook, &box);
	mlx_loop(box.mlx);
	mlx_terminate(box.mlx);
	return 0;
}