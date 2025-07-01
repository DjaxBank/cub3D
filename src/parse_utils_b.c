/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils_b.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 15:44:49 by showard       #+#    #+#                 */
/*   Updated: 2025/07/01 17:19:51 by showard       ########   odam.nl         */
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

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("x: %f y: %f\n", data->player.pos_x, data->player.pos_y);
	printf("n: %s\n", data->n_tex);
	printf("n: %s\n", data->s_tex);
	printf("n: %s\n", data->w_tex);
	printf("n: %s\n", data->e_tex);
	printf("R: %i, G: %i, B: %i\n", data->floor[RED], data->floor[GREEN],
		data->floor[BLUE]);
	printf("R: %i, G: %i, B: %i\n", data->ceiling[RED], data->ceiling[GREEN],
		data->ceiling[BLUE]);
}
