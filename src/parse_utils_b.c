/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:44:49 by showard           #+#    #+#             */
/*   Updated: 2025/07/03 16:17:16 by dbank            ###   ########.fr       */
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
