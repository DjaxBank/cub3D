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

void print_map(t_state *state)
{
	int i;

	i = 0;
	while (state->map[i] != NULL)
	{
		printf("%s\n", state->map[i]);
		i++;
	}
	printf("x: %i y: %i\n", state->pos_x, state->pos_y);
	printf("n: %s\n", state->n_tex);
	printf("n: %s\n", state->s_tex);
	printf("n: %s\n", state->w_tex);
	printf("n: %s\n", state->e_tex);
	printf("R: %i, G: %i, B: %i\n", state->floor[RED], state->floor[GREEN],
		state->floor[BLUE]);
	printf("R: %i, G: %i, B: %i\n", state->ceiling[RED], state->ceiling[GREEN],
		state->ceiling[BLUE]);
}