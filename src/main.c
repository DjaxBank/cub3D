/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/06/27 16:27:01 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

int	main(int argc, char *argv[])
{
	t_state		state;
	s_mlx		box;
	
	ft_bzero(&state, sizeof(t_state));
	if (argc != 2 || input_check(argv[1], &state) != 1)
	{
		printf("Error\n");
		printf("Usage: ./cub3d <map_file.cub>\n");
		return (1);
	}
	// map_init(&state);

	box.block = mlx_load_png("textures/block.png");
	box.mlx = mlx_init(800, 800, "Cub3d", false);
	mlx_key_hook(box.mlx, key_hook, &box);
	mlx_loop_hook(box.mlx, loop_hook, &box);
	render_background((int[3]){130, 16, 182}, (int[3]){23, 130, 230}, &box);
	mlx_loop(box.mlx);
	mlx_terminate(box.mlx);
	return 0;
}
