/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:29 by dbank             #+#    #+#             */
/*   Updated: 2025/06/30 14:34:59 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "parse.h"

char **testmap()
{
	char	**map = malloc(7 * sizeof(char *));

	map[0] = ft_strdup("1111111111111111111");
	map[1] = ft_strdup("1000000000000000001");
	map[2] = ft_strdup("1000000000000000001");
	map[3] = ft_strdup("1000000000000000001");
	map[4] = ft_strdup("100000000N000000001");
	map[5] = ft_strdup("1111111111111111111");
	map[6] = NULL;
	return (map);
}
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
	box.game.map = test_map();
	mlx_loop_hook(box.mlx, loop_hook, &box);
	render_background((int[3]){40, 40, 120}, (int[3]){50, 110, 40}, &box);
	mlx_loop(box.mlx);
	mlx_terminate(box.mlx);
	return 0;
}
