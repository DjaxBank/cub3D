/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils_b.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 15:44:49 by showard       #+#    #+#                 */
/*   Updated: 2025/07/24 14:26:40 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	count_list(t_list *lst)
{
	t_list	*current;
	int		i;

	i = 0;
	current = lst;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	torch_check(t_data *data, t_mlx *mlx)
{
	if (ft_strcmp("./textures/Wall_3_rtorch.png", data->w_tex) == 0)
	{
		mlx->tex2[W] = mlx_load_png("./textures/Wall_3_2.png");
		if (mlx->tex2[W] == NULL)
			werror("Failure loading WE2 texture.", data);
		data->rtorch = true;
	}
	if (ft_strcmp("./textures/Wall_4_btorch.png", data->e_tex) == 0)
	{
		mlx->tex2[E] = mlx_load_png("./textures/Wall_4_1.png");
		if (mlx->tex2[E] == NULL)
			werror("Failure loading EA2 texture.", data);
		data->btorch = true;
	}
}
